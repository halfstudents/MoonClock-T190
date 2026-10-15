#include <WiFi.h>
#include <time.h>
#include <math.h>

// -------- WIFI CONFIGURATION --------
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// India Standard Time: UTC + 5 hours 30 minutes
const long GMT_OFFSET_SECONDS = 19800;
const int DAYLIGHT_OFFSET_SECONDS = 0;

// -------- MOON CALCULATIONS --------
const double SYNODIC_MONTH = 29.530588853;

// 2000-01-06 18:14 UTC, approximate New Moon
const double REFERENCE_NEW_MOON = 947182440.0;

const char* PHASE_NAMES[] = {
  "New Moon",
  "Waxing Crescent",
  "First Quarter",
  "Waxing Gibbous",
  "Full Moon",
  "Waning Gibbous",
  "Last Quarter",
  "Waning Crescent"
};

struct MoonData {
  double age;
  double illumination;
  int phase;
  int nextPhase;
  double daysUntilNext;
};

MoonData getMoonData(time_t utc) {
  MoonData m;

  double days =
      ((double)utc - REFERENCE_NEW_MOON) / 86400.0;

  m.age = fmod(days, SYNODIC_MONTH);
  if (m.age < 0) m.age += SYNODIC_MONTH;

  double fraction = m.age / SYNODIC_MONTH;

  m.illumination =
      50.0 * (1.0 - cos(2.0 * PI * fraction));

  m.phase = ((int)floor(fraction * 8.0 + 0.5)) % 8;

  // Next major event: New Moon, First Quarter,
  // Full Moon or Last Quarter.
  const double targets[] = {
    0.0, 7.3826, 14.7653, 22.1479
  };

  double best = SYNODIC_MONTH;
  int bestIndex = 0;

  for (int i = 0; i < 4; i++) {
    double delta = targets[i] - m.age;
    if (delta <= 0.0) delta += SYNODIC_MONTH;

    if (delta < best) {
      best = delta;
      bestIndex = i;
    }
  }

  const int majorPhaseIndices[] = {0, 2, 4, 6};

  m.nextPhase = majorPhaseIndices[bestIndex];
  m.daysUntilNext = best;

  return m;
}

// -------- TIME SYNCHRONIZATION --------
bool syncClock() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");

  unsigned long start = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - start < 20000) {
    delay(300);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi connection failed.");
    return false;
  }

  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());

  configTime(
    GMT_OFFSET_SECONDS,
    DAYLIGHT_OFFSET_SECONDS,
    "pool.ntp.org",
    "time.google.com"
  );

  struct tm timeInfo;

  if (!getLocalTime(&timeInfo, 15000)) {
    Serial.println("NTP time synchronization failed.");
    return false;
  }

  Serial.println("Time synchronized.");
  return true;
}

// -------- SERIAL DISPLAY / DEBUG --------
// Replace this function's body with drawing calls
// from the working Heltec T190 TFT example.
void drawMoonClock(time_t now) {
  struct tm localTime;
  localtime_r(&now, &localTime);

  MoonData moon = getMoonData(now);

  char timeText[16];
  char dateText[24];

  strftime(timeText, sizeof(timeText),
           "%H:%M:%S", &localTime);

  strftime(dateText, sizeof(dateText),
           "%d %b %Y", &localTime);

  Serial.println("\n========== MOON CLOCK ==========");
  Serial.printf("Time: %s\n", timeText);
  Serial.printf("Date: %s\n", dateText);
  Serial.printf("Moon phase: %s\n", PHASE_NAMES[moon.phase]);
  Serial.printf("Moon age: %.2f days\n", moon.age);
  Serial.printf("Illumination: %.1f%%\n", moon.illumination);
  Serial.printf("Next major phase: %s\n",
                PHASE_NAMES[moon.nextPhase]);
  Serial.printf("Approx. days remaining: %.2f\n",
                moon.daysUntilNext);
  Serial.println("================================");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting Moon Clock...");

  if (!syncClock()) {
    Serial.println(
      "Check Wi-Fi credentials and internet access."
    );
  }
}

void loop() {
  static unsigned long lastDraw = 0;

  if (millis() - lastDraw >= 1000) {
    lastDraw = millis();

    time_t now = time(nullptr);

    // Do not calculate a phase from an invalid clock.
    if (now > 1700000000) {
      drawMoonClock(now);
    } else {
      Serial.println("Waiting for valid NTP time...");
    }
  }

  // Retry Wi-Fi/time synchronization periodically.
  static unsigned long lastRetry = 0;

  if (WiFi.status() != WL_CONNECTED &&
      millis() - lastRetry >= 30000) {
    lastRetry = millis();
    syncClock();
  }
}
