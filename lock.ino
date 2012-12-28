#define MOTOR_PIN 9

PWMServo servo;

boolean locked = false; //make sure this is true with setup_lock();

void setup_lock()
{
  servo.attach(MOTOR_PIN);
  force_lock();
}

void lock()
{
  if (!locked)
  {
    force_lock();
  }
}

void unlock()
{
  if (locked)
  {
    force_unlock();
  }
}

void force_lock()
{
  locked = true;
  servo.write(40);
  Serial.println("Locked box.");
}

void force_unlock()
{
  locked = false;
  servo.write(150);
  Serial.println("Unlocked box.");
}

unsigned long time = 0;
unsigned long oldtime = 0;

void loop_lock(GPSState &state)
{
  /**
   * Debug lock loop
   */
  /*if ((millis() / (3 * 1000)) % 2) {
    unlock();
  } else {
    lock();
  }*/
  
  
  if (state.place.name == "ANYWHERE" || state.place.name == "NO_SIGNAL")
  {
    lock();
  }
  else
  { 
    unlock();
  }
 
}


