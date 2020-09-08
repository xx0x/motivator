
// Brightness
#define BRIGHTNESS_MODES 4
byte brightnessModes[BRIGHTNESS_MODES] = {0, 32, 128, 255};
byte currentBrightness = BRIGHTNESS_MODES - 1;

void updateBrightness()
{
    analogWrite(PIN_BRIGHTNESS, brightnessModes[currentBrightness]);
}

void nextBrightness()
{
    currentBrightness++;
    if (currentBrightness >= BRIGHTNESS_MODES)
    {
        currentBrightness = 0;
    }
    updateBrightness();
}
