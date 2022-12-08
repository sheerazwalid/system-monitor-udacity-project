#include <string>

#include "format.h"

using namespace std;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS

string Format::ElapsedTime(long seconds) {
    string time = "00:00:00";
    long timeVal = 0;

    if (seconds > 0) {
      // 3600 seconds in an hour
      timeVal = seconds / 3600;
      time = Time_String(timeVal) + ":";
        
      // 60 seconds in a  minutes
      // mod 60 in order to keep minutes in the 0-60 range
      timeVal = (seconds / 60) % 60;
      time += Time_String(timeVal) + ":";
        
      // mod 60 in order to keep seconds in the 0-60 range
      timeVal = seconds % 60;
      time += Time_String(timeVal);
    }
  return time;
}

// formats time in double digits 00:00:00
// if value size is not 2 digits a zero is placed in front
string Format::Time_String(long time) {
  if (time < 10)
    return "0" + to_string(time);
  else
    return to_string(time);
}