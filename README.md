# Heltec Vision Master T190 Moon Clock

An Arduino Moon Clock project for the T190's built-in colour TFT, collected from the shared project conversation for viewers and readers to reference.

The latest sketch displays Wi-Fi-synchronized time, date, a shaded lunar disc, estimated phase and illumination, a next-phase countdown, twinkling stars, and an orbiting indicator. The default time zone is India Standard Time.

## Start here

1. Follow [Arduino setup and wiring notes](docs/Setup.md).
2. Open [MoonClock_T190.ino](firmware/MoonClock_T190/MoonClock_T190.ino).
3. Enter Wi-Fi credentials locally, select your T190 board and port, and upload.
4. Read [validation status and limitations](docs/Known-Limitations.md).

## Folder contents

| Folder | Contents |
| --- | --- |
| `firmware/MoonClock_T190` | Latest complete animated sketch from the conversation |
| `examples/MoonClock_Calculation_Test` | Standalone serial-only calculation test with a fixed timestamp |
| `docs` | Setup, display correction, limitations, and both video scripts |
| `references` | Source links plus a machine-readable inventory of source and image URLs |
| `archive` | Earlier complete sketches and every unique extracted code block |

No external image files or astronomy APIs are needed to draw the Moon. Install the required graphics libraries through Arduino IDE rather than copying third-party library code into this repository.

## Upload this folder to GitHub

1. Extract the ZIP.
2. Create a new GitHub repository.
3. Choose **Add file → Upload files** and upload the **contents** of `MoonClock-T190-GitHub` so this README appears at the repository root.
4. Commit the files. Keep the Wi-Fi placeholders in the public copy.

Alternatively, with Git installed, open a terminal inside the extracted folder and run:

```bash
git init
git add .
git commit -m "Add T190 Moon Clock source and reference material"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/YOUR_REPOSITORY.git
git push -u origin main
```

Create the remote as an empty repository when using these commands. Replace the example username and repository name.

## Origin and reuse

Recovered from the original project conversation on 15 October 2026. The sketch is preserved rather than silently revised. This is a source/reference package; see the documented limits before presenting it as a tested release.

Third-party material remains under its owners' terms. No project-wide license has been chosen on the owner's behalf; add your preferred license before offering broad reuse permissions. Referenced libraries retain their own licenses.
