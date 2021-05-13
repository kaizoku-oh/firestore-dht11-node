# pio-dht11
An example of using esp-idf dht11 sensor component with platformio

<!-- ![Firestore logo](https://github.com/kaizoku-oh/pio-dht11/blob/main/docs/image/logo.png) -->
<!-- ![](https://github.com/<OWNER>/<REPOSITORY>/workflows/<WORKFLOW_NAME>/badge.svg) -->
![GitHub Build workflow status](https://github.com/kaizoku-oh/pio-dht11/workflows/Build/badge.svg)
![GitHub Release workflow status](https://github.com/kaizoku-oh/pio-dht11/workflows/Release/badge.svg)
[![GitHub release](https://img.shields.io/github/v/release/kaizoku-oh/pio-dht11)](https://github.com/kaizoku-oh/pio-dht11/releases)
[![GitHub issues](https://img.shields.io/github/issues/kaizoku-oh/pio-dht11)](https://github.com/kaizoku-oh/pio-dht11/issues)
![GitHub top language](https://img.shields.io/github/languages/top/kaizoku-oh/pio-dht11)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://github.com/kaizoku-oh/pio-dht11/blob/main/LICENSE)
[![Twitter follow](https://img.shields.io/twitter/follow/kaizoku_ouh?style=social)](https://twitter.com/kaizoku_ouh)

## How to use?
### Window (Powershell)
``` powershell
# Set local environment variables
> $env:WIFI_SSID = '"TYPE_YOUR_WIFI_SSID_HERE"'
> $env:WIFI_PASS = '"TYPE_YOUR_WIFI_PASSWORD_HERE"'
> $env:FIRESTORE_FIREBASE_PROJECT_ID = '"TYPE_YOUR_FIREBASE_PROJECT_ID_HERE"'
> $env:FIRESTORE_FIREBASE_API_KEY = '"TYPE_YOUR_FIREBASE_API_KEY_HERE"'

# OPTIONAL: To read and verify the values of the variables that you just set:
> Get-ChildItem Env:WIFI_SSID
> Get-ChildItem Env:WIFI_PASS
> Get-ChildItem Env:FIRESTORE_FIREBASE_PROJECT_ID
> Get-ChildItem Env:FIRESTORE_FIREBASE_API_KEY
```

### Linux (Bash)
``` bash
# Set local environment variables
$ export WIFI_SSID='"TYPE_YOUR_WIFI_SSID_HERE"'
$ export WIFI_PASS='"TYPE_YOUR_WIFI_PASS_HERE"'
$ export FIRESTORE_FIREBASE_PROJECT_ID='"TYPE_YOUR_FIREBASE_PROJECT_ID_HERE"'
$ export FIRESTORE_FIREBASE_API_KEY='"TYPE_YOUR_FIREBASE_PROJECT_ID_HERE"'

# OPTIONAL: To read and verify the values of the variables that you just set:
$ echo $WIFI_SSID
$ echo $WIFI_PASS
$ echo $FIRESTORE_FIREBASE_PROJECT_ID
$ echo $FIRESTORE_FIREBASE_API_KEY
```
