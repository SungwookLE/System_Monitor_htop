#include "processor.h"
#include <fstream>
#include <iostream>



// DONE(6/21) CLEAR => TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::string line, cpu, value;
    std::vector<std::string> utilization = LinuxParser::CpuUtilization();

    float user = std::stof(utilization[0]);
    float nice = std::stof(utilization[1]);
    float system = std::stof(utilization[2]);
    float idle = std::stof(utilization[3]);
    float iowait = std::stof(utilization[4]);
    float irq = std::stof(utilization[5]);
    float softirq = std::stof(utilization[6]);
    float steal = std::stof(utilization[7]);

    // Calculation
    float PrevIdle = previdle + previowait;
    float Idle = idle + iowait;

    float PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
    float NonIdle = user + nice + system + irq + softirq + steal;

    float PrevTotal = PrevIdle + PrevNonIdle;
    float Total = Idle + NonIdle;

    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;

    //Final output
    float output = (totald - idled ) / totald;

    // one step memory variable
    previdle = idle;
    previowait = iowait;
    prevuser = user;
    prevnice = nice;
    prevsystem = system;
    previrq = irq;
    prevsoftirq = softirq;
    prevsteal = steal;

    return output;
}





/* MEMO(6/21):HOW TO CALCULATE SYSTEM MEMORY UTILIZATION
1. https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
2. https://knowledge.udacity.com/questions/153570#160087

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