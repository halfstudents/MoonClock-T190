#include <WiFi.h>
#include <time.h>
#include <math.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// ========== T190 DISPLAY ==========
#define TFT_CS    39
#define TFT_DC    47
#define TFT_RST   40
#define TFT_SCLK  38
#define TFT_MOSI  48
#define TFT_BL    17
#define TFT_VCTRL 7

SPIClass lcdSPI(HSPI);
Adafruit_ST7789 tft(&lcdSPI, TFT_CS, TFT_DC, TFT_RST);

// ========== WIFI ==========
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// India Standard Time
const long GMT_OFFSET = 19800;
const int DST_OFFSET = 0;

// ========== MOON MODEL ==========
const double SYNODIC_MONTH = 29.530588853;
const double NEW_MOON_REF = 947182440.0;

const char* PHASES[] = {
  "New Moon", "Waxing Crescent",
  "First Quarter", "Waxing Gibbous",
  "Full Moon", "Waning Gibbous",
  "Last Quarter", "Waning Crescent"
};

struct MoonInfo {
  double age;
  double illumination;
  double fraction;
  int phase;
  int nextPhase;
  double daysToNext;
};

MoonInfo calculateMoon(time_t utc) {
  MoonInfo m;

  double days = ((double)utc - NEW_MOON_REF) / 86400.0;
  m.age = fmod(days, SYNODIC_MONTH);
  if (m.age < 0) m.age += SYNODIC_MONTH;

  m.fraction = m.age / SYNODIC_MONTH;
  m.illumination =
      50.0 * (1.0 - cos(2.0 * PI * m.fraction));

  m.phase = ((int)floor(m.fraction * 8.0 + 0.5)) % 8;

  const double targets[] = {0.0, 7.3826, 14.7653, 22.1479};
  const int indices[] = {0, 2, 4, 6};

  m.daysToNext = SYNODIC_MONTH;
  m.nextPhase = 0;

  for (int i = 0; i < 4; i++) {
    double delta = targets[i] - m.age;
    if (delta <= 0) delta += SYNODIC_MONTH;

    if (delta < m.daysToNext) {
      m.daysToNext = delta;
      m.nextPhase = indices[i];
    }
  }

  return m;
}

// ========== COLOURS ==========
const uint16_t BG = 0x0861;
const uint16_t WHITE = 0xFFFF;
const uint16_t MUTED = 0x9DB5;
const uint16_t MOON_DARK = 0x4208;
const uint16_t MOON_EDGE = 0xBDF7;

// ========== ANIMATION STATE ==========
unsigned long lastFrame = 0;
unsigned long lastClockUpdate = 0;
unsigned long lastWiFiRetry = 0;

int orbitAngle = 0;
bool starsBright = false;
bool clockReady = false;

// Fixed star positions
const int STAR_X[] = {15, 43, 148, 155, 24, 132, 62, 111, 8, 160};
const int STAR_Y[] = {52, 89, 43, 113, 193, 208, 225, 77, 135, 247};

// ========== TEXT HELPER ==========
void drawCentered(const char* text, int y,
                  uint16_t colour, uint8_t size) {
  tft.setTextSize(size);
  tft.setTextColor(colour, BG);

  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(text, 0, y, &x1, &y1, &w, &h);

  tft.setCursor((170 - (int)w) / 2, y);
  tft.print(text);
}

// ========== STARS ==========
void drawStars() {
  for (int i = 0; i < 10; i++) {
    tft.drawPixel(STAR_X[i], STAR_Y[i], MUTED);
  }
}

void animateStars() {
  starsBright = !starsBright;
  uint16_t c = starsBright ? WHITE : MUTED;

  for (int i = 0; i < 10; i++) {
    tft.drawPixel(STAR_X[i], STAR_Y[i], c);
  }
}

// ========== MOON GRAPHIC ==========
void drawMoon(double fraction, int cx, int cy, int radius) {
  tft.fillCircle(cx, cy, radius + 2, 0x630C);
  tft.fillCircle(cx, cy, radius, MOON_DARK);

  double theta = 2.0 * PI * fraction;

  for (int y = -radius; y <= radius; y++) {
    for (int x = -radius; x <= radius; x++) {
      double nx = (double)x / radius;
      double ny = (double)y / radius;
      double rr = nx * nx + ny * ny;

      if (rr > 1.0) continue;

      double nz = sqrt(1.0 - rr);
      double light = nx * sin(theta) - nz * cos(theta);

      if (light >= 0.0) {
        double texture =
          0.92 + 0.08 * sin(x * 0.31) * cos(y * 0.27);

        uint8_t shade = (uint8_t)(218 * texture);

        tft.drawPixel(cx + x, cy + y,
                      tft.color565(shade, shade, shade - 5));
      }
    }
  }

  tft.drawCircle(cx, cy, radius, MOON_EDGE);
}

// ========== ANIMATED ORBIT ==========
void animateOrbit() {
  // Clear the orbit path outside the Moon, then draw a moving dot.
  orbitAngle = (orbitAngle + 3) % 360;

  float a = orbitAngle * PI / 180.0;

  int x = 85 + (int)(49 * cos(a));
  int y = 143 + (int)(49 * sin(a));

  tft.fillCircle(x, y, 2, 0xFFE0);
}

// ========== FULL SCREEN ==========
void drawClock(time_t now) {
  struct tm local;
  localtime_r(&now, &local);

  MoonInfo m = calculateMoon(now);

  char timeBuf[16];
  char dateBuf[24];
  char illumBuf[28];
  char ageBuf[24];
  char nextBuf[32];

  strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", &local);
  strftime(dateBuf, sizeof(dateBuf), "%a, %d %b %Y", &local);

  snprintf(illumBuf, sizeof(illumBuf),
           "Illumination: %.1f%%", m.illumination);

  snprintf(ageBuf, sizeof(ageBuf),
           "Moon age: %.1f days", m.age);

  snprintf(nextBuf, sizeof(nextBuf),
           "%.1f days remaining", m.daysToNext);

  tft.fillScreen(BG);
  drawStars();

  drawCentered("MOON CLOCK", 8, 0x7DFF, 2);
  tft.drawFastHLine(12, 34, 146, 0x39A7);

  drawCentered(timeBuf, 42, WHITE, 2);
  drawCentered(dateBuf, 66, MUTED, 1);

  drawMoon(m.fraction, 85, 143, 43);

  drawCentered(PHASES[m.phase], 198, 0xFFE0, 2);
  drawCentered(illumBuf, 225, WHITE, 1);
  drawCentered(ageBuf, 243, MUTED, 1);

  // Illumination progress bar
  tft.drawRect(20, 261, 130, 7, MUTED);
  int barWidth = (int)(126.0 * m.illumination / 100.0);
  if (barWidth > 0) {
    tft.fillRect(22, 263, barWidth, 3, 0xFFE0);
  }

  tft.drawFastHLine(18, 276, 134, 0x39A7);
  drawCentered("NEXT MAJOR PHASE", 282, 0x7DFF, 1);
  drawCentered(PHASES[m.nextPhase], 296, WHITE, 1);
  drawCentered(nextBuf, 309, MUTED, 1);
}

// ========== DISPLAY INITIALIZATION ==========
void initDisplay() {
  pinMode(TFT_VCTRL, OUTPUT);
  digitalWrite(TFT_VCTRL, LOW);
  delay(20);

  lcdSPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

  tft.init(170, 320);
  tft.setRotation(0);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.fillScreen(BG);
}

// ========== WIFI / TIME ==========
void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");

  unsigned long start = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - start < 20000) {
    delay(250);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi connected.");
    configTime(GMT_OFFSET, DST_OFFSET,
               "pool.ntp.org", "time.google.com");
  } else {
    Serial.println("Wi-Fi unavailable.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  initDisplay();

  drawCentered("MOON CLOCK", 120, WHITE, 2);
  drawCentered("Starting Wi-Fi...", 155, MUTED, 1);

  connectWiFi();
}

void loop() {
  unsigned long ms = millis();

  // Continuously animate stars and orbit
  if (ms - lastFrame >= 400) {
    lastFrame = ms;
    animateStars();
    animateOrbit();
  }

  // Refresh time and lunar information once per second
  if (ms - lastClockUpdate >= 1000) {
    lastClockUpdate = ms;

    time_t now = time(nullptr);

    if (now > 1700000000) {
      clockReady = true;
      drawClock(now);
    } else if (!clockReady) {
      tft.fillScreen(BG);
      drawStars();
      drawCentered("MOON CLOCK", 110, WHITE, 2);
      drawCentered("Waiting for time...", 145, MUTED, 1);
      drawCentered("Check Wi-Fi", 170, MUTED, 1);
    }
  }

  // Retry connection if Wi-Fi disconnects
  if (WiFi.status() != WL_CONNECTED &&
      ms - lastWiFiRetry >= 30000) {
    lastWiFiRetry = ms;
    connectWiFi();
  }

  delay(10);
}
