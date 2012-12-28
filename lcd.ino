LiquidCrystal lcd(4, 7, 10, 11, 12, 13);
String clear_string = "                ";

void setup_LCD(String initial_hint) {
  lcd.clear();
  lcd.begin(16, 2); // set up the LCD's number of columns and rows
  lcd_topline("Let the games begin.");
  lcd.noCursor();

  delay(3000);

  lcd_topline(initial_hint);
}

void lcd_topline(String text) {
    lcd.setCursor(0,0);
    lcd.print(text + clear_string.substring(text.length()));
}
