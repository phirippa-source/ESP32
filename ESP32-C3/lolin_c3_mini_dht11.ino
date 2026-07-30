#include <DHT.h>

#define DHT_PIN 1
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(115200);
    delay(1000);

    dht.begin();

    Serial.println("DHT11 test start");
}

void loop() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT11");
        delay(2000);
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity, 1);
    Serial.println(" %");

    delay(2000);
}
