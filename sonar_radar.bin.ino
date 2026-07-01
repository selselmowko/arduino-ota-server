#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); 
const int trigPin = 5; const int echoPin = 6;

void setup() { u8g2.begin(); pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT); }

void loop() {
  // SOFTWARE RESET EXIT: If dial exits Card 2 zone, go back to menu!
  if (analogRead(A0) < 256 || analogRead(A0) > 511) { NVIC_SystemReset(); }

  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.drawStr(4, 12, "ULTRASONIC RADAR");
    u8g2.drawLine(0, 15, 128, 15);
    u8g2.setFont(u8g2_font_logisoso24_tf);
    u8g2.setCursor(15, 48); u8g2.print(distance); u8g2.print(" cm");
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.drawLine(0, 53, 128, 53); u8g2.drawStr(4, 63, "[TWIST DIAL TO EXIT]");
  } while ( u8g2.nextPage() );
  delay(200);
}
