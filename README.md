# EQX — ESP32 Hardware Remote for Sonos®

EQX is an open-source, dedicated physical remote control for Sonos® sound systems built on an ESP32 microcontroller. It connects directly over your local Wi-Fi network using UPnP/SOAP to provide immediate tactile volume, playback, and multi-band EQ control without cloud APIs or mobile app latency.

> **Disclaimer:** Sonos® is a registered trademark of Sonos, Inc. This is an independent DIY project and is not affiliated with, endorsed by, or sponsored by Sonos, Inc.

## Key Features

- **100% Local UPnP Control:** Operates directly over port 1400 with automatic SSDP discovery. Zero cloud tokens, zero developer accounts, zero external dependencies.
- **Ultra-Low Latency:** Point-to-point Wi-Fi communication with ~30–50 ms round-trip response times for continuous rotary turns.
- **Multi-Band Hardware Controls:** EC11 rotary encoders controlling Volume (with push-to-mute), Bass, Subwoofer Gain (with dynamic sub-detection), and Treble/Zone Menu.
- **Automatic Speaker Discovery:** Two-phase SSDP + SOAP scan that finds every Sonos zone on the network, filters out satellites/subs, and lets you switch the active zone from an on-device menu.
- **OLED Display:** Real-time feedback for active volume, Wi-Fi signal percentage, battery percentage, track playback icons, and EQ levels.
- **Battery Monitoring:** ESP32 ADC calibration with a resistive divider and exponential smoothing for a stable battery percentage reading.
- **Power Saving:** Automatic screen timeout and deep-sleep standby with RTC wake-up via the volume encoder button.
- **Self-Healing Connection:** Automatic Wi-Fi reconnection and exponential backoff retry logic if the selected Sonos speaker goes offline.
- **Custom 3D Enclosure:** Parametric CAD case designed in OpenSCAD with heat-set threaded inserts and a debossed "EQX" front logo.

## Hardware Components

- **Microcontroller:** ESP32-WROOM-32 DevKit v1
- **Display:** 0.96" I2C OLED (SSD1306, 128x64)
- **Dials:** 4x EC11 continuous rotary encoders with push buttons
- **Charging & Power:** TP4056 USB-C module + LiPo battery
- **Battery Sensing:** 10k/10k resistive voltage divider into ADC pin
- **Power Management:** Deep sleep standby with RTC wake-up support

## Hardware Architecture & Pinout

| Subsystem / Function | Pin(s) on ESP32 | Notes |
| :--- | :--- | :--- |
| **OLED Display (I2C)** | SDA: 21, SCL: 22 | SSD1306 (128x64), bus @ 400 kHz |
| **Battery ADC** | GPIO 34 | 10k/10k divider to VBAT (input-only pin) |
| **Volume Encoder (A/B/SW)** | 32 / 33 / 25 | SW is RTC GPIO (deep-sleep wake-up trigger) |
| **Bass Encoder (A/B/SW)** | 14 / 27 / 26 | Internal pull-up enabled |
| **Sub Gain Encoder (A/B/SW)** | 4 / 5 / 13 | Internal pull-up enabled |
| **Treble Encoder (A/B/SW)** | 18 / 19 / 23 | Internal pull-up enabled |
| **Charging & Power** | TP4056 USB-C | Micro-USB + USB-C dual access |

## Getting Started

### Prerequisites

- [PlatformIO](https://platformio.org/) (VS Code extension or CLI)
- ESP32-WROOM-32 DevKit
- The following libraries (installed automatically via PlatformIO): `Adafruit GFX`, `Adafruit SSD1306`

### Configuration

Create an `include/secrets.h` file with your network credentials (this file is already excluded via `.gitignore`, so it will never be committed):

```cpp
#pragma once

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
```

Then in `src/main.cpp`, include it and set your default Sonos zone:

```cpp
#include "secrets.h"

const char* SONOS_NAME = "Living Room"; // Default zone selected on boot
```

> ⚠️ Never commit real Wi-Fi credentials directly inside `main.cpp`. Keep them only in `secrets.h`.

If your battery divider reads slightly off from your multimeter, adjust `FACTOR_DIVISOR` in `main.cpp` accordingly (default `2.00` for a 10k/10k divider).

### Build & Upload

```bash
pio run --target upload
pio device monitor
```

## Controls & Navigation

- **Volume Dial (Top Left):** Rotate to adjust volume (0–100). Click to toggle mute/unmute.
- **Bass Dial:** Rotate to adjust bass (-10 to +10). Click to skip to the next track.
- **Sub Gain Dial:** Rotate to adjust subwoofer gain (-15 to +15, only active if a sub is detected on the current zone). Click to go to the previous track.
- **Treble Dial:** Rotate to adjust treble (-10 to +10).
  - **Short click:** open the zone selection menu to switch between discovered Sonos speakers (sorted alphabetically).
  - **Long press (~1.2s):** open the system menu (rescan network / return to control).

## Project Structure

```text
EQX/
├── hardware/      # OpenSCAD 3D models and STL export files
├── include/       # Firmware headers
├── src/           # Firmware C++ source code (main.cpp)
├── platformio.ini # PlatformIO environment configuration
├── .gitignore
├── LICENSE
└── README.md
```

## Roadmap

- [ ] Split `main.cpp` into modular files (Wi-Fi, Sonos/SOAP, OLED UI, encoders, power management)
- [ ] Move Wi-Fi credentials into a gitignored `secrets.h`
- [ ] Publish 3D-printable enclosure files under `hardware/`

## License

This project is licensed under the **PolyForm Noncommercial License 1.0.0** — see the [LICENSE](./LICENSE) file for full terms.

- **Permitted:** inspecting, downloading, modifying, 3D-printing, and building this project for personal, noncommercial use.
- **Prohibited:** commercial use, including selling assembled units, kits, printed parts, or offering paid services derived from this repository, without prior written permission from the author.
