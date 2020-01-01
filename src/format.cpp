#include <string>

#include "../include/format.h"
#include <iostream>
using namespace std;

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long hour, min, sec;
    string time,hourS,minS,secS ;

    hour = seconds/3600;
    min =  (long)((seconds/3600.0 - hour)*60);
    sec =  seconds - min*60 - hour*3600;
    hourS = to_string(hour);
    minS = to_string(min);
    secS = to_string(sec);
    if(hourS.size() == 1) hourS = "0" + hourS;
    if(minS.size() == 1) minS = "0" + minS;
    if(secS.size() == 1) secS = "0" + secS;
    time = hourS + ":" + minS + ":" + secS + '\n' ;
    return time;
}
