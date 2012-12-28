LiquidCrystal lcd(4, 7, 10, 11, 12, 13);

void setup_LCD(String initial_hint)
{
  lcd.clear();
  lcd.begin(16, 2); // set up the LCD's number of columns and rows: 
  lcd.print("Let the games begin.");
  lcd.noCursor();

  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(current_display_hint);
}

void loop_LCD(String current_display_hint)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(current_display_hint);
}
