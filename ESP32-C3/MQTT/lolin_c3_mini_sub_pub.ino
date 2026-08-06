#include <WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;

const char* ssid = "RiaSummer2G";
const char* password = "730124go";
const char* brokerAddress = "192.168.2.6";
const char* brokerUser = "ship";
const char* brokerPassword = "1234";
const char* clientId = "ria_lolin_c3_mini_sub_pub_01";
const char* topicSub = "Riatech/A/Line1/Led";
const char* topicPub = "Riatech/A/Line1/Lux";


void onMessage(char* topic, byte* payload, unsigned int length) {
    String message = "";
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println("Topic: " + String(topic));
    Serial.println("Message: " + message);
    if (message == "on" || message == "On") {
        digitalWrite(7, HIGH);
    } else if (message == "off" || message == "Off") {
        digitalWrite(7, LOW);
    } else {
        Serial.print("Wring Message ! : " + message );
    }
}

WiFiClient wifiClient;
PubSubClient mqttClient(brokerAddress, 1883, onMessage, wifiClient);


void setup() {
    Serial.begin(115200);
    Serial.println("Connecting to Wi-Fi: " + String(ssid));

    WiFi.begin(ssid, password);
    WiFi.setTxPower(WIFI_POWER_8_5dBm);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");  delay(500);
    }

    Serial.println();
    Serial.println("Wi-Fi connected");
    Serial.println("Connecting to MQTT Broker: " + String(brokerAddress));

    while (!mqttClient.connect(clientId, brokerUser, brokerPassword)) {
        Serial.print(".");  delay(500);
    }

    Serial.println();
    Serial.println("MQTT Broker connected");
    mqttClient.subscribe(topicSub);
    Serial.println("Subscribed topic: " + String(topicSub));
    
    pinMode(7, OUTPUT);
    Wire.begin(8, 10, 400000);
    lightMeter.begin();
}


void loop() {
    mqttClient.loop();

    char buf[16];
    float lux = lightMeter.readLightLevel();
    snprintf(buf, sizeof(buf), "%.1f", lux);
    bool result = mqttClient.publish(topicPub, buf);

    if (result) {
        Serial.printf("%s : %s\n", topicPub, buf);
    } else {
        Serial.println("Publish failed");
    }
    delay(2000);
}
