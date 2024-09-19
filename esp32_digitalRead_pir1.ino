#define PIR 36
void setup() {
   Serial.begin(115200);
   pinMode(PIR, INPUT);
}
void loop() {
   Serial.println(digitalRead(PIR) ? "Motion detected!" : "No Motion!");
   delay(500);
}

