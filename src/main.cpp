#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED vars
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 5
#define OLED_SCL 6
#define OLED_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// N64 Analog Pin Layout (from left to right when looking from top)
// 1 - Signal Analog Stick Left
// 2 - VCC (3.3V)
// 3 - GND
// 4 - Signal Analog Stick Right
// 5 - Signal Analog Stick Up
// 6 - Signal Analog Stick Down

// Stick vars
#define stickLeft 0
#define stickRight 1
#define stickUp 2
#define stickDown 3

volatile int valX = 0;
volatile int valY = 0;

// Helper function to clamp a value between a min and max
// This was initially used because i got some weird values from the analog stick
int clamp(int value, int minVal, int maxVal)
{
  if (value > maxVal)
    return maxVal;
  if (value < minVal)
    return minVal;
  return value;
}

void handleX()
{
  if (digitalRead(stickLeft) == digitalRead(stickRight))
  {
    valX++;
  }
  else
  {
    valX--;
  }

  valX = clamp(valX, -50, 50);
}

void handleY()
{
  if (digitalRead(stickUp) == digitalRead(stickDown))
  {
    valY++;
  }
  else
  {
    valY--;
  }

  valY = clamp(valY, -50, 50);
}

void initDisplay()
{
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
}

void drawAnalogStick(int x, int y)
{
  display.clearDisplay();

  // Draw 'calibration cross' in the middle of the screen
  display.drawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, SSD1306_WHITE);  // Vertical line
  display.drawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, SSD1306_WHITE); // Horizontal line

  // Map x and y to the screen coordinates
  int dotX = map(x, -50, 50, 0, SCREEN_WIDTH);
  int dotY = map(y, -50, 50, SCREEN_HEIGHT, 0); // Y-axis inverted for graphical display

  // Draw the dot
  display.fillCircle(dotX, dotY, 2, SSD1306_WHITE);

  // Display the X/Y values at the bottom of the screen
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, SCREEN_HEIGHT - 10); // Bottom-left corner
  display.print("X: ");
  display.print(x);
  display.print(" Y: ");
  display.println(y);

  display.display();
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  initDisplay();

  pinMode(stickLeft, INPUT);
  pinMode(stickRight, INPUT);
  pinMode(stickUp, INPUT);
  pinMode(stickDown, INPUT);

  // digitalPinToInterrupt(pin) translates a pin number into interrupt number. Pin nubers are not the same as interrupt numbers.
  // attachInterrupt() links a hardware interrupt to a function, allowing immediate response to input changes for time-sensitive tasks.
  attachInterrupt(digitalPinToInterrupt(stickLeft), handleX, CHANGE);
  attachInterrupt(digitalPinToInterrupt(stickDown), handleY, CHANGE);
}

void loop()
{
  // Update the analog stick display with X/Y values
  drawAnalogStick(valX, valY);
  delay(50); // Slight delay for smoother updates
}
