#define PIR    36
void setup() {
   Serial.begin(115200);
   pinMode(PIR, INPUT);
}
void loop() {
   if ( digitalRead(PIR) ) {
      Serial.println("Motion detected!");
   } else {
      Serial.println("No Motion!");
   }
   delay(500);
}
