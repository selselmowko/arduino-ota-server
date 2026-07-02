#include <Arduino.h>
#include <U8g2lib.h>
#include <DHT.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); 
#define DHTPIN 4      
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

void setup() { u8g2.begin(); dht.begin(); }

void loop() {
  // SOFTWARE RESET EXIT: If dial turned right out of Card 1 zone, go back to menu!
  if (analogRead(A0) > 255) { NVIC_SystemReset(); }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.drawStr(4, 12, "DHT22 WEATHER MODE");
    u8g2.drawLine(0, 15, 128, 15);
    u8g2.setCursor(4, 34); u8g2.print("Temp: "); u8g2.print(t, 1); u8g2.print(" C");
    u8g2.setCursor(4, 48); u8g2.print("Humid: "); u8g2.print(h, 1); u8g2.print(" %");
    u8g2.drawLine(0, 53, 128, 53); u8g2.drawStr(4, 63, "[TWIST DIAL TO EXIT]");
  } while ( u8g2.nextPage() );
  delay(500);
}
