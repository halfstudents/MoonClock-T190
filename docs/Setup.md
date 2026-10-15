# Arduino IDE setup

1. Connect the Heltec Vision Master T190 with a USB data cable.
2. Install the ESP32/Heltec board support following the [Heltec T190 guide](https://wiki.heltec.org/docs/devices/open-source-hardware/esp32-series/vision-master/vison-master-t190/). Use the exact board configuration that worked for your board, or the board selection recommended by Heltec. This package does not pin a board-core version.
3. In Library Manager install **Adafruit GFX Library** and **Adafruit ST7735 and ST7789 Library**, accepting their dependencies.
4. Open `firmware/MoonClock_T190/MoonClock_T190.ino`. Arduino requires the folder and sketch basename to match; they already do.
5. Replace `YOUR_WIFI_NAME` and `YOUR_WIFI_PASSWORD` locally. Keep those placeholders in any public GitHub copy.
6. Select the board and COM port. Verify, upload, and open Serial Monitor at **115200 baud**.
7. Allow the board to connect to Wi-Fi and obtain network time. The default time offset is **UTC+05:30 (IST)**, expressed as `GMT_OFFSET = 19800`; daylight-saving offset is zero.

## Display configuration in the final source

| Signal | GPIO |
| --- | ---: |
| TFT CS | 39 |
| TFT DC | 47 |
| TFT reset | 40 |
| SPI clock | 38 |
| SPI MOSI | 48 |
| Backlight | 17 |
| Panel power control | 7, active low |

The latest sketch uses `SPIClass lcdSPI(HSPI)`, ST7789 initialization at 170 × 320, and rotation 0. These values are inherited from the shared conversation; confirm compatibility with your hardware revision using the vendor pin map and factory example.

## Quick checks

- Blank screen: run the exact T190 vendor display example, then compare SPI pins, power control, and backlight configuration.
- Missing Adafruit header: install both display libraries and their dependencies.
- Missing terminating quotation mark: put each Wi-Fi value inside a complete pair of double quotes.
- Waiting for time: check Wi-Fi and NTP access. A valid clock is needed before lunar information is drawn.
- Do not add `LoRaWan_APP.h` or `VextON()` from unrelated examples; this project uses Wi-Fi and TFT functions.

The calculation-only example uses a fixed UTC timestamp. Its output does not advance in real time.
