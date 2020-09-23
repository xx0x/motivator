void displayNotFound()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Soubor data.txt");
    lcd.setCursor(0, 1);
    lcd.print("nenalezen.");
}

void displayTooShort()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Soubor data.txt");
    lcd.setCursor(0, 1);
    lcd.print("je kratky.");
}

void displayInvalidLength()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Soubor data.txt");
    lcd.setCursor(0, 1);
    lcd.print("nelze delit 2.");
}

void displayRootFailed()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Chyba");
    lcd.setCursor(0, 1);
    lcd.print("pameti :(");
}

void displayTransferComplete()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Data");
    lcd.setCursor(0, 1);
    lcd.print("aktualizovana.");
}

byte clear[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000};

byte dino1[] = {
    B00000,
    B00111,
    B00111,
    B00110,
    B10110,
    B11111,
    B01010,
    B01010};

byte dino2[] = {
    B00000,
    B00110,
    B00110,
    B00100,
    B10110,
    B11111,
    B00101,
    B00101};

byte dinoJump[] = {
    B00111,
    B00111,
    B00110,
    B00110,
    B11111,
    B11010,
    B01010,
    B00000};

byte dinoDied[] = {
    B10010,
    B00101,
    B01000,
    B00010,
    B10100,
    B00010,
    B01010,
    B10001};

byte tree[] = {
    B00000,
    B00100,
    B00100,
    B10100,
    B10101,
    B01110,
    B00100,
    B00100};

byte rock[] = {
    B00000,
    B00000,
    B00000,
    B00110,
    B01010,
    B01101,
    B11011,
    B10111};

byte coin[] = {
    B00000,
    B00000,
    B00000,
    B01010,
    B11111,
    B11111,
    B01110,
    B00100};

#define CHAR_CLEAR byte(0)
#define CHAR_DINO1 byte(1)
#define CHAR_DINO2 byte(2)
#define CHAR_DINO_JUMP byte(3)
#define CHAR_DINO_DIED byte(4)
#define CHAR_TREE byte(5)
#define CHAR_ROCK byte(6)
#define CHAR_COIN byte(7)

#define LCD_JUMP_LINE 0
#define LCD_BASE_LINE 1
#define LCD_DINO_COL 2

unsigned int gameScore = 0;
bool dinoFrame = false;

void displayDino(bool jump, bool died)
{
    if (died)
    {
        lcd.setCursor(LCD_DINO_COL, LCD_BASE_LINE);
        lcd.write(CHAR_DINO_DIED);
        return;
    }
    if (!jump)
    {
        lcd.setCursor(LCD_DINO_COL, LCD_BASE_LINE);
        lcd.write(dinoFrame ? CHAR_DINO1 : CHAR_DINO2);
    }
    else
    {
        lcd.setCursor(LCD_DINO_COL, LCD_JUMP_LINE);
        lcd.write(CHAR_DINO_JUMP);
    }
    dinoFrame = !dinoFrame;
}

void displayScore()
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

byte objects[LCD_WIDTH];

#define OBJ_COUNT 3
#define OBJ_TREE 1
#define OBJ_ROCK 2
#define OBJ_COIN 3

void gameStart()
{
    for (byte i = 0; i < LCD_WIDTH; i++)
    {
        objects[i] = 0;
    }
}

#define GAME_SPEEDS 5
unsigned int gameSpeeds[GAME_SPEEDS] = {600, 400, 300, 220, 150};
bool prevJumped = false;

void displayTest()
{
    lcd.createChar(0, clear);
    lcd.createChar(1, dino1);
    lcd.createChar(2, dino2);
    lcd.createChar(3, dinoJump);
    lcd.createChar(4, dinoDied);
    lcd.createChar(5, tree);
    lcd.createChar(6, rock);
    lcd.createChar(7, coin);
    gameStart();
    /*
    lcd.home();
    lcd.write(byte(0));
    lcd.write(byte(2));
    lcd.write(byte(1));
    lcd.write(byte(3));
    lcd.write(byte(4));*/

    bool prevObject = false;
    byte pos = 0;
    while (true)
    {
        byte indexToWrite = (pos + LCD_WIDTH - 1) % LCD_WIDTH;
        objects[indexToWrite] = 0;
        if (!prevObject && random(10) > 6)
        {
            objects[indexToWrite] = random(1, OBJ_COUNT + 1);
            prevObject = true;
        }
        else
        {
            prevObject = false;
        }

        lcd.setCursor(LCD_DINO_COL, LCD_BASE_LINE);
        lcd.write(CHAR_CLEAR);
        lcd.setCursor(LCD_DINO_COL, LCD_JUMP_LINE);
        lcd.write(CHAR_CLEAR);

        lcd.setCursor(0, LCD_BASE_LINE);
        for (byte i = 0; i < LCD_WIDTH; i++)
        {
            switch (objects[(i + pos) % LCD_WIDTH])
            {
            case OBJ_TREE:
                lcd.write(CHAR_TREE);
                break;
            case OBJ_ROCK:
                lcd.write(CHAR_ROCK);
                break;
            case OBJ_COIN:
                lcd.write(CHAR_COIN);
                break;
            default:
                lcd.write(CHAR_CLEAR);
            }
        }
        byte currObj = objects[(LCD_DINO_COL + pos) % LCD_WIDTH];
        bool collision = currObj > 0 && currObj < OBJ_COIN;
        bool dynoJumped = setButtonPressed && !prevJumped;
        prevJumped = dynoJumped;
        setButtonPressed = false;
        if (!dynoJumped && collision)
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
            displayDino(false, true);
            gameScore = 0;
            delay(2000);
            lcd.clear();
            gameStart();
        }
        else
        {
            if (collision)
            {
                gameScore += 1;
            }
            if (currObj == OBJ_COIN)
            {
                gameScore += 3;
                objects[(LCD_DINO_COL + pos) % LCD_WIDTH] = 0;
            }
            displayScore();
            displayDino(dynoJumped, false);
        }

        pos++;
        if (pos >= LCD_WIDTH)
        {
            pos = 0;
        }
        unsigned int gameSpeed = gameScore / 10;
        if (gameSpeed > GAME_SPEEDS)
        {
            gameSpeed = GAME_SPEEDS - 1;
        }
        delay(gameSpeeds[gameSpeed]);
    }

    delay(10000);
}