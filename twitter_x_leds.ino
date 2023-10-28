#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 102
#define PIN 8
#define DELAY_MS 25
#define ARM_LEN 30

int sw_ne__[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};
int nw_se_l[] = {67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38};
int nw_se_r[] = {73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
int ne_sw__[] = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
int se_nw_l[] = {38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67};
int se_nw_r[] = {33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}

void loop() {
  wipeRight(true);
  wipeRight(false);
  wipeDown(true);
  wipeDown(false);
  wipeLeft(true);
  wipeLeft(false);
  wipeUp(true);
  wipeUp(false);
  wipeOut(true);
  wipeOut(false);
  wipeOut(true);
  wipeOut(false);
  wipeOut(true);
  wipeOut(false);
  broadway(1, 4);
  broadway(-1, 4);
  broadway(1, 3);
  broadway(-1, 3);
  fadeInOut(2);
  fadeInOut(2);
  fadeInOut(1);
  fadeInOut(1);
  fadeInOut(1);
}

void fadeInOut(int speed) {
  for (int intensity = 0; intensity < 10; intensity++) {
    stepFade(intensity, speed);
  }
  for (int intensity = 10; intensity >= 0; intensity--) {
    stepFade(intensity, speed);
  }
}

void stepFade(int intensity, int speed) {
  for (int i = 0; i < ARM_LEN; i++) {
    pixels.setPixelColor(sw_ne__[i], pixels.Color(intensity, intensity, intensity));
    pixels.setPixelColor(nw_se_l[i], pixels.Color(intensity, intensity, intensity));
    pixels.setPixelColor(nw_se_r[i], pixels.Color(intensity, intensity, intensity));
  }
  pixels.show();
  delay(DELAY_MS * speed);
}

void broadway(int cw, int speed) {
  for (int repeat = 0; repeat < 5; repeat++) {
      for (int i = 0; i < 3; i++) {
        clear();
        for (int j = 0; j < 10; j++) {
          stepWipe(sw_ne__[3 * j + (pseudoMod3(i * cw))], true);
          stepWipe(se_nw_l[3 * j + (pseudoMod3(i * cw))], true);
          stepWipe(nw_se_r[3 * j + (pseudoMod3(i * cw))], true);
        }
        pixels.show();
        delay(DELAY_MS * speed);
    }
  }
  clear();
}

int pseudoMod3(int i) {
  if (i < 0) {
    i += 3;
  }
  return i;
}

void wipeRight(bool toOn) {
  for (int i = 0; i < ARM_LEN; i++) {
    stepWipe(sw_ne__[i], toOn);
    stepWipe(nw_se_l[i], toOn);
    stepWipe(nw_se_r[i], toOn);
    endStepWipe();
  }
}

void wipeDown(bool toOn) {
  for (int i = 0; i < ARM_LEN; i++) {
    stepWipe(ne_sw__[i], toOn);
    stepWipe(nw_se_l[i], toOn);
    stepWipe(nw_se_r[i], toOn);
    endStepWipe();
  }
}

void wipeLeft(bool toOn) {
  for (int i = 0; i < ARM_LEN; i++) {
    stepWipe(ne_sw__[i], toOn);
    stepWipe(se_nw_l[i], toOn);
    stepWipe(se_nw_r[i], toOn);
    endStepWipe();
  }
}

void wipeUp(bool toOn) {
  for (int i = 0; i < ARM_LEN; i++) {
    stepWipe(sw_ne__[i], toOn);
    stepWipe(se_nw_l[i], toOn);
    stepWipe(se_nw_r[i], toOn);
    endStepWipe();
  }
}

void wipeOut(bool toOn) {
  for (int i = 0; i < ARM_LEN / 2; i++) {
    stepWipe(sw_ne__[ARM_LEN / 2 + i], toOn);
    stepWipe(se_nw_l[ARM_LEN / 2 + i], toOn);
    stepWipe(se_nw_r[ARM_LEN / 2 + i], toOn);
    stepWipe(sw_ne__[ARM_LEN / 2 - 1 - i], toOn);
    stepWipe(se_nw_l[ARM_LEN / 2 - 1 - i], toOn);
    stepWipe(se_nw_r[ARM_LEN / 2 - 1 - i], toOn);
    endStepWipe();
  }
}

void stepWipe(int i, bool toOn) {
  if (toOn) {
    pixels.setPixelColor(i, pixels.Color(10, 10, 10));
  } else {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void clear() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void endStepWipe() {
  pixels.show();
  delay(DELAY_MS);
}
