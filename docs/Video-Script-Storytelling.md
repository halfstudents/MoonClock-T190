Here’s a more natural, **storytelling-style YouTube script** built around your actual experience: you receive a new Heltec board, unbox it, explore the documentation, decide to test it by building a Moon Phase Clock, and then demonstrate the display and Wi-Fi working. The tone is professional, engaging, and to the point, with a target length of about five minutes.



# YouTube Video Script: From Unboxing to a Working Moon Phase Clock

Target duration: 5 minutes · Style: Hands-on tech project · Tone: Professional storytelling

## Scene 1 — The beginning: a new board (0:00–0:25)

**Visuals:** Show the sealed package, rotate it to show the packaging, then open it and carefully take out the board. Use close-up shots.

:::writing{variant="standard" id="62481"}
“Today, I have a new development board to try out — the Heltec Vision Master T190.

Instead of just going through its specifications, I wanted to explore what it can actually do. So, in this video, I’ll unbox the board, go through its documentation, and use a simple project to test its display, Wi-Fi, and overall functionality.

Let’s open it up and get started.”
:::

## Scene 2 — Unboxing and first impressions (0:25–1:00)

**Visuals:** Take out the board, show it from the front and back, zoom in on the screen and connectors, and place it neatly on your desk.

:::writing{variant="standard" id="62482"}
“Here’s the Heltec Vision Master T190.

My first impression is the compact design and the integrated colour display. Having a screen built directly into a development board makes it especially interesting for projects involving clocks, dashboards, and small information displays.

It also has an ESP32-S3 microcontroller with Wi-Fi connectivity, which means we can do more than just display graphics — we can also build projects that use network data.

But before starting the project, I wanted to understand the board properly, so the next step was to check the official documentation.”
:::

## Scene 3 — Exploring the documentation (1:00–1:35)

**Visuals:** Record your screen while opening the official Heltec documentation. Scroll through the board overview, specifications, display details, and any relevant examples.

:::writing{variant="standard" id="62483"}
“Whenever I work with a new development board, I like to start with the official documentation. It helps me understand the hardware, identify the correct setup, and avoid guessing which settings or connections to use.

While exploring the documentation, I decided that a Moon Phase Clock would be a good first project. It would let me test the display with real graphics, show useful information on the screen, and use Wi-Fi to obtain the current time.

So, rather than testing only a basic text example, I chose a project that could demonstrate several features of the board in one go.”
:::

On screen: show the documentation URL briefly, then highlight the board specifications and the Moon Phase Clock code or example you used. If the clock was your own implementation inspired by the documentation, describe it that way rather than calling it an official example.

## Scene 4 — Connecting the board and setting up Arduino IDE (1:35–2:15)

**Visuals:** Connect the board to your computer using USB. Open Arduino IDE and show the code editor and board-selection settings.

:::writing{variant="standard" id="62484"}
“Now it’s time to connect the board to the computer.

I’ve connected it through USB, and I’m using the Arduino IDE to prepare and upload the program.

The first step is to make sure the appropriate ESP32 board support is installed and that the correct board and port are selected. These settings are important because the IDE needs to know which hardware it’s compiling the program for.

Once that’s ready, we can move on to the libraries and the clock code.”
:::

## Scene 5 — Installing libraries and configuring the clock (2:15–3:10)

**Visuals:** Open Library Manager, search for and install the required libraries, then show the sketch. Zoom in on the Wi-Fi settings and time configuration without showing your actual password.

:::writing{variant="standard" id="62485"}
“Since this project uses a colour display, I installed the required display libraries — Adafruit GFX and Adafruit ST7735 and ST7789.

Next, I opened the Moon Phase Clock sketch and configured the Wi-Fi credentials so the board could connect to my network. I also checked the time-zone setting for India, so the clock would display local time.

The program combines the current time with a calculation of the Moon’s phase and illumination. That information is then drawn on the display.

With the libraries installed and the settings configured, everything is ready for the first upload.”
:::

**Editing tip:** Show the code briefly, but don’t spend too long scrolling through it. Viewers mainly need to see the important settings and understand what they do.

## Scene 6 — Uploading and testing (3:10–4:10)

**Visuals:** Click Verify, then Upload. Show the compilation progress, upload messages, and the board restarting. Cut to the display as the clock appears.

:::writing{variant="standard" id="62486"}
“Now I’m verifying the code and uploading it to the board.

The IDE compiles the program first, then transfers it over USB. Once the upload is complete, the board restarts and begins running the clock.

And there we go — the Moon Phase Clock is running!

We can see the time, date, Moon graphic, and the current phase information on the display. This is exactly why I wanted to test the board with a practical project: it gives us a much better idea of how the screen performs than simply looking at the specifications.

I’m also checking that the board connects to Wi-Fi and that the time updates correctly. These are important checks for a clock that relies on network time.”
:::

**Visuals to capture:**

- A clear, close-up shot of the full display.
- The Moon graphic and phase information.
- The clock running for a few seconds.
- The successful Wi-Fi connection, if shown in your Serial Monitor.
- A wider shot showing the board connected to your computer.

## Scene 7 — Final impressions and outro (4:10–5:00)

**Visuals:** Show the finished clock from different angles. Hold the board steady, then end with a clean shot of the display.

:::writing{variant="standard" id="62487"}
“So, that was my first test of the Heltec Vision Master T190 — from unboxing the board to getting a working Moon Phase Clock running on it.

The integrated colour display makes it a great platform to experiment with visual projects, while the ESP32-S3 and Wi-Fi give it plenty of potential for connected applications.

Most importantly, this project helped me go through the complete workflow: reading the documentation, setting up Arduino IDE, installing the libraries, configuring the code, and uploading it to the hardware.

This is just the beginning. There are plenty of other projects we can explore with this board, and I’m looking forward to trying them out.

If you enjoyed this video, consider liking it and subscribing for more electronics and development-board projects. Thanks for watching!”
:::

---

## Before you record

- [ ] Film the unopened package before removing anything.
- [ ] Get close-up shots of the board, screen, ports, and connectors.
- [ ] Record the official documentation on your computer.
- [ ] Capture the Arduino IDE setup, library installation, and upload process.
- [ ] **Hide your Wi-Fi password** and any personal network details on camera.
- [ ] Record the final display in good lighting, with minimal reflections.
- [ ] If possible, capture the Serial Monitor showing a successful Wi-Fi connection.

**Suggested video title:** *I Built a Moon Phase Clock with the Heltec Vision Master T190! 🌙*

**Thumbnail text:** `UNBOX → CODE → MOON CLOCK`

**One storytelling tip:** Don’t make the video feel like a tutorial from the very first second. Let the audience follow your process: *new board → exploring the documentation → choosing a project → uploading the code → seeing the result.* That gives the video a clear beginning, middle, and payoff without sacrificing the technical details.

---

If you want, I can:

- Summarize this conversation
- Create a concise storyboard for the YouTube video
- Explain key features of the Heltec Vision Master T190 board
