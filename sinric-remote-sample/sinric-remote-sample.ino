#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#ifdef ESP8266 
       #include <ESP8266WiFi.h>
#endif 
#ifdef ESP32   
       #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProLight.h"

#define WIFI_SSID         ""    
#define WIFI_PASS         ""
#define APP_KEY           ""      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        ""   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define BAUD_RATE         9600                // Change baudrate to your need

#define AC_ID          ""
#define LED_ID         ""

const uint16_t kIrLed = 16;  // D4

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

struct {
  bool powerState = false;
} device_state; 

bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Device %s power turned %s \r\n", deviceId.c_str(), state?"on":"off");
  const char* locate_state = state?"on":"off";
  if (String(deviceId.c_str()) == String(AC_ID)){
    if (locate_state == "on"){
      uint16_t rawData[440]={3470, 1742, 438, 434, 438, 1310, 438, 434, 438, 434, 438, 438, 434, 438, 438, 438, 434, 434, 438, 438, 434, 438, 438, 434, 438, 438, 434, 438, 438, 1306, 438, 438, 438, 434, 438, 438, 434, 438, 434, 438, 438, 434, 438, 434, 438, 1310, 438, 1310, 438, 1306, 438, 434, 438, 438, 438, 1310, 434, 438, 434, 438, 438, 434, 438, 434, 438, 438, 434, 438, 462, 410, 438, 434, 438, 438, 438, 434, 438, 434, 438, 438, 438, 434, 438, 434, 438, 438, 434, 438, 438, 434, 438, 434, 438, 434, 438, 438, 438, 434, 438, 438, 438, 434, 438, 434, 438, 434, 438, 438, 434, 438, 438, 434, 438, 434, 466, 410, 438, 1310, 434, 1310, 438, 434, 438, 438, 434, 438, 446, 426, 438, 434, 438, 10042, 3470, 1742, 434, 438, 434, 1310, 438, 434, 438, 438, 434, 438, 438, 434, 438, 434, 438, 438, 434, 438, 438, 434, 438, 434, 438, 438, 438, 434, 438, 1306, 442, 434, 438, 434, 438, 434, 438, 438, 438, 434, 438, 434, 438, 434, 438, 1310, 438, 1310, 434, 1310, 438, 434, 438, 438, 434, 1310, 438, 434, 438, 438, 434, 438, 438, 434, 438, 438, 438, 430, 438, 438, 438, 434, 442, 430, 438, 438, 438, 434, 438, 434, 438, 434, 442, 1306, 438, 434, 438, 438, 438, 430, 442, 1306, 438, 1310, 438, 434, 462, 410, 438, 438, 438, 1306, 438, 434, 438, 438, 438, 1306, 438, 1310, 438, 434, 438, 434, 438, 438, 438, 434, 438, 434, 438, 434, 438, 438, 438, 434, 438, 434, 462, 1286, 438, 1306, 438, 434, 462, 1286, 438, 438, 438, 434, 438, 434, 438, 1310, 434, 438, 438, 434, 438, 434, 438, 438, 438, 434, 438, 434, 438, 434, 438, 434, 442, 434, 438, 434, 438, 434, 438, 434, 442, 434, 438, 434, 438, 438, 434, 438, 438, 434, 438, 434, 438, 1310, 438, 1310, 434, 438, 438, 434, 438, 434, 438, 434, 438, 434, 438, 438, 438, 434, 438, 434, 438, 434, 442, 434, 438, 1306, 438, 1310, 438, 434, 438, 438, 438, 430, 442, 434, 438, 434, 438, 434, 438, 438, 438, 434, 438, 434, 442, 434, 438, 434, 438, 434, 438, 434, 438, 438, 438, 434, 438, 434, 438, 438, 434, 438, 438, 434, 438, 434, 438, 438, 438, 434, 438, 434, 438, 434, 438, 1310, 438, 434, 438, 434, 438, 438, 438, 434, 462, 410, 438, 434, 442, 434, 462, 410, 438, 434, 438, 1310, 458, 1290, 438, 430, 462, 414, 438, 434, 438, 434, 438, 434, 442, 434, 438, 1306, 462, 414, 438, 1310, 458, 1286, 462, 410, 462, 410, 438, 438, 438, 1000};
      irsend.sendRaw(rawData, 440, 38);  // Send a raw data capture at 38kHz.
    }
    if (locate_state == "off"){
      uint16_t rawData[440]={3506, 1734, 446, 426, 446, 1298, 450, 426, 446, 426, 446, 426, 450, 426, 446, 426, 446, 426, 450, 426, 450, 422, 450, 422, 450, 426, 446, 426, 446, 1298, 450, 426, 446, 426, 450, 422, 450, 426, 450, 422, 450, 422, 450, 426, 450, 1294, 450, 1298, 446, 1298, 450, 426, 450, 422, 450, 1298, 446, 426, 450, 422, 450, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 422, 450, 426, 450, 422, 450, 422, 450, 426, 450, 422, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 1298, 450, 1298, 446, 426, 450, 422, 450, 426, 450, 422, 450, 422, 450, 10002, 3514, 1702, 474, 422, 450, 1298, 450, 422, 450, 426, 446, 426, 450, 422, 450, 422, 454, 422, 450, 422, 454, 418, 450, 426, 450, 422, 450, 422, 450, 1298, 450, 422, 450, 426, 446, 426, 450, 422, 450, 422, 450, 426, 450, 422, 450, 1298, 450, 1298, 446, 1298, 450, 422, 450, 426, 446, 1298, 450, 426, 446, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 450, 422, 446, 426, 450, 426, 446, 426, 446, 426, 450, 1298, 446, 426, 450, 422, 450, 426, 446, 1298, 450, 1298, 446, 1298, 450, 1298, 446, 426, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 422, 450, 426, 446, 1302, 446, 1298, 446, 426, 450, 1298, 446, 426, 450, 426, 446, 1298, 450, 426, 446, 1298, 446, 426, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 422, 450, 426, 450, 422, 450, 422, 450, 1298, 450, 1298, 446, 426, 450, 422, 450, 426, 446, 426, 446, 426, 450, 426, 446, 426, 446, 426, 450, 426, 446, 426, 446, 1298, 450, 1298, 446, 426, 450, 1298, 446, 426, 450, 422, 450, 426, 446, 426, 446, 426, 450, 426, 446, 426, 450, 426, 446, 426, 446, 426, 446, 426, 450, 426, 446, 426, 446, 426, 450, 426, 446, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 422, 450, 426, 446, 1298, 450, 426, 446, 426, 446, 426, 450, 426, 446, 426, 446, 426, 450, 422, 450, 426, 446, 426, 450, 1298, 446, 1298, 450, 426, 446, 426, 450, 422, 450, 426, 446, 426, 446, 426, 446, 430, 446, 1298, 446, 430, 450, 1294, 446, 426, 450, 426, 446, 1298, 446, 1000};
      irsend.sendRaw(rawData, 440, 38);  // Send a raw data capture at 38kHz.
    }
  }

  if (String(deviceId.c_str()) == String(LED_ID)){
    if (locate_state == "on"){
      uint16_t rawData[68]={8954, 4474, 554, 558, 558, 1674, 558, 558, 582, 534, 558, 558, 586, 534, 554, 558, 562, 1674, 558, 1674, 554, 562, 554, 1678, 554, 1678, 554, 558, 558, 1674, 554, 1678, 554, 562, 554, 562, 554, 1678, 554, 1674, 558, 558, 558, 558, 582, 1654, 554, 558, 558, 1674, 558, 1674, 582, 534, 558, 558, 558, 1674, 558, 1670, 586, 530, 562, 1674, 558, 558, 554, 1000};
      irsend.sendRaw(rawData, 68, 38);  // Send a raw data capture at 38kHz.
    }
    if (locate_state == "off"){
      uint16_t rawData[68]={8974, 4450, 558, 554, 582, 1650, 558, 558, 558, 558, 558, 558, 558, 558, 558, 558, 558, 1674, 562, 1670, 582, 562, 558, 1642, 582, 1654, 550, 590, 558, 1646, 554, 1678, 530, 610, 562, 530, 578, 1650, 554, 1678, 534, 1694, 538, 1694, 562, 1666, 602, 542, 506, 1698, 602, 1626, 606, 538, 510, 606, 506, 610, 506, 610, 506, 610, 506, 1698, 602, 542, 534, 1000};
      irsend.sendRaw(rawData, 68, 38);  // Send a raw data capture at 38kHz.
    }
  }
  
  device_state.powerState = state;
  return true; // request handled properly
}

void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  IPAddress localIP = WiFi.localIP();
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
}

void setupSinricPro() {
  // get a new Light device from SinricPro
  SinricProLight &myAC = SinricPro[AC_ID];
  SinricProLight &myLED = SinricPro[LED_ID];

  // set callback function to device
  myAC.onPowerState(onPowerState);
  myLED.onPowerState(onPowerState);

  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  irsend.begin();
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
