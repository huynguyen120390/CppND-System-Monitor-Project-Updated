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
    string time ;

    hour = seconds/3600;
    min =  (seconds/3600.0 - hour)*60;
    sec =  seconds - min*60 - hour*3600;
    time = to_string(hour) + ":" + to_string(min) + ":" + to_string(sec);
    return time;
}
// int main(){
//      cout << Format::ElapsedTime(5404);
// }