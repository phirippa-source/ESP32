#define RS485RW     4
#define WRITE_MODE  HIGH
#define READ_MODE   LOW

HardwareSerial RS485(2);
byte cmd[] = {0x01, 0x04, 0x00, 0x01, 0x00, 0x02, 0x20, 0x0B};
byte rxBuf[9];

void setup() {
    Serial.begin(9600);
    RS485.begin(9600, SERIAL_8N1, 16, 17);
    pinMode(RS485RW, OUTPUT);
}

void loop() {
    float t, h;
    digitalWrite(RS485RW, WRITE_MODE);
    RS485.write(cmd, sizeof(cmd));
    RS485.flush();
    digitalWrite(RS485RW, READ_MODE);
    if(RS485.readBytes(rxBuf, 9)) {
        t = ((rxBuf[3] << 8) | rxBuf[4]) / 10.0;
        h = ((rxBuf[5] << 8) | rxBuf[6]) / 10.0;
        Serial.print("Temp : " + String(t, 1) + "\t");
        Serial.println("Humi :" + String(h, 1));
    }
    delay(1000);
}
