#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int n): pid_(n) { Process::Ram_ = LinuxParser::Ram(pid_);}

// DONE(6/17) CLEAR => TODO: Return this process's ID
int Process::Pid() { return pid_; }

// DONE(6/18) => TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return LinuxParser::ActiveJiffies(pid_); }

// DONE(6/17) CLEAR => TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// DONE(6/17) CLEAR => TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// DONE(6/17) CLEAR => TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// DONE(6/17) CLEAR => TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// DONE(6/18) => TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  bool cond = false;
  cond = ( std::stol(this->Ram_) > std::stol(a.Ram_) ) ;
  
  return cond;
}