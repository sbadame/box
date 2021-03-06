#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <PWMServo.h>
#include <LiquidCrystal.h>
#include "data.h"
#include "places.h" // Where Place places[] is defined.
                    // .gitignore'd because of GPS coordinates.
Place ANYWHERE = {"ANYWHERE", 0, 0, "ANYWHERE", "ANYWHERE bot", -1, ""};
Place NO_SIGNAL = {"NO_SIGNAL", 0, 0, "NO_SIGNAL","NO_SIGNAL bot", -1, ""};

/**
 * Data about the places to go.
 */
#define NUMBER_OF_PLACES (sizeof(places)/sizeof(Place))
#define SLACK_METERS 50

/**
 * The history buffer
 */
#define HISTORY_LENGTH 5
Place place_history[HISTORY_LENGTH];
Place last_known_place = ANYWHERE;
int place_history_index = 0;

String current_display_hint = places[0].hint;
String current_display_bottom = places[0].bottom;
String current_display_progress = places[0].progress;

GPSState previous_state;

void setup() {
  for(int i = 0; i < NUMBER_OF_PLACES; i++) {
    places[i].index = i;
  }
  previous_state.place = NO_SIGNAL;

  // Fill this up with ANYWHERE.
  for(int i = 0; i < HISTORY_LENGTH; i++) {
    place_history[i] = ANYWHERE;
  }

  setup_serial();
  setup_LCD();
  lcd_display("Let the games", "begin.", "");
  setup_GPS();
  setup_lock();
  unlock();
  lcd_display(places[0].hint, places[0].bottom, places[0].progress);
  delay(5000);
  lock();
}

void loop() {
  GPSState new_state;
  loop_GPS(new_state); //Writes to new_state the new coordinates
  loop_serial(new_state);

  //Writes to new_state the current place
  //requires 5 consecutive good reads for it to happen
  new_state.place = calculate_current_place(
      new_state.longitude, new_state.latitude);

  if (new_state.place.name != previous_state.place.name
          && new_state.place.name != ANYWHERE.name
          && new_state.place.name != NO_SIGNAL.name)  {

    if (new_state.place.index == NUMBER_OF_PLACES - 1) {
      current_display_hint = "Open me up babe";
      current_display_bottom = "";
      current_display_progress = "";
      unlock();
    } else {
      Place next_place = places[new_state.place.index + 1];
      current_display_hint = next_place.hint;
      current_display_bottom = next_place.bottom;
      current_display_progress = next_place.progress;
    }

    Serial.print("Now at: ");
    Serial.println(new_state.place.name);
    lcd_display(current_display_hint,
                current_display_bottom,
                current_display_progress);
  }

  previous_state = new_state;
  delay(1000);
}

/**
 * converts long/lat coordinates into a place.
 * Adds that place to the history buffer.
 * If the entire history buffer is the same then last_known_place is updated.
 * last_known_place is returned.
 */
Place calculate_current_place(float longitude, float latitude) {
  place_history[place_history_index] = calculate_place(longitude, latitude);
  place_history_index = (place_history_index + 1) % HISTORY_LENGTH;
  print_history();

  for (int i = 0; i < HISTORY_LENGTH-1; i++) {
    if (place_history[i].name != place_history[i+1].name) {
      return last_known_place;
    }
  }

  last_known_place = place_history[0];
  return last_known_place;
}

/**
 * Really stupid function that finds the place in places that is closest
 * to the given longitude/latitude.
 * Returns ANYWHERE if none of the places are within 
 */
Place calculate_place(float longitude, float latitude) {
  for(int i = 0; i < NUMBER_OF_PLACES; i++) {
    if (distance(latitude, longitude,
                 places[i].latitude, places[i].longitude) < SLACK_METERS) {
      return places[i];
    }
  }
  return ANYWHERE;
}

float distance(float lat1, float lon1,
               float lat2, float lon2) {
  //Uses haversine from:
  //  http://www.movable-type.co.uk/scripts/latlong.html
  float dLat = radians(lat2-lat1);
  float dLon = radians(lon2-lon1);
  float lat1_rad = radians(lat1);
  float lat2_rad = radians(lat2);

  float a = sin(dLat/2) * sin(dLat/2) +
            sin(dLon/2) * sin(dLon/2) *
            cos(lat1_rad) * cos(lat2_rad);
  float c = 2 * atan2(sqrt(a), sqrt(1-a));
  return 6372795 * c; //Earth's radius in m
}
