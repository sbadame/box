LiquidCrystal lcd(4, 7, 10, 11, 12, 13);

char clear_string[] = "                ";

void setup_LCD(String initial_hint){
  lcd.clear();
  lcd.begin(16, 2); // set up the LCD's number of columns and rows
  lcd.print("Yet the games begin.");
  lcd.noCursor();

  delay(3000);

  lcd_topline(initial_hint);
}

void loop_LCD(String current_display_hint){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(current_display_hint);
}

void lcd_topline(String text) {
    char* cleanbase = strdup(clear_string);
    strncpy(cleanbase, text, strlen(text));
    lcd.setCursor(0,0);
    lcd.print(text);
    free(cleanbase);
}
