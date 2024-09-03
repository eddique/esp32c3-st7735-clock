#include "screen_tests.h"

void chatTest(Adafruit_ST7789 tft)
{
    const char *conversation[] = {
        "Hi ChatGPT!",
        "Hello! How can I assist you today?",
        "I was wondering how to create a scrolling text effect on a TFT screen.",
        "That's a great question! Do you have any specific requirements for the scrolling effect?",
        "I'd like the text to scroll smoothly from bottom to top.",
        "Got it. I can help you with that. Do you have any sample text you want to scroll?",
        "Yes, let's use a simple conversation for the scrolling text.",
        "Sounds good! Let's start with a basic example and build from there."};
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(5, 5);

    for (int i = 0; i < 8; i++)
    {
        const char *role = i % 2 == 0 ? "User:" : "ChatGPT:";
        const uint16_t color = i % 2 == 0 ? ST77XX_MAGENTA : ST77XX_CYAN;
        tft.setCursor(5, tft.getCursorY());
        tft.setTextColor(color);

        for (int j = 0; j < strlen(role); j++)
        {
            tft.print(role[j]);
            delay(10);
        }

        tft.setTextColor(ST77XX_WHITE);
        size_t text_len = strlen(conversation[i]);
        for (int j = 0; j < text_len; j++)
        {
            if (tft.getCursorX() == 0)
            {
                tft.setCursor(5, tft.getCursorY());
            }
            tft.print(conversation[i][j]);
            delay(10);
        }
        tft.println("\n");
        delay(2000);
    }
}

void testlines(Adafruit_ST7789 tft, uint16_t color)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawLine(0, 0, x, tft.height() - 1, color);
        delay(0);
    }
    for (int16_t y = 0; y < tft.height(); y += 6)
    {
        tft.drawLine(0, 0, tft.width() - 1, y, color);
        delay(0);
    }

    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
        delay(0);
    }
    for (int16_t y = 0; y < tft.height(); y += 6)
    {
        tft.drawLine(tft.width() - 1, 0, 0, y, color);
        delay(0);
    }

    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawLine(0, tft.height() - 1, x, 0, color);
        delay(0);
    }
    for (int16_t y = 0; y < tft.height(); y += 6)
    {
        tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
        delay(0);
    }

    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
        delay(0);
    }
    for (int16_t y = 0; y < tft.height(); y += 6)
    {
        tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
        delay(0);
    }
}

void testdrawtext(Adafruit_ST7789 tft, const char *text, uint16_t color)
{
    tft.setCursor(0, 0);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}

void testfastlines(Adafruit_ST7789 tft, uint16_t color1, uint16_t color2)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int16_t y = 0; y < tft.height(); y += 5)
    {
        tft.drawFastHLine(0, y, tft.width(), color1);
    }
    for (int16_t x = 0; x < tft.width(); x += 5)
    {
        tft.drawFastVLine(x, 0, tft.height(), color2);
    }
}

void testdrawrects(Adafruit_ST7789 tft, uint16_t color)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
    }
}

void testfillrects(Adafruit_ST7789 tft, uint16_t color1, uint16_t color2)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x = tft.width() - 1; x > 6; x -= 6)
    {
        tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
        tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
    }
}

void testfillcircles(Adafruit_ST7789 tft, uint8_t radius, uint16_t color)
{
    for (int16_t x = radius; x < tft.width(); x += radius * 2)
    {
        for (int16_t y = radius; y < tft.height(); y += radius * 2)
        {
            tft.fillCircle(x, y, radius, color);
        }
    }
}

void testdrawcircles(Adafruit_ST7789 tft, uint8_t radius, uint16_t color)
{
    for (int16_t x = 0; x < tft.width() + radius; x += radius * 2)
    {
        for (int16_t y = 0; y < tft.height() + radius; y += radius * 2)
        {
            tft.drawCircle(x, y, radius, color);
        }
    }
}

void testtriangles(Adafruit_ST7789 tft)
{
    tft.fillScreen(ST77XX_BLACK);
    uint16_t color = 0xF800;
    int t;
    int w = tft.width() / 2;
    int x = tft.height() - 1;
    int y = 0;
    int z = tft.width();
    for (t = 0; t <= 15; t++)
    {
        tft.drawTriangle(w, y, y, x, z, x, color);
        x -= 4;
        y += 4;
        z -= 4;
        color += 100;
    }
}

void testroundrects(Adafruit_ST7789 tft)
{
    tft.fillScreen(ST77XX_BLACK);
    uint16_t color = 100;
    int i;
    int t;
    for (t = 0; t <= 4; t += 1)
    {
        int x = 0;
        int y = 0;
        int w = tft.width() - 2;
        int h = tft.height() - 2;
        for (i = 0; i <= 16; i += 1)
        {
            tft.drawRoundRect(x, y, w, h, 5, color);
            x += 2;
            y += 3;
            w -= 4;
            h -= 6;
            color += 1100;
        }
        color += 100;
    }
}

void tftScreenTest(Adafruit_ST7789 tft)
{
    tft.fillScreen(ST77XX_BLACK);
    tft.fillScreen(ST77XX_BLUE);
    tft.fillScreen(ST77XX_CYAN);
    tft.fillScreen(ST77XX_GREEN);
    tft.fillScreen(ST77XX_MAGENTA);
    tft.fillScreen(ST77XX_ORANGE);
    tft.fillScreen(ST77XX_RED);
    tft.fillScreen(ST77XX_WHITE);
    tft.fillScreen(ST77XX_YELLOW);
}

void tftPrintTest(Adafruit_ST7789 tft)
{
    float p = 3.1415926;

    tft.setTextWrap(false);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 30);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(1);
    tft.println("Hello World!");
    tft.setTextColor(ST77XX_YELLOW);
    tft.setTextSize(2);
    tft.println("Hello World!");
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.println("Hello World!");
    tft.setTextColor(ST77XX_BLUE);
    tft.setTextSize(4);
    tft.print(1234.567);
    delay(1500);
    tft.setCursor(0, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(0);
    tft.println("Hello World!");
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_GREEN);
    tft.print(p, 6);
    tft.println(" Want pi?");
    tft.println(" ");
    tft.print(8675309, HEX); // print 8,675,309 out in HEX!
    tft.println(" Print HEX!");
    tft.println(" ");
    tft.setTextColor(ST77XX_WHITE);
    tft.println("Sketch has been");
    tft.println("running for: ");
    tft.setTextColor(ST77XX_MAGENTA);
    tft.print(millis() / 1000);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(" seconds.");
}

void mediabuttons(Adafruit_ST7789 tft)
{
    // play
    tft.fillScreen(ST77XX_BLACK);
    tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
    tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
    delay(500);
    // pause
    tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
    tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
    tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
    delay(500);
    // play color
    tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
    delay(50);
    // pause color
    tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
    tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
    // play color
    tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}

void runScreenTests(Adafruit_ST7789 tft)
{
    tft.invertDisplay(false);

    Serial.println(F("Initialized"));
    tft.setRotation(0);
    uint16_t time = millis();
    time = millis() - time;

    Serial.println(time, DEC);
    delay(500);
    tftScreenTest(tft);
    delay(1000);
    // large block of text
    tft.fillScreen(ST77XX_BLACK);
    testdrawtext(tft, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
    delay(1000);

    // tft print function!
    tftPrintTest(tft);
    delay(4000);

    // a single pixel
    tft.drawPixel(tft.width() / 2, tft.height() / 2, ST77XX_GREEN);
    delay(500);

    // line draw test
    testlines(tft, ST77XX_CYAN);
    delay(500);

    // optimized lines
    testfastlines(tft, ST77XX_RED, ST77XX_BLUE);
    delay(500);

    testdrawrects(tft, ST77XX_GREEN);
    delay(500);

    testfillrects(tft, ST77XX_YELLOW, ST77XX_MAGENTA);
    delay(500);

    tft.fillScreen(ST77XX_BLACK);
    testfillcircles(tft, 10, ST77XX_BLUE);
    testdrawcircles(tft, 10, ST77XX_WHITE);
    delay(500);

    testroundrects(tft);
    delay(500);

    testtriangles(tft);
    delay(500);

    mediabuttons(tft);
    delay(500);

    Serial.println("done");
    delay(1000);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(5, 5);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextWrap(true);
    tft.invertDisplay(false);
    tft.print("initializing");
    for (int i = 0; i < 100; i++)
    {
        if ((i + 1) % 10 == 0)
            tft.println("");
        tft.print(".");
        delay(200);
    }
    tft.println("");
    tft.setRotation(1);
    chatTest(tft);
    tft.fillScreen(ST77XX_BLACK);
}
