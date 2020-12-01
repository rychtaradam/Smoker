#include <OneWire.h>
#include <DallasTemperature.h>
#include <virtuabotixRTC.h>
#include <TM1637Display.h>

#define TEMP 2
#define CLK 3
#define DIO 4

virtuabotixRTC myRTC(5, 6, 7);
TM1637Display display = TM1637Display(CLK, DIO);
OneWire oneWireDS(TEMP);
DallasTemperature teplomer(&oneWireDS);

const uint8_t all[] = {0xff, 0xff, 0xff, 0xff};
const uint8_t none[] = {0x00, 0x00, 0x00, 0x00};

const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};
const uint8_t degree[] = {
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

void setup() {
  Serial.begin(9600);
  //myRTC.setDS1302Time(00, 03, 10, 2, 1, 12, 2020);
  teplomer.begin();
  
  display.clear();
  delay(1000);
}

void loop() {
  myRTC.updateTime();
  display.setBrightness(4);
  teplomer.requestTemperatures();
  float teplota = teplomer.getTempCByIndex(0);
  
  if(teplota <= -10 || teplota >= 100){
    display.showNumberDec(teplota, false, 3, 0);
    display.setSegments(degree, 1, 3);
  }
  else if(teplota >= -9 || teplota <= 99){
    display.showNumberDec(teplota, false, 2, 0);
    display.setSegments(celsius, 2, 2);
  }
  delay(10000);

  display.showNumberDecEx(myRTC.hours, 0x40, true, 2, 0);
  display.showNumberDecEx(myRTC.minutes, 0, true, 2, 2);
  delay(10000);
}
