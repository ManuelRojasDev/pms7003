#include <pms7003.h>

pms7003 pms(1);// initialize on uart 1

void setup() {
  Serial.begin(9600);
}


unsigned long timer;
uint16_t PM1_0, PM2_5, PM10;
void loop() {


  if ( millis() - t > 1000) {// print every 1 second
    t = millis();
    pms.read(PM1_0, PM2_5, PM10);
    Serial.println("PM1.0 concentration in ug/M^3: " + String(PM1_0)) + "   PM2.5.0 concentration in ug/M^3: " + String(PM2_5) + " PM10 concentration in ug/M^3: " + String(PM10));
  }

}


