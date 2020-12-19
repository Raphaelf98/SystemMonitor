#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)
{  int h, m, s;
    h = int(seconds/(60*60));
    std::string hour;
    m = int ((seconds%(60*60))/60);
    std::string min;
    s = int ((seconds%(60*60))%60);
    std::string sec;
    if (h<10) {hour = "0"+std::to_string(h);}
    else hour = std::to_string(h);

    if (m<10) {min = "0"+std::to_string(m);}
    else min = std::to_string(m);

    if (s<10) {sec = "0"+std::to_string(s);}
    else sec = std::to_string(s);
    return hour+":"+min+":"+sec;

}
