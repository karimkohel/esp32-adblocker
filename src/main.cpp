#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"

constexpr unsigned long WIFI_TIMEOUT_MS = 20000;

// Connect to the existing Wi-Fi network
void connectToWiFi() {

    Serial.println();
    Serial.println("Connecting to Wi-Fi...");

    // Station mode: connect to an existing access point
    WiFi.mode(WIFI_STA);

    WiFi.setSleep(false);

    // Automatically reconnect if Wi-Fi drops
    WiFi.setAutoReconnect(true);

    // Start connecting
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED &&
           millis() - start < WIFI_TIMEOUT_MS) {

        delay(500);
        Serial.print(".");
    }

    Serial.println();

    // Check connection result
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wi-Fi connection failed!");
        return;
    }

    Serial.println("Wi-Fi connected successfully!");

    // Print network information
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Subnet mask: ");
    Serial.println(WiFi.subnetMask());

    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());

    Serial.print("DNS server: ");
    Serial.println(WiFi.dnsIP());

    Serial.print("Signal strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    // Test DNS resolution
    IPAddress resolvedIP;

    if (WiFi.hostByName("example.com", resolvedIP) == 1) {
        Serial.print("example.com resolved to: ");
        Serial.println(resolvedIP);
    } else {
        Serial.println("DNS resolution failed!");
    }
}

void setup() {

    Serial.begin(115200);
    delay(1500);

    Serial.println();
    Serial.println("===========================");
    Serial.println("    ESP32 AdBlock - WiFi   ");
    Serial.println("===========================");

    connectToWiFi();
}

void loop() {

    static unsigned long lastReport = 0;

    if (millis() - lastReport >= 5000) {

        lastReport = millis();

        if (WiFi.status() == WL_CONNECTED) {

            Serial.print("Online | IP: ");
            Serial.print(WiFi.localIP());

            Serial.print(" | RSSI: ");
            Serial.print(WiFi.RSSI());
            Serial.println(" dBm");

        } else {

            Serial.println("Wi-Fi disconnected!");
            WiFi.reconnect();
        }
    }

    delay(50);
}