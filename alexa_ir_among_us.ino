#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include "fauxmoESP.h"

#include <IRremoteESP8266.h>
#include <IRsend.h>

// Rename the credentials.sample.h file to credentials.h and 
// edit it according to your router configuration


fauxmoESP fauxmo;

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.  

// -----------------------------------------------------------------------------

#define SERIAL_BAUDRATE     115200

#define LED_LAMP  "Among us"

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------

void wifiSetup() {

    

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", "BTHub4-RQ7P");
    WiFi.begin("SSID", "password");

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}

void setup() {

    irsend.begin();

    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println();



    // Wifi
    wifiSetup();

    // By default, fauxmoESP creates it's own webserver on the defined port
    // The TCP port must be 80 for gen3 devices (default is 1901)
    // This has to be done before the call to enable()
    fauxmo.createServer(true); // not needed, this is the default value
    fauxmo.setPort(80); // This is required for gen3 devices

    // You have to call enable(true) once you have a WiFi connection
    // You can enable or disable the library at any moment
    // Disabling it will prevent the devices from being discovered and switched
    fauxmo.enable(true);

    // You can use different ways to invoke alexa to modify the devices state:
    // "Alexa, turn yellow lamp on"
    // "Alexa, turn on yellow lamp
    // "Alexa, set yellow lamp to fifty" (5g0 means 50% of brightness, note, this example does not use this functionality)

    // Add virtual devices
    fauxmo.addDevice(LED_LAMP);
    //fauxmo.addDevice("Among us strobe");
    //fauxmo.addDevice("Among us smooth");
    //fauxmo.addDevice("Among us fade");
    //fauxmo.addDevice("Among us purple");
    fauxmo.addDevice("Among us orange");
    fauxmo.addDevice("Among us white"); 
    fauxmo.addDevice("Among us blue");  
    fauxmo.addDevice("Among us green"); 
    fauxmo.addDevice("Among us red"); 

    //fauxmo.addDevice("Among us flash");

    fauxmo.addDevice("Among us pink");  //fuscia
    //fauxmo.addDevice("Among us ocean"); 
    //fauxmo.addDevice("Among us lemon"); 
    //fauxmo.addDevice("Among us plum");  
    //fauxmo.addDevice("Among us sea"); 
    //fauxmo.addDevice("Among us honey");

    fauxmo.addDevice("Among us sky");
    //fauxmo.addDevice("Among us tangerine");
    fauxmo.addDevice("Among us purple"); //teal
    fauxmo.addDevice("Among us mint");

    //fauxmo.addDevice("Among us brighter");
    //fauxmo.addDevice("Among us dimmer");

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value, unsigned int hue, unsigned int saturation, unsigned int ct) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
        if (strcmp(device_name, LED_LAMP)==0){
          if (state) {
            irsend.sendNEC(0xFFB04F, 32);                             
            Serial.println("ON");             

          }
          else {
            irsend.sendNEC(0xFFF807, 32);                             
            Serial.println("OFF"); 
          }
        }
        if (strcmp(device_name, "Among us strobe")==0) {
            irsend.sendNEC(0xFF00FF, 32);                             
            Serial.println("strobe"); 
        }
        if (strcmp(device_name, "Among us smooth")==0) {
            irsend.sendNEC(0xFF30CF, 32);                             
            Serial.println("smooth"); 
        }
        if (strcmp(device_name, "Among us flash")==0) {
            irsend.sendNEC(0xFF30CF, 32);                             
            Serial.println("flash"); 
        }
        if (strcmp(device_name, "Among us fade")==0) {
            irsend.sendNEC(0xFF58A7, 32);                             
            Serial.println("fade"); 
        }
        if (strcmp(device_name, "Among us fuscia")==0) {
            irsend.sendNEC(0xFFF00F, 32);                             
            Serial.println("fuscia"); 
        }
        if (strcmp(device_name, "Among us pink")==0) { // fuscia renamed pink
            irsend.sendNEC(0xFFF00F, 32);                             
            Serial.println("fuscia"); 
        }
        if (strcmp(device_name, "Among us ocean")==0) {
            irsend.sendNEC(0xFF28D7, 32);                             
            Serial.println("ocean"); 
        }
        if (strcmp(device_name, "Among us lemon")==0) {
            irsend.sendNEC(0xFF38C7, 32);                             
            Serial.println("lemon"); 
        }
        if (strcmp(device_name, "Among us plum")==0) {
            irsend.sendNEC(0xFF708F, 32);                             
            Serial.println("plum"); 
        }
        if (strcmp(device_name, "Among us sea")==0) {
            irsend.sendNEC(0xFF7887, 32);                             
            Serial.println("sea"); 
        }
        if (strcmp(device_name, "Among us honey")==0) {
            irsend.sendNEC(0xFF50AF, 32);                             
            Serial.println("honey"); 
        }
        //if (strcmp(device_name, "Among us purple")==0) {
        //    irsend.sendNEC(0xFF20DF, 32);                             
        //    Serial.println("purple"); 
        //}
        if (strcmp(device_name, "Among us sky")==0) {
            irsend.sendNEC(0xFF32CD, 32);                             
            Serial.println("sky"); 
        }
        if (strcmp(device_name, "Among us tangerine")==0) {
            irsend.sendNEC(0xFF02FD, 32);                             
            Serial.println("tangerine"); 
        }
        if (strcmp(device_name, "Among us teal")==0) {
            irsend.sendNEC(0xFF6897, 32);                             
            Serial.println("teal"); 
        }
        if (strcmp(device_name, "Among us purple")==0) { // teal renamed purple 
            irsend.sendNEC(0xFF6897, 32);                             
            Serial.println("teal"); 
        }
        if (strcmp(device_name, "Among us mint")==0) {
            irsend.sendNEC(0xFF48B7, 32);                             
            Serial.println("mint"); 
        }
        if (strcmp(device_name, "Among us orange")==0) {
            irsend.sendNEC(0xFFE817, 32);                             
            Serial.println("orange"); 
        }
        if (strcmp(device_name, "Among us white")==0) {
            irsend.sendNEC(0xFFA857, 32);                             
            Serial.println("white"); 
        }
        if (strcmp(device_name, "Among us blue")==0) {
            irsend.sendNEC(0xFF8877, 32);                             
            Serial.println("blue"); 
        }
        if (strcmp(device_name, "Among us green")==0) {
            irsend.sendNEC(0xFFD827, 32);                             
            Serial.println("green"); 
        }
        if (strcmp(device_name, "Among us red")==0) {
            irsend.sendNEC(0xFF9867, 32);                             
            Serial.println("red"); 
        }
        if (strcmp(device_name, "Among us dimmer")==0) {
            irsend.sendNEC(0xFFB847, 32);                             
            Serial.println("dimmer"); 
        }
        if (strcmp(device_name, "Among us brighter")==0) {
            irsend.sendNEC(0xFF906F, 32);                             
            Serial.println("brighter"); 
        }


    });

}

void loop() {
    delay(1);
    // fauxmoESP uses an async TCP server but a sync UDP server
    // Therefore, we have to manually poll for UDP packets
    fauxmo.handle();

    // This is a sample code to output free heap every 5 seconds
    // This is a cheap way to detect memory leaks
    //static unsigned long last = millis();
    //if (millis() - last > 5000) {
    //    last = millis();
    //    Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    //}

    // If your device state is changed by any other means (MQTT, physical button,...)
    // you can instruct the library to report the new state to Alexa on next request:
    // fauxmo.setState(ID_YELLOW, true, 255);
    
}
