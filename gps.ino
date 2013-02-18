/*
 * GPS Constants
 */
#define RXPIN 2
#define TXPIN 3

// Set this value equal to the baud rate of your GPS
#define GPSBAUD  4800
SoftwareSerial uart_gps(RXPIN, TXPIN);
TinyGPS gps;

void setup_GPS() {
  // Sets baud rate of your GPS
  uart_gps.begin(GPSBAUD);
}

void loop_GPS(GPSState &state) {
  while(uart_gps.available()) {  // While there is data on the RX pin...
      int c = uart_gps.read();   // load the data into a variable...
      if(gps.encode(c)) {        // if there is a new valid sentence...
        gps.f_get_position(      // Store it.
            &(state.latitude), &(state.longitude));
        state.satellites = gps.satellites();
      }
  }
}

