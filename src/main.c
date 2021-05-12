#include "esp_log.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "dht11.h"

#define TAG "APP_MAIN"
#define DHT11_PIN GPIO_NUM_4

static struct dht11_reading stDht11Reading;

void dht11_test(void *pvParameter)
{
  DHT11_init(DHT11_PIN);

  while(1)
  {
    stDht11Reading = DHT11_read();
    if((DHT11_OK == stDht11Reading.status) &&
       (0 != stDht11Reading.temperature) &&
       (0 != stDht11Reading.humidity))
    {
      ESP_LOGI(TAG,
               "Temperature: %d °C    Humidity: %d %%",
               stDht11Reading.temperature,
               stDht11Reading.humidity);
    } 
    else
    {
      ESP_LOGW(TAG,
               "Cannot read from sensor: %s",
               (DHT11_TIMEOUT_ERROR == stDht11Reading.status)
               ?"Timeout"
               :"Bad CRC");
    }
    vTaskDelay(2500 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  xTaskCreate(dht11_test, "dht11_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
