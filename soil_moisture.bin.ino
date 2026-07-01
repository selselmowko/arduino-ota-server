#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); 

void setup() { u8g2.begin(); }

void loop() {
  // SOFTWARE RESET EXIT: If dial turned left out of Card 4 zone, go back to menu!
  if (analogRead(A0) < 768) { NVIC_SystemReset(); }

  int rawMoisture = analogRead(A1);
  int moisturePercent = map(rawMoisture, 1023, 200, 0, 100);
  if(moisturePercent > 100) moisturePercent = 100;
  if(moisturePercent < 0) moisturePercent = 0;

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.drawStr(4, 12, "SOIL MOISTURE MONITOR");
    u8g2.drawLine(0, 15, 128, 15);
    u8g2.setCursor(4, 38); u8g2.print("Saturation: "); u8g2.print(moisturePercent); u8g2.print(" %");
    u8g2.drawLine(0, 53, 128, 53); u8g2.drawStr(4, 63, "[TWIST DIAL TO EXIT]");
  } while ( u8g2.nextPage() );
  delay(200);
}
