# YouTube video script: Building a Moon Phase Clock with the Heltec Vision Master T190



(5-minute video) (Unboxing + Tutorial) (Arduino IDE)

Format: on-camera introduction, unboxing, screen recording, coding walkthrough, and final demo.

Here is a ready-to-record script with timestamps, what to show on camera, what to say, and on-screen text. The narration is designed to sound natural rather than like reading a technical manual.

## Scene 1 — Hook and introduction (0:00–0:25)



Camera shot

Show the board in your hand, then cut quickly to the finished Moon Clock running on its screen. Add a close-up of the animated Moon.

On-screen title: “I Built a Moon Phase Clock!”

:::writing{variant="standard" id="61301"}
Hey everyone, welcome back to the channel!

Today, I'm going to turn this little Heltec Vision Master T190 into something really cool — a Moon Phase Clock!

It will display the current time, the Moon's current phase, its illumination percentage, and the next major lunar phase. And we'll even add some animation to make the display look more alive.

I'll take you through everything, from unboxing the board and exploring its documentation to setting up Arduino IDE, installing the libraries, uploading the code, and seeing the final result.

So, let's get started!
:::

## Scene 2 — Unboxing and board features (0:25–1:00)



Camera shot

Open the packaging, remove the board, show the display, USB port, PCB, buttons, and any included accessories. Use close-up shots and good lighting.

On-screen text: “ESP32-S3 · Colour TFT · Wi-Fi”

:::writing{variant="standard" id="61302"}
Here we have the Heltec Vision Master T190.

Let's open the packaging and take a closer look at what we get.

The first thing you'll notice is the built-in colour display. This makes it perfect for projects where we want to show information and graphics without connecting a separate screen.

The board is based on the ESP32-S3, which gives us processing power and Wi-Fi connectivity.

That means we can synchronize the time over the internet and use the display to show our Moon phase information.

For this project, we don't need any additional display or RTC module. We'll start with the board, a USB data cable, and our computer.
:::

## Scene 3 — Finding the idea in the documentation (1:00–1:35)



Screen recording

Open the [official T190 documentation](https://wiki.heltec.org/docs/devices/open-source-hardware/esp32-series/vision-master/vison-master-t190/). Show the specifications, display information, pin map, and example code.

On-screen text: “Read the documentation first”

:::writing{variant="standard" id="61303"}
Before writing any code, I wanted to understand the board properly.

So, I opened the official Heltec documentation and checked the specifications, display configuration, pin mapping, and available examples.

This step is important because different development boards can use different display controllers and pin configurations.

Once I understood how the T190's display is initialized, I had an idea: why not use this screen to build a small astronomy clock?

Instead of displaying only the time, we can calculate the Moon's phase using the current date and visualize the illuminated part of the Moon.

And that's the idea behind this project!
:::

## Scene 4 — Connecting the board and setting up Arduino IDE (1:35–2:15)



Camera + screen recording

Connect the board to your computer with a USB data cable. Show Arduino IDE, Boards Manager, board selection, and serial port.

On-screen text: “USB → Arduino IDE → ESP32-S3”

:::writing{variant="standard" id="61304"}
Now let's connect the board to our computer using a USB data cable.

I'm using Arduino IDE to program the T190.

First, we need to install the correct ESP32 board support and select the board configuration recommended by Heltec.

Then, we select the correct serial port.

Before uploading our own program, it's always a good idea to run the manufacturer's display example. This confirms that the computer can communicate with the board and that the screen works correctly.

Once that test is successful, we're ready to move on to our Moon Clock code.
:::

## Scene 5 — Installing libraries and configuring the code (2:15–3:05)



Screen recording

Show Library Manager, install the graphics libraries, and open the complete Moon Clock sketch.

On-screen text: “Adafruit GFX + ST7789”

:::writing{variant="standard" id="61305"}
Next, let's install the libraries required for the display.

I'm using the Adafruit GFX Library and the Adafruit ST7735 and ST7789 Library.

These provide the graphics and drawing functions used by our Moon Clock.

Now we can open the sketch.

At the top, we enter our Wi-Fi network name and password. The board uses Wi-Fi to get the current time through an NTP time server.

I'm also setting the time zone to Indian Standard Time. If you're in another country, you can change the UTC offset accordingly.

The program calculates the Moon's age using an approximate lunar cycle of 29.53 days. From that, it estimates the phase and the illuminated percentage.

Finally, the drawing functions create the Moon graphic and display the next major lunar phase.

One important thing: the display initialization must match the T190, so we use the configuration verified against its own documentation and display example.
:::

## Scene 6 — Uploading and testing the Moon Clock (3:05–4:10)



Screen recording + board close-up

Click Verify, show successful compilation, upload the sketch, and open Serial Monitor at 115200 baud.

On-screen text: “Compile ✓ Upload ✓ Wi-Fi ✓”

:::writing{variant="standard" id="61306"}
Now it's time to upload the code.

First, I'll click Verify to check for compilation errors.

As you can see, the sketch compiles successfully. Next, I'll upload it to the board.

Once the upload finishes, we can open the Serial Monitor at 115200 baud and check whether the board connects to Wi-Fi and synchronizes the time.

After the time is available, the Moon Clock can calculate the current lunar phase and illumination.

Let's take a look at the display.

We now have the digital clock, the date, the Moon illustration, the phase name, and the illumination percentage. The display also shows an estimate of the time remaining until the next major lunar phase.

The animated stars and orbiting indicator make the interface feel more dynamic.

The actual lunar phase changes gradually, of course, so the animation represents the Moon rather than making its real phase change artificially every second.
:::

## Scene 7 — Final result and outro (4:10–5:00)



Beauty shots

Show the working display in a darker environment. Record a close-up of the Moon, the time, and the animation. Add a brief montage of the unboxing and code.

On-screen text: “Project complete · Moon Clock”

:::writing{variant="standard" id="61307"}
And that's it! We've turned the Heltec Vision Master T190 into a Moon Phase Clock using Arduino IDE, Wi-Fi time synchronization, and a little bit of astronomy.

I really like how a small development board can become a useful and visually interesting project with just a few lines of code and some creativity.

There are plenty of ways we can improve it in the future, such as adding touch controls, a lunar calendar, more accurate astronomical calculations, or even different display themes.

If you enjoyed this build, give the video a thumbs up, subscribe to the channel, and let me know in the comments what project you'd like to see next.

Thanks for watching, and I'll see you in the next one!
:::

---

## Recording checklist

## Before you publish

of

## Suggested YouTube title and thumbnail



Title

:::writing{variant="standard" id="61308"}
I Built a Moon Phase Clock with the Heltec Vision Master T190! 🌙 | ESP32 + Arduino
:::

Thumbnail text

:::writing{variant="standard" id="61309"}
I BUILT A MOON CLOCK!
:::

Editing tip: use quick cuts during unboxing, zoom in on the display initialization in the code, and leave the final working Moon Clock on screen for a few seconds so viewers can appreciate the result.
