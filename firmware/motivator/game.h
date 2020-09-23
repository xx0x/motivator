#include "game_sprites.h"

#define LCD_JUMP_LINE 0
#define LCD_BASE_LINE 1
#define LCD_DINO_COL 2

#define OBJECTS_BASE 5 // 5-7
#define OBJECTS_COUNT 3

#define GAME_SPEEDS 5

byte gameObjects[LCD_WIDTH];
byte gameObjectsPos = 0;

unsigned int gameSpeeds[GAME_SPEEDS] = {600, 400, 300, 220, 150};
bool gamePrevJumped = false;
unsigned int gameScore = 0;
unsigned long lastTimeGame = 0;
bool gameEnded = true;
bool prevGameWasObject = false; // to not generate two objects in a row
bool dinoFrame = false;         // swapping dino frames

void gameDisplayDino(bool jump, bool died)
{
    if (died)
    {
        lcd.setCursor(LCD_DINO_COL, LCD_BASE_LINE);
        lcd.write(SPRITE_DIED);
        return;
    }
    if (!jump)
    {
        lcd.setCursor(LCD_DINO_COL, LCD_BASE_LINE);
        lcd.write(dinoFrame ? SPRITE_DINO1 : SPRITE_DINO2);
    }
    else
    {
        lcd.setCursor(LCD_DINO_COL, LCD_JUMP_LINE);
        lcd.write(SPRITE_JUMP);
    }
    dinoFrame = !dinoFrame;
}

void gameDisplayScore()
{
    int cur = LCD_WIDTH - numPlaces(gameScore) - 7;
    if (cur >= 0)
    {
        lcd.setCursor(cur, LCD_JUMP_LINE);
        lcd.print("SCORE: ");
    }
    else
    {
        lcd.setCursor(0, LCD_JUMP_LINE);
    }
    lcd.print(gameScore);
}

void gameSetup()
{
    prevGameWasObject = false;
    gameObjectsPos = 0;
    gameEnded = false;
    for (byte i = 0; i < SPRITES_COUNT; i++)
    {
        lcd.createChar(i, sprites[i]);
    }
    for (byte i = 0; i < LCD_WIDTH; i++)
    {
        gameObjects[i] = 0;
    }
}

unsigned int gameSpeedCalculate()
{
    unsigned int gameSpeed = gameScore / 10;
    if (gameSpeed > GAME_SPEEDS)
    {
        gameSpeed = GAME_SPEEDS - 1;
    }
    return gameSpeeds[gameSpeed];
}

void gameEnd()
{
    int cur = LCD_WIDTH - numPlaces(gameScore) - 11;
    if (cur >= 0)
    {
        lcd.setCursor(cur, LCD_JUMP_LINE);
        lcd.print("GAME OVER: ");
    }
    else
    {
        lcd.setCursor(0, LCD_JUMP_LINE);
    }
    lcd.print(gameScore);
    if(gameScore > gameHighScore){
        gameHighScore = gameScore;
        flashWriteConfig();
    }
    gameDisplayDino(false, true);
    gameScore = 0;
    delay(2000);
    lcd.clear();
    lastTimeGame = 0;
    gameEnded = true;
    return;
}

void gameLoop()
{
    if(menuButtonPressed){
        menuButtonPressed = false;
        mode = MODE_MENU;
        lcd.clear();
        delay(500);
        return;
    }
    if (millis() - lastTimeGame < gameSpeedCalculate())
    {
        return;
    }
    lastTimeGame = millis();
    if (gameEnded)
    {
        gameSetup();
    }
    byte indexToWrite = (gameObjectsPos + LCD_WIDTH - 1) % LCD_WIDTH;
    gameObjects[indexToWrite] = 0;
    if (!prevGameWasObject && random(10) > 6)
    {
        gameObjects[indexToWrite] = OBJECTS_BASE + random(0, OBJECTS_COUNT);
        prevGameWasObject = true;
    }
    else
    {
        prevGameWasObject = false;
    }

    lcd.setCursor(LCD_DINO_COL, LCD_BASE_LINE);
    lcd.write(SPRITE_CLEAR);
    lcd.setCursor(LCD_DINO_COL, LCD_JUMP_LINE);
    lcd.write(SPRITE_CLEAR);
    lcd.setCursor(0, LCD_BASE_LINE);
    for (byte i = 0; i < LCD_WIDTH; i++)
    {
        byte object = gameObjects[(i + gameObjectsPos) % LCD_WIDTH];
        if (object > 0)
        {
            lcd.write(object);
        }
        else
        {
            lcd.write(SPRITE_CLEAR);
        }
    }
    byte currObj = gameObjects[(LCD_DINO_COL + gameObjectsPos) % LCD_WIDTH];
    bool collision = currObj > 0 && currObj < SPRITE_COIN;
    bool dinoJumped = setButtonPressed && !gamePrevJumped;
    gamePrevJumped = dinoJumped;
    setButtonPressed = false;
    if (!dinoJumped && collision)
    {
        gameEnd();
    }
    else
    {
        if (collision)
        {
            gameScore += 1;
        }
        if (currObj == SPRITE_COIN && !dinoJumped)
        {
            gameScore += 3;
            gameObjects[(LCD_DINO_COL + gameObjectsPos) % LCD_WIDTH] = 0;
        }
        gameDisplayScore();
        gameDisplayDino(dinoJumped, false);
    }
    gameObjectsPos++;
    if (gameObjectsPos >= LCD_WIDTH)
    {
        gameObjectsPos = 0;
    }
}