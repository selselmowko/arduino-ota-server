#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); 

void setup() { u8g2.begin(); }

void loop() {
  // SOFTWARE RESET EXIT: If dial exits Card 3 zone, go back to menu!
  if (analogRead(A0) < 512 || analogRead(A0) > 767) { NVIC_SystemReset(); }

  int rawLight = analogRead(A1);
  int lightPercent = map(rawLight, 0, 1023, 0, 100);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.drawStr(4, 12, "LDR LIGHT DETECTOR");
    u8g2.drawLine(0, 15, 128, 15);
    u8g2.drawFrame(14, 28, 100, 14);
    u8g2.drawBox(16, 30, map(lightPercent, 0, 100, 0, 96), 10);
    u8g2.setCursor(45, 50); u8g2.print(lightPercent); u8g2.print(" %");
    u8g2.drawLine(0, 53, 128, 53); u8g2.drawStr(4, 63, "[TWIST DIAL TO EXIT]");
  } while ( u8g2.nextPage() );
  delay(100);
}
