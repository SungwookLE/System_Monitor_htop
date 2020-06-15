#include "processor.h"
#include <fstream>
#include <iostream>
#include <sstream>


// NOT COMPLETED(6/15) => TODO: Return the aggregate CPU utilization
// GO TO JIFFIES AND ACTIVEJIFFIES, IDLEJIFFIES
float Processor::Utilization() { 
    std::string line,key,value1,value2;
    std::string cpu_num, cpu0_num, cpu1_num, cpu2_num, cpu3_num;

    std::ifstream filestream(CPUPath);
    if (filestream.is_open()){
        while (std::getline(filestream, line)){
            std::istringstream linestream(line);
            linestream >> key >> value1 >> value2;
            if (key=="cpu")
                cpu_num = value1;
            else if (key =="cpu0")
                cpu0_num = value1;
            else if (key == "cpu1")
                cpu1_num =value1;
            else if (key == "cpu2")
                cpu2_num = value1;
            else if (key == "cpu3")
                cpu3_num = value1;
        }
    }


    return std::stof(cpu_num); }