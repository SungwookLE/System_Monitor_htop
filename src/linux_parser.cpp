#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os1, os2, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os1 >> os2 >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE(6/14) => TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::ifstream stream(kProcDirectory+kMeminfoFilename);
  string line, key,res_line;
  string value_memtotal;
  string value_memfree;

  if (stream.is_open()){
    while (std::getline(stream, line)){
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), 'k', ' ');
      std::replace(line.begin(), line.end(), 'B', ' ');
      std::istringstream linestream(line);
      linestream >> key >> res_line;
      if (key == "MemTotal") {
          value_memtotal=res_line;
          std::replace(value_memtotal.begin(), value_memtotal.end(), '_', ' ');
        }
      else if (key == "MemFree"){
          value_memfree=res_line;
          std::replace(value_memfree.begin(), value_memfree.end(), '_', ' ');
      }
    }
  }

  return stof(value_memtotal) - stof(value_memfree); }

// DONE(6/15) => TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  string line, val1, val2;

  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> val1 >> val2;
  }
  
  return std::stoi(val1);  }

//  DONE(6/16) => TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return  LinuxParser::ActiveJiffies() + LinuxParser::IdleJiffies(); }


// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

//  DONE(6/16) => TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  
  std::vector<string> values = LinuxParser::CpuUtilization();
  long val = stof(values[CPUStates::kUser_]) +
          stof(values[kNice_]) + 
          stof(values[kSystem_]) + 
          stof(values[kIdle_]) + 
          stof(values[kSoftIRQ_]) + 
          stof(values[kSteal_]) + 
          stof(values[kGuest_]) + 
          stof(values[kGuestNice_]) ;
  
  return val; }

//  DONE(6/16) => TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  vector<string> values = LinuxParser::CpuUtilization() ;
  return (stof(values[kIdle_]) + stof(values[kIOwait_])); 
}
// DONE(6/16) => TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  std::vector<string> cpu_num;
  std::string line, key;
  std::string cpu_user, cpu_nice, cpu_system, cpu_idle, cpu_iowait, cpu_irq, cpu_softirq , cpu_steal, cpu_guest, cpu_guest_nice;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  
  if (filestream.is_open()){
     while (std::getline(filestream, line)){
       std::istringstream linestream(line);
       linestream >> key >> cpu_user >> cpu_nice >> cpu_system >> cpu_idle
       >> cpu_iowait >> cpu_irq >> cpu_softirq >> cpu_steal >> cpu_guest >> cpu_guest_nice;
        if (key == "cpu"){
          cpu_num.push_back(cpu_user);
          cpu_num.push_back(cpu_nice);
          cpu_num.push_back(cpu_system);
          cpu_num.push_back(cpu_idle);
          cpu_num.push_back(cpu_iowait);
          cpu_num.push_back(cpu_irq);
          cpu_num.push_back(cpu_softirq);
          cpu_num.push_back(cpu_steal);
          cpu_num.push_back(cpu_guest);
          cpu_num.push_back(cpu_guest_nice);
        }
     }
  }
  return cpu_num;
}

// DONE(6/14) => TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::ifstream stream(kProcDirectory+kStatFilename);
  string line,key,res_line,total_proc;

  if (stream.is_open()){
    while (std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> key >> res_line;
      if (key == "processes")
        total_proc = res_line;
    }
  }
  return std::stoi(total_proc); }

// DONE(6/14) => TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::ifstream stream(kProcDirectory+kStatFilename);
  string line,key,res_line,running_proc;

   if (stream.is_open()){
     while (std::getline(stream, line)){
       std::istringstream linestream(line);
       linestream >> key >> res_line;
       if (key == "procs_running")
          running_proc= res_line;
     }
   }
  return std::stoi(running_proc); }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// DONE(6/16) => TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::ifstream stream(kProcDirectory+to_string(pid)+kStatusFilename);
  std::string line, key, uid;
  if (stream.is_open()){
    while (std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> key >> uid;
      if (key == "Uid:")
        return string(uid); 
    }
  }
}

// DONE(6/16) => TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::ifstream stream(kPasswordPath);
  std::string line, key, user, res;
  if (stream.is_open()){
    while (std::getline(stream,line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> res >> key;
      if (key==to_string(pid))
        return user;
    }
  }
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }