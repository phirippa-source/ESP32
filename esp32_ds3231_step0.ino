// esp32_ds3231_step0.ino
void setup() {
   Serial.begin(115200);
   Serial.print(__DATE__);
   Serial.print(" ");
   Serial.println(__TIME__);
}

void loop() {
}
