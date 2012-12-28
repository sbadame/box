struct Place {
  String name;
  float latitude;
  float longitude;
  String hint;
  int index;
};

struct GPSState {
  unsigned short satellites;
  float longitude;
  float latitude;
  Place place;
};
