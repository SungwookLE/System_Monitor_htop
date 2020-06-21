#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE(6/21) QUESTION: WHY IS IT NEEDED AS A MEMBER IN THIS CLASS? => TODO: Return the system's CPU
Processor& System::Cpu() { 
    static Processor cpu_;
    return cpu_; }
  
// DONE(6/18) CLEAR => NOT COMPLETED (6/17) TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    std::vector<int> pids = LinuxParser::Pids();
    static std::vector<Process> processes_;
    processes_.clear();

    for (auto it:pids){
        Process p1(it);
        processes_.emplace_back(p1);
    }

    // QUESTION(6/21): HOW TO WORK WITHOUT COMPARE FUNCTION INSERTION BELOW SORT FUNCTION? 
    std::sort(processes_.begin(), processes_.end());
    
    return processes_; }

// DONE(6/14) CLEAR => TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// DONE(6/14) CLEAR => TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// DONE(6/14) CLEAR => TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DONE(6/14) CLEAR => TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE(6/14) CLEAR => TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE(6/15) CLEAR => TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }