
// Buttons
#define DEBOUNCE_TIME 250
bool menuButtonPressed = false;
bool setButtonPressed = false;
unsigned long lastTimeMenuButtonPressed = 0;
unsigned long lastTimeSetButtonPressed = 0;

void menuButtonCallback()
{
    if (millis() - lastTimeMenuButtonPressed > DEBOUNCE_TIME)
    {
        menuButtonPressed = true;
        forceUpdate = true;
        lastTimeMenuButtonPressed = millis();
    }
}

void setButtonCallback()
{
    if (millis() - lastTimeSetButtonPressed > DEBOUNCE_TIME)
    {
        setButtonPressed = true;
        forceUpdate = true;
        lastTimeSetButtonPressed = millis();
    }
}

void buttonsSetup()
{
    pinMode(PIN_MENU_BUTTON, INPUT_PULLUP);
    pinMode(PIN_SET_BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_MENU_BUTTON), menuButtonCallback, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIN_SET_BUTTON), setButtonCallback, FALLING);
}