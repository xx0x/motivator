void displayNotFound()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("data.txt");
    lcd.setCursor(0, 1);
    lcd.print("not found");
}

void displayRootFailed()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("open root");
    lcd.setCursor(0, 1);
    lcd.print("failed");
}