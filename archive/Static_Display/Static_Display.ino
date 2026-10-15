#include <WiFi.h>
#include <time.h>
#include <math.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// ========== T190 DISPLAY PINS ==========
#define TFT_MISO  -1
#define TFT_MOSI  48
#define TFT_SCLK  38
#define TFT_CS    39
#define TFT_DC    47
#define TFT_RST   40
#define TFT_BL    17
#define TFT_VCTRL 7

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

// ========== WIFI ==========
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// India Standard Time
const long GMT_OFFSET = 19800;
const int DST_OFFSET = 0;

// ========== LUNAR MODEL ==========
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

  // Next major phase in the lunar cycle
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
uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  return tft.color565(r, g, b);
}

const uint16_t BG       = 0x0861;
const uint16_t WHITE    = 0xFFFF;
const uint16_t MUTED    = 0x9DB5;
const uint16_t MOON_DARK = 0x4208;
const uint16_t MOON_LIT  = 0xDEDB;

// ========== DISPLAY HELPERS ==========
void drawStars() {
  // Fixed decorative stars
  const int sx[] = {15, 43, 148, 155, 24, 132, 62, 111, 8, 160};
  const int sy[] = {52, 89, 43, 113, 193, 208, 225, 77, 135, 247};

  for (int i = 0; i < 10; i++) {
    tft.drawPixel(sx[i], sy[i], 0xBDF7);
  }

  tft.fillCircle(29, 112, 1, WHITE);
  tft.fillCircle(143, 182, 1, WHITE);
  tft.fillCircle(45, 240, 1, WHITE);
}

// Render the lunar disc using a spherical illumination model.
// New Moon = dark; Full Moon = fully illuminated.
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

      // Visible hemisphere normal
      double nz = sqrt(1.0 - rr);

      // Direction toward the Sun as viewed from the Moon
      double light = nx * sin(theta) - nz * cos(theta);

      if (light >= 0.0) {
        // Slight surface variation for a less flat appearance
        double texture = 0.92 + 0.08 * sin(x * 0.31) * cos(y * 0.27);

        uint8_t shade = (uint8_t)(218 * texture);
        tft.drawPixel(cx + x, cy + y,
                      rgb(shade, shade, shade - 5));
      }
    }
  }

  tft.drawCircle(cx, cy, radius, 0xBDF7);
}

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

void drawClock(time_t now) {
  struct tm local;
  localtime_r(&now, &local);

  char timeBuf[16];
  char dateBuf[24];
  char illumBuf[24];
  char ageBuf[24];
  char nextBuf[32];

  strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", &local);
  strftime(dateBuf, sizeof(dateBuf), "%a, %d %b %Y", &local);

  MoonInfo m = calculateMoon(now);

  snprintf(illumBuf, sizeof(illumBuf), "Illumination %.1f%%",
           m.illumination);
  snprintf(ageBuf, sizeof(ageBuf), "Moon age %.1f days", m.age);
  snprintf(nextBuf, sizeof(nextBuf), "Next: %.1f days",
           m.daysToNext);

  tft.fillScreen(BG);
  drawStars();

  // Header
  drawCentered("MOON CLOCK", 8, 0x7DFF, 2);
  tft.drawFastHLine(12, 34, 146, 0x39A7);

  drawCentered(timeBuf, 42, WHITE, 2);
  drawCentered(dateBuf, 66, MUTED, 1);

  // Large graphical Moon
  drawMoon(m.fraction, 85, 143, 43);

  // Phase and data
  drawCentered(PHASES[m.phase], 198, 0xFFE0, 2);
  drawCentered(illumBuf, 225, WHITE, 1);
  drawCentered(ageBuf, 243, MUTED, 1);

  tft.drawFastHLine(18, 265, 134, 0x39A7);
  drawCentered("NEXT MAJOR PHASE", 274, 0x7DFF, 1);
  drawCentered(PHASES[m.nextPhase], 291, WHITE, 1);
  drawCentered(nextBuf, 307, MUTED, 1);
}

void setup() {
  Serial.begin(115200);
  delay(500);

  // Power the T190 TFT panel.
  pinMode(TFT_VCTRL, OUTPUT);
  digitalWrite(TFT_VCTRL, LOW);
  delay(20);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // Initialise SPI using the T190 pin map.
  SPI.begin(TFT_SCLK, TFT_MISO, TFT_MOSI, TFT_CS);

  tft.init(170, 320);
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);

  drawCentered("MOON CLOCK", 135, WHITE, 2);
  drawCentered("Connecting Wi-Fi", 165, WHITE, 1);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED &&
         millis() - start < 20000) {
    delay(250);
  }

  configTime(GMT_OFFSET, DST_OFFSET,
             "pool.ntp.org", "time.google.com");

  struct tm ti;
  if (WiFi.status() == WL_CONNECTED &&
      getLocalTime(&ti, 15000)) {
    Serial.println("NTP time synchronized.");
  } else {
    Serial.println("Wi-Fi/NTP unavailable; waiting for time.");
  }
}

void loop() {
  static unsigned long lastDraw = 0;

  if (millis() - lastDraw >= 60000) {
    lastDraw = millis();

    time_t now = time(nullptr);
    if (now > 1700000000) {
      drawClock(now);
    } else {
      tft.fillScreen(BG);
      drawCentered("MOON CLOCK", 100, WHITE, 2);
      drawCentered("Waiting for NTP time", 145, MUTED, 1);
      drawCentered("Check Wi-Fi", 170, MUTED, 1);
    }
  }

  delay(50);
}
