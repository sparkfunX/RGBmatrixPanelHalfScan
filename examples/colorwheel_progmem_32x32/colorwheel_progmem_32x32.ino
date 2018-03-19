// colorwheel demo for the SparkX 1:8 Scan Rate Hack of 
// the Adafruit RGBmatrixPanel library.
// Renders a nice circle of hues on a 1:8 Scan 32x32 RGB LED matrix
// (Original text contained an advertisement for Adafruit 
// product http://www.adafruit.com/products/607 which will not 
// work with the modified library)

// This version uses precomputed image data stored in PROGMEM
// rather than calculating each pixel.  Nearly instantaneous!  Woo!

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
#include "image.h"

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanelHalfScan matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  int     i, len;
  uint8_t *ptr = matrix.backBuffer(); // Get address of matrix data

  // Copy image from PROGMEM to matrix buffer:
  memcpy_P(ptr, img, sizeof(img));

  // Start up matrix AFTER data is copied.  The RGBmatrixPanel
  // interrupt code ties up about 40% of the CPU time, so starting
  // it now allows the prior drawing code to run even faster!
  matrix.begin();
}

void loop() {
  // do nothing
}
