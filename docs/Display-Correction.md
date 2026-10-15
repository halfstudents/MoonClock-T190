## Important correction for your T190

I verified the board-specific display example information. The T190 uses an ST7789 colour TFT at 170 × 320 pixels, and Heltec's factory-test example initializes it with a dedicated `HSPI` bus and `Adafruit_ST7789` instance. 

That means the earlier sketch needs one important adjustment: **initialize the display using Heltec's `HSPI` configuration**, rather than relying on the default SPI bus.

## 1. Corrected display initialization

In your sketch, replace the previous display object and `setup()` display initialization with this T190-specific setup:

```cpp

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS   39
#define TFT_DC   47
#define TFT_RST  40
#define TFT_SCLK 38
#define TFT_MOSI 48

SPIClass lcdSPI(HSPI);
Adafruit_ST7789 tft(&lcdSPI, TFT_CS, TFT_DC, TFT_RST);

void initT190Display() {
  lcdSPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

  // T190 panel power is active-low on the
  // documented configuration used by this example.
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  delay(20);

  tft.init(170, 320);
  tft.setRotation(0);

  // Enable the TFT backlight after initialization.
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 20);
  tft.println("MOON CLOCK");
}
```

This uses the dedicated SPI instance and pins shown in the T190 factory-test implementation. 

**Important:** this is a replacement for the display initialization, not a second complete sketch. Keep only one `setup()` and one `loop()` in your project.

## 2. Finish the integration

Keep the lunar calculation and Wi-Fi/NTP functions from the previous sketch. In `setup()`, call `initT190Display()` before connecting to Wi-Fi. In `loop()`, call `drawClock(time(nullptr))` once a minute after the time is valid.

To make the graphical Moon look right, retain the `drawMoon()` function from the previous sketch. It renders the illuminated portion locally, so you don't need an API key or internet image service for the Moon itself.

For reliable operation, first verify the display with the T190 factory test, then upload the integrated Moon Clock. The official board documentation is available here: [Vision Master T190 documentation](https://wiki.heltec.org/docs/devices/open-source-hardware/esp32-series/vision-master/vison-master-t190/).
