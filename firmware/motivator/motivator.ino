
// Libraries
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include "SPI.h"
#include "SdFat.h"
#include "Adafruit_SPIFlash.h"
#include "Adafruit_TinyUSB.h"

// Pins
#define PIN_LCD_RS 12
#define PIN_LCD_ENABLE 11
#define PIN_LCD_D4 10
#define PIN_LCD_D5 9
#define PIN_LCD_D6 6
#define PIN_LCD_D7 5
#define PIN_BRIGHTNESS 13
#define PIN_MENU_BUTTON 14
#define PIN_SET_BUTTON 15

unsigned long lastTime = 0;

#include "buttons.h";
#include "brightness.h";

#define MODE_DISPLAY 1
#define MODE_MENU 2

byte mode = MODE_DISPLAY;
byte currentMenuItem = 0;

#define DELAYS 8
unsigned long delays[DELAYS] = {2000, 4000, 6000, 10000, 20000, 60000, 3600000, 3600000 * 24};
byte currentDelay = 2;
bool randomOrder = false;
#define CURRENT_DELAY delays[currentDelay]

#define MENU_ITEMS 3
#define MENU_ITEM_BRIGHTNESS 0
#define MENU_ITEM_RANDOM 1
#define MENU_ITEM_DELAY 2

// LCD
Adafruit_LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_ENABLE, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
#define LCD_LINES 2
#define ASCII_CR 13
#define ASCII_LF 10

Adafruit_FlashTransport_SPI flashTransport(EXTERNAL_FLASH_USE_CS, EXTERNAL_FLASH_USE_SPI);
Adafruit_SPIFlash flash(&flashTransport);
FatFileSystem fatfs;
FatFile file;
FatFile root;
Adafruit_USBD_MSC usb_msc;

#include "flash.h";
#include "display.h";

unsigned long printedLines = 0;
byte forceUpdate = true;

void nextDelay()
{
    currentDelay++;
    if (currentDelay >= DELAYS)
    {
        currentDelay = 0;
    }
}

void setup()
{
    pinMode(PIN_BRIGHTNESS, OUTPUT);
    updateBrightness();
    lcd.begin(16, 2);
    Serial.begin(115200);
    buttonsSetup();
    flashSetup();
    delay(500);
}

void loop()
{
    switch (mode)
    {
    case MODE_DISPLAY:
        displayLoop();
        break;
    case MODE_MENU:
        menuLoop();
        break;
    }
}

void displayLoop()
{
    if (menuButtonPressed)
    {
        switchMode(MODE_MENU);
        return;
    }

    if (!forceUpdate && millis() - lastTime < CURRENT_DELAY)
    {
        return;
    }

    forceUpdate = false;
    lastTime = millis();

    lcd.clear();
    if (root.open("/"))
    {
        if (file.open("data.txt", O_RDONLY))
        {
            byte lcdLine = 0;
            unsigned long fileLine = 0;
            bool printing = printedLines == 0;
            lcd.setCursor(0, 0);
            while (file.available())
            {
                char c;
                file.read(&c, 1);
                if (c == ASCII_CR)
                {
                    continue;
                }
                if (c == ASCII_LF && printing)
                {
                    fileLine++;
                    lcdLine++;
                    if (lcdLine >= LCD_LINES)
                    {
                        printedLines += LCD_LINES;
                        break;
                    }
                    lcd.setCursor(0, lcdLine);
                    continue;
                }
                if (!printing)
                {
                    if (c == ASCII_LF)
                    {
                        fileLine++;
                        if (fileLine >= printedLines)
                        {
                            printing = true;
                        }
                    }
                    continue;
                }
                lcd.write(c);
            }

            if (!file.available())
            {
                printedLines = 0;
            }
            file.close();
        }
        else
        {
            displayNotFound();
        }
        root.close();
    }
    else
    {
        displayRootFailed();
    }
}

void switchMode(byte m)
{
    mode = m;
    setButtonPressed = false;
    menuButtonPressed = false;
    lcd.clear();
    delay(500);
}

void menuLoop()
{
    if (menuButtonPressed)
    {
        lcd.clear();
        currentMenuItem++;
        menuButtonPressed = false;
        if (currentMenuItem >= MENU_ITEMS)
        {
            currentMenuItem = 0;
            switchMode(MODE_DISPLAY);
            return;
        }
    }

    if (setButtonPressed)
    {
        lcd.clear();
        setButtonPressed = false;
        switch (currentMenuItem)
        {
        case MENU_ITEM_BRIGHTNESS:
            nextBrightness();
            break;
        case MENU_ITEM_DELAY:
            nextDelay();
            break;
        case MENU_ITEM_RANDOM:
            randomOrder = !randomOrder;
            break;
        }
    }

    lcd.setCursor(0, 0);
    lcd.print("MENU");
    lcd.setCursor(0, 1);
    unsigned long s;
    switch (currentMenuItem)
    {
    case MENU_ITEM_BRIGHTNESS:
        lcd.print("Jas: ");
        lcd.print(currentBrightness);
        break;
    case MENU_ITEM_DELAY:
        lcd.print("Interval: ");
        s = delays[currentDelay] / 1000;
        if (s < 60)
        {
            lcd.print(s);
            lcd.print("s");
        }
        else if (s < 3600)
        {
            lcd.print(s / 60);
            lcd.print("m");
        }
        else
        {
            lcd.print(s / 3600);
            lcd.print("h");
        }

        break;
    case MENU_ITEM_RANDOM:
        lcd.print("Poradi: ");
        if (!randomOrder)
        {
            lcd.print("Postupne");
        }
        else
        {
            lcd.print("Nahodne");
        }
        break;
    }
}
