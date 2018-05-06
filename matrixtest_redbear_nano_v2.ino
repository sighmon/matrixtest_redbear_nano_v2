// Adafruit_DotStarMatrix example for single DotStar LED matrix.
// Scrolls 'Howdy' across the matrix.

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define DATAPIN  4
#define CLOCKPIN 5
#define LEDPIN 13

// MATRIX DECLARATION:
// Parameter 1 = width of DotStar matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   DS_MATRIX_TOP, DS_MATRIX_BOTTOM, DS_MATRIX_LEFT, DS_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     DS_MATRIX_TOP + DS_MATRIX_LEFT for the top-left corner.
//   DS_MATRIX_ROWS, DS_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   DS_MATRIX_PROGRESSIVE, DS_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type:
//   DOTSTAR_BRG  Pixels are wired for BRG bitstream (most DotStar items)
//   DOTSTAR_GBR  Pixels are wired for GBR bitstream (some older DotStars)

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
  8, 8, DATAPIN, CLOCKPIN,
  DS_MATRIX_TOP     + DS_MATRIX_LEFT +
  DS_MATRIX_COLUMNS + DS_MATRIX_PROGRESSIVE,
  DOTSTAR_BRG);
//Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
//  8, 8,
//  DS_MATRIX_TOP     + DS_MATRIX_RIGHT +
//  DS_MATRIX_COLUMNS + DS_MATRIX_PROGRESSIVE,
//  DOTSTAR_BRG);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), // Red
  matrix.Color(0, 255, 0), // Green
  matrix.Color(0, 0, 255), // Blue
  matrix.Color(255, 255, 255) // White
};

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10); // was 40
//  matrix.setTextColor(colors[0]);
  matrix.setTextColor(colors[2]);
  // Show signs of life
  pinMode(LEDPIN, OUTPUT);
}

int x    = matrix.width();
int pass = 0;
const String messageToDisplay = "MOD.   ";
int messageLength = messageToDisplay.length();

void loop() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
//  matrix.print(F("sighmon"));
  matrix.print(messageToDisplay);
  if(--x < -(6 * messageLength)) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    // All colours
//    matrix.setTextColor(colors[pass]);
    // Blue
    matrix.setTextColor(colors[3]);
  }
  matrix.show();
  delay(100);
  digitalWrite(LEDPIN, HIGH);
}
