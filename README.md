# N64 Analog Stick to ESP32

This project is a simple way to connect an N64 controller to an ESP32 and read the analog stick values. The N64 controller uses a 3.3V supply voltage, so it can be connected directly to the ESP32.

## Software
I used platformio to build and upload the code to the ESP32. You can use the Arduino IDE if you prefer. This project contains the platformio.ini for my setup.

## Hardware
- Any ESP32 board that has enough GPIO pins and can output 3.3V. I used an ESP32-3C.
- An Analog Stick from an N64 controller. I used an old semi broken stick i had laying around.
- An OLED display (optional). I guess you could use a serial monitor instead, but the OLED is more fun.

## Wiring
- Connect the 3.3V from the ESP32 to the 3.3V on the N64 controller.
- Connect the GND from the ESP32 to the GND on the N64 controller.
- Connect the 4 data pins from the N64 controller to any GPIO pins on the ESP32. I used GPIO 0, 1, 2 and 3.

## N64 Analog Stick Wiring
From left to right when looking from the top.

| Pin    | Description                  |
| -------| ---------------------------- |
| 1      | Signal Analog Stick Left     |
| 2      | VCC (3.3V)                   |
| 3      | GND                          |
| 4      | Signal Analog Stick Right    |
| 5      | Signal Analog Stick Up       |
| 6      | Signal Analog Stick Down     |

## Result
![Gif of finished project](https://i.ibb.co/5Fxrjv6/n64analog.gif)