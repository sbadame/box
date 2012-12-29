struct Place {
  char* name;
  float latitude;
  float longitude;
  char* hint;
  char* bottom;
  int index;
  char* progress;
};

struct GPSState {
  unsigned short satellites;
  float longitude;
  float latitude;
  Place place;
};
