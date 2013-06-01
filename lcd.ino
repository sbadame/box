LiquidCrystal lcd(4, 7, 10, 11, 12, 13);
String lcd_top = "";
String lcd_bottom = "";
String lcd_progress = "";

void setup_LCD() {
  lcd.clear();
  lcd.begin(16, 2); // set up the LCD's number of columns and rows
  lcd.noCursor();
  lcd.noAutoscroll();
}

void lcd_display(String top, String bottom, String progress) {
    lcd_top = top;
    lcd_bottom = bottom;
    lcd_progress = progress;
    update_screen();
}

void update_screen() {
    lcd.clear();

    lcd.leftToRight();
    lcd.setCursor(0,0);
    lcd.print(lcd_top);

    // Clear the bottom line
    lcd.leftToRight();
    lcd.setCursor(0,1);

    // Print starting from the left
    lcd.setCursor(0,1);
    lcd.print(lcd_bottom);

    // Print starting from the right
    lcd.rightToLeft();
    lcd.setCursor(15,1);
    lcd.print(lcd_progress);
}
