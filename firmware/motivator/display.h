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