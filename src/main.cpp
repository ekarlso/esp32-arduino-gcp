#include "Arduino.h"

#include <WiFiClientSecure.h>

#include <CloudIoTCore.h>
// #include <CloudIoTCoreMQTTClient.h>
// #include <PubSubClient.h>
#include "MQTT.h"

#include "config.h" // Configure with your settings
#include <WiFi.h>
#include <time.h>
#include <rBase64.h> // If using binary messages
#include <pb_decode.h>
#include <pb.h>

#include <backoff.h>
#include <sensor.pb.h>

#define PIR_PIN 27
#define GOOGLE_IOT_HTTP_BRIDGE "cloudiotdevice.googleapis.com"

CloudIoTCoreDevice device(project_id, location, registry_id, device_id,
                          private_key_str);
// CloudIoTCoreMQTTClient client(device);

// When was the PIR last fired
long triggerLatestMillis = 0;
// How long to wait before resetting the "state" 1 sec = 1000 milli
long triggerResetDuration = 20000;

unsigned long iss;
String jwt;

WiFiClientSecure wifiClient;

// Checks if motion was detected, sets LED HIGH and starts a timer
void IRAM_ATTR detectsMovement()
{
    Serial.println("Detected motion!");
    triggerLatestMillis = millis();
}

void messageReceived(String &topic, String &payload)
{
    sensor_SensorEvent event = sensor_SensorEvent_init_zero;

    Serial.println("incoming: " + topic + " - " + payload);
}

String getJWT()
{
    if (iss == 0 || time(nullptr) - iss > 3600)
    {
        iss = time(nullptr);
        jwt = device.createJWT(iss);
    }
    return jwt;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting detector.");

    // PIR Motion Sensor mode INPUT_PULLUP
    pinMode(PIR_PIN, INPUT_PULLUP);
    // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), detectsMovement, FALLING);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }

    Serial.println("IP:");
    Serial.println(WiFi.localIP().toString());

    Serial.println("Waiting on time sync...");
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    while (time(nullptr) < 1510644967)
    {
        delay(10);
    }

    // wifiClient.setCACert(root_cert);
}

void sendTelemetry(String data)
{
    String host = GOOGLE_IOT_HTTP_BRIDGE;
    if (!wifiClient.connect(host.c_str(), 443))
    {
        Serial.println("Connect failed.");
        return;
    }

    rbase64.encode(data);
    String postData = String("{\"binary_data\": \"") + rbase64.result() + String("\"}");

    String header = String("POST ") + device.getSendTelemetryPath().c_str() + String(" HTTP/1.1");
    String authString = "Authorization: Bearer " + String(jwt.c_str());

    wifiClient.println(header.c_str());
    wifiClient.println("host: https://" + host);
    wifiClient.println("method: POST");
    wifiClient.println("cache-control: no-cache");
    wifiClient.println(authString.c_str());
    wifiClient.println("content-type: application/json");
    wifiClient.print("content-length:");
    wifiClient.println(postData.length());
    wifiClient.println();
    wifiClient.println(postData);
    wifiClient.println();
    wifiClient.println();

    while (!wifiClient.available())
    {
        delay(100);
        Serial.print('.');
    }

    while (wifiClient.connected())
    {
        String line = wifiClient.readStringUntil('\n');
        if (line.startsWith("HTTP/1.1 200 OK"))
        {
            // reset backoff
            resetBackoff();
        }
        if (line == "\r")
        {
            break;
        }
    }
    while (wifiClient.available())
    {
        String line = wifiClient.readStringUntil('\n');
    }
     
    Serial.println("Complete.");
    wifiClient.stop();
}

void loop()
{
    Serial.println("Connecting.");

    long timeSinceLastTrigger = millis() - triggerLatestMillis;
    if (timeSinceLastTrigger >= triggerResetDuration)
    {
        Serial.println("Motion detection reset");
    }

    sendTelemetry("test");
}