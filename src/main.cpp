#include "ncurses_display.h"
#include "system.h"
#include <iostream>


#include "linux_parser.h"

int main() {
  System system;

  /* TEST print for system class */
  std::cout << system.OperatingSystem() <<std::endl;
  std::cout << system.Kernel() << std::endl;
  std::cout << system.MemoryUtilization() << std::endl;
  std::cout << system.TotalProcesses() << std::endl;
  std::cout << system.RunningProcesses() << std::endl;
  std::cout << system.UpTime() << std::endl;
  std::cout << std::endl;

  system.Processes().back(); // (6/17 why is this point has the segmentation error??... )

  // for (auto msg:LinuxParser::CpuUtilization()){
  //   std::cout<< msg << std::endl;
  // }
  // std::cout << Processor::Utilization() << std::endl;

  // std::cout << std::endl;
  
  //  for ( auto msg:LinuxParser::Pids()) {
  //     std::cout  << LinuxParser::Ram(msg) << std::endl;
  //  }
  
 
  
  
  /* Original */
  // NCursesDisplay::Display(system);

  
}