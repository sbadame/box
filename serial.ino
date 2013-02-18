#define TERMBAUD  115200

void setup_serial() {
  // Sets baud rate of your terminal program
  Serial.begin(TERMBAUD);
  Serial.println("");
  Serial.println("Sandro\'s Box");
  Serial.println("       ...waiting for lock...           ");
  Serial.println("");
}

void loop_serial(GPSState &state) {
  // You can now print variables latitude and longitude
  Serial.print("Lat/Long: ");
  Serial.print(state.latitude,5);
  Serial.print(", ");
  Serial.print(state.longitude,5);
  Serial.print(" Sats: ");
  Serial.println(state.satellites);
}

void print_history() {
  Serial.print("History[");
  Serial.print(place_history_index);
  Serial.print("]: ");
  for(int i = 0; i < HISTORY_LENGTH; i++)
  {
    Serial.print(place_history[i].name);
    Serial.print(", ");
  }
  Serial.println();
}
