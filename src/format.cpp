#include <string>
#include <sstream>
#include <iomanip>


#include "format.h"

using std::string;

// DONE(6/18) CLEAR! => TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    std::stringstream stream1,stream2,stream3;
    long h = seconds / 3600;
    stream1 << std::setw(2) << std::setfill('0') << h;
    std::string hour_;
    hour_ = stream1.str();

    long m = seconds % 3600 /60 ;
    stream2 << std::setw(2) << std::setfill('0') << m;
    std::string min_;
    min_ = stream2.str();

    long s = seconds % 3600 % 60;
    stream3 << std::setw(2) << std::setfill('0') << s;
    std::string sec_;
    sec_ = stream3.str();

    return (hour_ + ":"+min_+":"+sec_ ); }