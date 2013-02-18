/*
 * GPS Constants
 */
#define RXPIN 2
#define TXPIN 3

// Set this value equal to the baud rate of your GPS
#define GPSBAUD  4800
SoftwareSerial uart_gps(RXPIN, TXPIN);
TinyGPS gps;

// The getgps function will get and print the values we want.
void getgps(TinyGPS &gps, GPSState &state) {
  // Define the variables that will be used
  float latitude, longitude;
  gps.f_get_position(&(state.latitude), &(state.longitude));
  state.satellites = gps.satellites();
}

void setup_GPS() {
  // Sets baud rate of your GPS
  uart_gps.begin(GPSBAUD);
}

void loop_GPS(GPSState &state) {
  while(uart_gps.available()) {     // While there is data on the RX pin...
      int c = uart_gps.read();    // load the data into a variable...
      if(gps.encode(c)) {      // if there is a new valid sentence...
        getgps(gps, state);         // then grab the data.
      }
  }
}

