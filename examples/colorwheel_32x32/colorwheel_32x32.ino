// colorwheel demo for the SparkX 1:8 Scan Rate Hack of 
// the Adafruit RGBmatrixPanel library.
// Renders a nice circle of hues on a 1:8 Scan 32x32 RGB LED matrix
// (Original text contained an advertisement for Adafruit 
// product http://www.adafruit.com/products/607 which will not 
// work with the modified library)

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.
/*
  /$$$$$$                                /$$       /$$   /$$
 /$$__  $$  HAXX0RD FOR 1/8 SCAN RATE   | $$      | $$  / $$
| $$  \__/  /$$$$$$   /$$$$$$   /$$$$$$ | $$   /$$|  $$/ $$/
|  $$$$$$  /$$__  $$ |____  $$ /$$__  $$| $$  /$$/ \  $$$$/ 
 \____  $$| $$  \ $$  /$$$$$$$| $$  \__/| $$$$$$/   >$$  $$ 
 /$$  \ $$| $$  | $$ /$$__  $$| $$      | $$_  $$  /$$/\  $$
|  $$$$$$/| $$$$$$$/|  $$$$$$$| $$      | $$ \  $$| $$  \ $$
 \______/ | $$____/  \_______/|__/      |__/  \__/|__/  |__/
          | $$ BY NPOOLE, SPARKFUN ELECTRONICS 2018                                             
          | $$                                              
          |__/  
*/

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanelHalfScan.h> // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanelHalfScan matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  int      x, y, hue;
  float    dx, dy, d;
  uint8_t  sat, val;
  uint16_t c;

  matrix.begin();

  for(y=0; y < matrix.width(); y++) {
    dy = 15.5 - (float)y;
    for(x=0; x < matrix.height(); x++) {
      dx = 15.5 - (float)x;
      d  = dx * dx + dy * dy;
      if(d <= (16.5 * 16.5)) { // Inside the circle(ish)?
        hue = (int)((atan2(-dy, dx) + PI) * 1536.0 / (PI * 2.0));
        d = sqrt(d);
        if(d > 15.5) {
          // Do a little pseudo anti-aliasing along perimeter
          sat = 255;
          val = (int)((1.0 - (d - 15.5)) * 255.0 + 0.5);
        } else
        {
          // White at center
          sat = (int)(d / 15.5 * 255.0 + 0.5);
          val = 255;
        }
        c = matrix.ColorHSV(hue, sat, val, true);
      } else {
        c = 0;
      }
      matrix.drawPixel(x, y, c);
    }
  }
}

void loop() {
  // do nothing
}
