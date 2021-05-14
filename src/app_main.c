#include <stdio.h>
#include <string.h>

#include <esp_log.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "dht11.h"
#include "firestore.h"

#include "app_wifi.h"
#include "app_time.h"
#include "app_ota.h"

static void _app_main_send_data(struct dht11_reading *);
static void _app_main_firestore_task(void *);

#define APP_MAIN_TAG                             "APP_MAIN"
#define APP_MAIN_DHT11_PIN                       GPIO_NUM_4

#define APP_MAIN_FIRESTORE_TASK_STACK_SIZE       10240
#define APP_MAIN_FIRESTORE_TASK_PRIORITY         4
#define APP_MAIN_FIRESTORE_PERIOD_MS             2500
#define APP_MAIN_FIRESTORE_DOC_MAX_SIZE          160
#define APP_MAIN_FIRESTORE_DOC_EXAMPLE           "{"                                     \
                                                   "\"fields\": {"                       \
                                                     "\"humidity\": {"                   \
                                                       "\"integerValue\": 55"            \
                                                     "},"                                \
                                                     "\"temperature\": {"                \
                                                       "\"integerValue\": 23"            \
                                                     "},"                                \
                                                     "\"timestamp\": {"                  \
                                                       "\"integerValue\": 1621010203262" \
                                                     "},"                                \
                                                   "}"                                   \
                                                 "}"

static uint32_t u32DocLength;
static char tcDoc[APP_MAIN_FIRESTORE_DOC_MAX_SIZE];
static struct dht11_reading stDht11Reading;

void app_main(void)
{
  app_wifi_init();
  app_wifi_wait();

  app_ota_start();

  app_time_init();

  xTaskCreate(_app_main_firestore_task,
              "firestore",
              APP_MAIN_FIRESTORE_TASK_STACK_SIZE,
              NULL,
              APP_MAIN_FIRESTORE_TASK_PRIORITY,
              NULL);
}

static void _app_main_firestore_task(void *pvParameter)
{
  DHT11_init(APP_MAIN_DHT11_PIN);
  firestore_init();

  while(1)
  {
    stDht11Reading = DHT11_read();
    if((DHT11_OK == stDht11Reading.status) &&
       (0 != stDht11Reading.temperature) &&
       (0 != stDht11Reading.humidity))
    {
      ESP_LOGI(APP_MAIN_TAG,
               "Temperature: %d °C    Humidity: %d %%",
               stDht11Reading.temperature,
               stDht11Reading.humidity);
      _app_main_send_data(&stDht11Reading);
    } 
    else
    {
      ESP_LOGW(APP_MAIN_TAG,
               "Cannot read from sensor: %s",
               (DHT11_TIMEOUT_ERROR == stDht11Reading.status)
               ?"Timeout"
               :"Bad CRC");
    }
    vTaskDelay(APP_MAIN_FIRESTORE_PERIOD_MS / portTICK_PERIOD_MS);
  }
}

static void _app_main_send_data(struct dht11_reading *pstReading)
{
  int64_t s64Timestamp;

  /* Format document with newly fetched data */
  if(ESP_OK == app_time_get_ts(&s64Timestamp))
  {
    ESP_LOGI(APP_MAIN_TAG, "Current timestamp: %lld", s64Timestamp);
    u32DocLength = snprintf(tcDoc,
                            sizeof(tcDoc),
                            "{\"fields\":{\"humidity\":{\"integerValue\":%d},\"temperature\":{\"integerValue\":%d},\"timestamp\":{\"integerValue\":%lld}}}",
                            pstReading->humidity,
                            pstReading->temperature,
                            s64Timestamp);
  }
  else
  {
    ESP_LOGW(APP_MAIN_TAG, "Failed to get timestamp --> formatting data without timestamp");
    u32DocLength = snprintf(tcDoc,
                            sizeof(tcDoc),
                            "{\"fields\":{\"humidity\":{\"integerValue\":%d},\"temperature\":{\"integerValue\":%d}}}",
                            pstReading->humidity,
                            pstReading->temperature);
  }
  ESP_LOGD(APP_MAIN_TAG, "Document length after formatting: %d", u32DocLength);
  if(u32DocLength > 0)
  {
    /* Update document in firestore or create it if it doesn't already exists */
    if(FIRESTORE_OK == firestore_update_document("devices",
                                                 "dht11-node",
                                                 tcDoc,
                                                 &u32DocLength))
    {
      ESP_LOGI(APP_MAIN_TAG, "Document updated successfully");
      ESP_LOGD(APP_MAIN_TAG, "Updated document length: %d", u32DocLength);
      ESP_LOGD(APP_MAIN_TAG, "Updated document content:\r\n%.*s", u32DocLength, tcDoc);
    }
    else
    {
      ESP_LOGE(APP_MAIN_TAG, "Couldn't update document");
    }
  }
  else
  {
    ESP_LOGE(APP_MAIN_TAG, "Couldn't format document");
  }
}
