#include "processor.h"
#include <fstream>
#include <iostream>
#include <sstream>


// NOT COMPLETED(6/16) ??=> TODO: Return the aggregate CPU utilization
// GO TO JIFFIES AND ACTIVEJIFFIES, IDLEJIFFIES
float Processor::Utilization() { 
    float totalTime = LinuxParser::Jiffies();
    float activeTime = LinuxParser::ActiveJiffies() ;
    float result = 1.0 * (activeTime/totalTime);
    return result;
}

/* 메모(6/16): 아니 이렇게 계산하라는게 stack overflow에 써있는 내용인데,, 왜 uda community랑 답변이 다른 것 같지?
1. https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
2. https://knowledge.udacity.com/questions/156400


PrevIdle = previdle + previowait
Idle = idle + iowait

PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
NonIdle = user + nice + system + irq + softirq + steal

PrevTotal = PrevIdle + PrevNonIdle
Total = Idle + NonIdle

# differentiate: actual value minus the previous one
totald = Total - PrevTotal
idled = Idle - PrevIdle

CPU_Percentage = (totald - idled)/totald
*/