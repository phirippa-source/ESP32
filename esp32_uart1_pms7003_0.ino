#include "PMS.h"
PMS pms(Serial1);
PMS::DATA data;

void setup() {
   Serial.begin(9600); 
   // UART1의 Rx, Tx 핀을 25, 26으로 설정
   Serial1.begin(9600, SERIAL_8N1, 25, 26);
}
void loop() {
   if( pms.read(data) ) {
      Serial.print("PM 2.5[ug/m3]:"); Serial.println(data.PM_AE_UG_2_5);
   }
}
