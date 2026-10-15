#include <math.h>
#include <time.h>

// Moon Clock - lunar phase calculation test
// Target: ESP32-S3 / Heltec Vision Master
// This version prints results to Serial Monitor.

const double SYNODIC_MONTH = 29.530588853;
const double REFERENCE_NEW_MOON = 947182440.0;
// Reference new moon: 2000-01-06 18:14 UTC

const char* phaseNames[] = {
  "New Moon",
  "Waxing Crescent",
  "First Quarter",
  "Waxing Gibbous",
  "Full Moon",
  "Waning Gibbous",
  "Last Quarter",
  "Waning Crescent"
};

void calculateMoon(time_t utc) {
  double days =
    (double)utc - REFERENCE_NEW_MOON;
  days /= 86400.0;

  double age = fmod(days, SYNODIC_MONTH);
  if (age < 0) age += SYNODIC_MONTH;

  double fraction = age / SYNODIC_MONTH;

  // Approximate illuminated fraction
  double illumination =
    50.0 * (1.0 - cos(2.0 * PI * fraction));

  int phase = (int)round(fraction * 8.0) % 8;

  Serial.println();
  Serial.println("===== MOON CLOCK =====");
  Serial.printf("Moon age: %.2f days\n", age);
  Serial.printf("Phase: %s\n", phaseNames[phase]);
  Serial.printf("Illumination: %.1f%%\n", illumination);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Start with a known UTC timestamp for testing.
  // Replace this with the current UTC time after NTP sync.
  time_t testTime = 1791979200;

  calculateMoon(testTime);
}

void loop() {
  delay(60000);
}
