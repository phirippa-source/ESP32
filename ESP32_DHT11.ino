#include "DHT.h"
#define DHTPIN  4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t) ) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: " + String(t, 1) + "[°C]\t");
    Serial.println("Humidity: " + String(h, 1) + "[%]");
    delay(2000);
}
