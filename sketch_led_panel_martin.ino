#include <Adafruit_NeoPixel.h> // add this library "Adafruit_NeoPixel" to your Arduino IDE

// Uses a 8x8 WS2812B led panel to display a birthday card for an 8 year old kid.
// See it running here: https://twitter.com/jeromeschneider/status/1612566775467593732
//
// I used this led panel, others might work as well! https://www.amazon.fr/gp/product/B088W62171/
//
// Pins:  Arduino             Led Panel
//        -------             ---------
//        D6                  Data in
//        Power 5V            5v in
//        Ground              Ground

const int DATA_PIN = 6;  // digital pin on the Arduino

// Declare a NeoPixel strip object with the correct number of pixels.
// In this case, the strip has 64 pixels (8 rows of 8 pixels).
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, DATA_PIN, NEO_GRB + NEO_KHZ800);

int heart[] = { 1, 2, 5, 6, 8, 11, 12, 15, 16, 23, 24, 31, 33, 38, 42, 45, 51, 52 };
int heartLen = sizeof(heart) / sizeof(heart[0]);

int eight[] = { 2, 3, 4, 5, 9, 14, 17, 22, 26, 27, 28, 29, 33, 38, 41, 46, 49, 54, 58, 59, 60, 61 };
int eightLen = sizeof(eight) / sizeof(eight[0]);

// int fusee[] = {5, 6, 7, 12, 15, 19, 21, 23, 25, 26, 30, 37, 42, 50};
int fusee[] = { 0, 1, 2, 12, 14, 15, 16, 18, 20, 25, 26, 30, 34, 39, 44, 51, 59 };
int fuseeLen = sizeof(fusee) / sizeof(fusee[0]);

int fuseeFlamme[] = { 36, 41, 42, 53, 54, 55, 56, 57 };
int fuseeFlammeLen = sizeof(fuseeFlamme) / sizeof(fuseeFlamme[0]);

int stars[][4] = {
  { 5, 9, 23, 255 },
  { 32, 46, 50, 60 },
  { 5, 9, 23, 255 },
  { 48, 62, 255, 255 },
  { 32, 46, 50, 60 },
  { 48, 62, 255, 255 },
};
int starsLen = sizeof(stars) / sizeof(stars[0]);

int oranges[][3] = {
  { 255, 255, 0 },
  { 229, 103, 23 },
  { 252, 127, 3 },
  { 255, 0, 0 },
  { 255, 0, 0 },
  { 255, 0, 0 },
};
int orangesLen = sizeof(oranges) / sizeof(oranges[0]);

void setup() {
  // Initialize the NeoPixel strip object.
  strip.begin();
  strip.setBrightness(16);
}

int frame = 0;

void loop() {
  // Clear the strip.
  strip.clear();

  switch (frame % 3) {
    case 0:
      {
        for (int i = 0; i < heartLen; i++) {
          strip.setPixelColor(heart[i], strip.Color(255, 0, 0));
        }
        strip.show();
        delay(5000);
        break;
      }
    case 1:
      {
        for (int i = 0; i < eightLen; i++) {
          strip.setPixelColor(eight[i], strip.Color(255, 255, 0));
        }
        strip.show();
        delay(5000);
        break;
      }
    case 2:
      {
        for (int f = 0; f < 50; f++) {
          strip.clear();
          for (int i = 0; i < fuseeLen; i++) {
            strip.setPixelColor(fusee[i], strip.Color(255, 0, 255));
          }

          for (int i = 0; i < fuseeFlammeLen; i++) {
            int *randomColor = oranges[map(random(1024), 0, 1023, 0, orangesLen - 1)];
            strip.setPixelColor(fuseeFlamme[i], strip.Color(randomColor[0], randomColor[1], randomColor[2]));
          }

          int *star = stars[f / 4 % starsLen];
          int starFrame = f % 4;
          if (star[starFrame] != 255) {
            strip.setPixelColor(star[starFrame], strip.Color(128, 128, 128));
          }

          strip.setPixelColor(18, strip.Color(0, 255, 255));

          strip.show();
          delay(100);
        }
        break;
      }
  }

  frame++;
}
