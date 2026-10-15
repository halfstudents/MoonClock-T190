# Validation and known limitations

The firmware is packaged from the shared conversation without functional changes. It has not been compiled against a pinned ESP32 core or tested on hardware as part of this packaging task. The conversation reports that an earlier static version was working; that does not establish that the later animated sketch was hardware-tested.

- Full-screen redraw every second may cause flicker and briefly erase animation.
- `animateOrbit()` draws a new dot without erasing the previous dot; the next full redraw clears the accumulated marks.
- Some long phase names at text size 2 exceed the 170-pixel display width.
- Wi-Fi reconnect attempts can block animation for up to approximately 20 seconds.
- NTP initialization occurs only after a successful connection. If the first NTP attempt fails while Wi-Fi stays connected, the code has no explicit periodic NTP restart path.
- The fixed 29.530588853-day mean lunar cycle is an educational approximation. Illumination and next-phase countdown are estimates, not precision ephemeris predictions.
- The real lunar phase changes over days. Twinkling stars and the orbit dot are decorative animation.
- Exact board package and library versions were not supplied in the conversation.

See `Display-Correction.md` before using an earlier archived display example.
