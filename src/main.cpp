#include <Arduino.h>
#include <WiFi.h>
#include <rtc.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>
#include <time.h>
#include "screen_tests.h"
#include "walk_gif.h"
#include "run_gif.h"

#define TFT_MOSI D10
#define TFT_SCK D8
#define TFT_CS D0
#define TFT_DC D1
#define TFT_RST D2

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

const int initialYear = 2024;
const int initialMonth = 9;
const int initialDay = 1;
const int initialHour = 10;
const int initialMinute = 0;
const int initialSecond = 0;

#define TFT_WIDTH 320
#define TFT_HEIGHT 240
#define LEFT_PAD 80
#define TOP_PAD 123

char previousTimeBuffer[9] = "        ";

const uint16_t *intro_frames[] = {walk_gif_0, walk_gif_1, walk_gif_2};
const int numIntroFrames = sizeof(intro_frames) / sizeof(intro_frames[0]);
const uint16_t *frames[] = {run_gif_0, run_gif_1, run_gif_2, run_gif_3};
// const uint16_t *frames[] = {cape_gif_0, cape_gif_1, cape_gif_2, cape_gif_3, cape_gif_4, cape_gif_5, cape_gif_6, cape_gif_7, cape_gif_8, cape_gif_9, cape_gif_10, cape_gif_11};
const int numFrames = sizeof(frames) / sizeof(frames[0]);
int current_frame = 0;

const char *ssid = "Samsung Galaxy S9+_9728";
const char *password = "jabe7335";

void printLocalTime()
{
  struct tm timeInfo;
  if (!getLocalTime(&timeInfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  char timeBuffer[9];
  snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d", timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);

  if (strcmp(timeBuffer, previousTimeBuffer) != 0)
  {
    for (int i = 0; i < 8; i++)
    {
      if (timeBuffer[i] != previousTimeBuffer[i])
      {
        tft.setTextColor(ST77XX_BLACK);
        tft.setCursor(LEFT_PAD + i * 18, TOP_PAD);
        tft.print(previousTimeBuffer[i]);

        // Draw new character
        tft.setTextColor(ST77XX_CYAN);
        tft.setCursor(LEFT_PAD + i * 18, TOP_PAD);
        tft.print(timeBuffer[i]);
      }
    }
    strcpy(previousTimeBuffer, timeBuffer);

    Serial.println(timeBuffer);
  }
}

void drawFrame(const uint16_t *frame, int frameWidth, int frameHeight)
{
  // Buffer to hold the frame data
  uint16_t frameBuffer[frameWidth * frameHeight];

  // Extract the frame data from PROGMEM
  for (int y = 0; y < frameHeight; y++)
  {
    for (int x = 0; x < frameWidth; x++)
    {
      int pixelIndex = y * frameWidth + x;
      frameBuffer[pixelIndex] = pgm_read_word(&frame[pixelIndex]);
    }
  }
  // tft.drawRect((TFT_WIDTH / 2) - frameWidth / 2, 150, frameWidth, frameHeight, ST77XX_BLACK);
  // Draw the frame on the display
  tft.drawRGBBitmap((TFT_WIDTH / 2) - frameWidth / 2, 150, frameBuffer, frameWidth, frameHeight); // Adjust position as needed
}

void drawSplashScreen(int index)
{
  int numFrames = 3;
  int frameWidth = 27;
  int frameHeight = 40;
  int dotMax = 4;
  tft.setCursor(100, 100);
  tft.setTextColor(ST77XX_CYAN);
  tft.print("loading");
  int x = tft.getCursorX();
  int y = tft.getCursorY();
  int frame = index % numIntroFrames;
  drawFrame(intro_frames[frame], frameWidth, frameHeight);
  if (index % 5 == 0)
  {
    int dots = (index / 5) % (dotMax + 1);
    if (dots == dotMax)
    {
      dots = 0;
      tft.fillRect(x, y - 16, dotMax * 18, 20, ST77XX_BLACK);
      tft.setCursor(x, y);
    }

    tft.setTextColor(ST77XX_CYAN);
    for (int i = 0; i < dots; i++)
    {
      tft.print(".");
    }
  }
}

void displaySplashScreen()
{
  int numFrames = 3;
  int frameWidth = 27;
  int frameHeight = 40;
  int dotMax = 4;
  int dots = 0;
  tft.setCursor(100, 100);
  tft.setTextColor(ST77XX_CYAN);
  tft.print("loading");
  int x = tft.getCursorX();
  int y = tft.getCursorY();

  for (int i = 0; i < numFrames * 100; i++)
  {
    int frame = i % numIntroFrames;
    drawFrame(intro_frames[frame], frameWidth, frameHeight);
    if (i % 5 == 0)
    {
      if (dots == dotMax)
      {
        dots = 0;
        tft.fillRect(x, y - 16, dotMax * 18, 20, ST77XX_BLACK);
        tft.setCursor(x, y);
      }

      tft.setTextColor(ST77XX_CYAN);
      tft.print(".");
      dots++;
    }
    delay(100);
  }
}

void setup()
{
  Serial.begin(115200);
  tft.initSPI(40000000, SPI_MODE0);
  tft.init(240, 320);
  tft.setRotation(2);
  tft.invertDisplay(false);
  tft.fillScreen(ST77XX_BLACK); // Clear screen
  tft.setRotation(1);
  tft.setFont(&FreeSans12pt7b);
  WiFi.begin(ssid, password);
  int index = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    drawSplashScreen(index);
    index++;
    delay(10);
  }
  Serial.println("WiFi connected");

  // Initialize time
  configTime(-14400, 0, "pool.ntp.org", "time.nist.gov");
  // struct tm tm;
  // tm.tm_year = initialYear - 1900; // Years since 1900
  // tm.tm_mon = initialMonth - 1;    // Months since January (0-11)
  // tm.tm_mday = initialDay;
  // tm.tm_hour = initialHour;
  // tm.tm_min = initialMinute;
  // tm.tm_sec = initialSecond;
  // time_t t = mktime(&tm);
  // struct timeval now = {.tv_sec = t};
  // settimeofday(&now, NULL);

  // printLocalTime();
  // displaySplashScreen();
  tft.fillScreen(ST77XX_BLACK); // Clear screen
}
void loop()
{
  printLocalTime();
  drawFrame(frames[current_frame], 27, 40);
  current_frame++;
  if (current_frame >= numFrames)
  {
    current_frame = 0;
  }
  delay(100);
}