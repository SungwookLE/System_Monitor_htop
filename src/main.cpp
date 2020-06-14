#include "ncurses_display.h"
#include "system.h"
#include <iostream>

int main() {
  System system;

  /* TEST print for system class */
  std::cout << system.OperatingSystem() <<std::endl;
  std::cout << system.Kernel() << std::endl;
  std::cout << system.MemoryUtilization() << std::endl;
  std::cout << system.TotalProcesses() << std::endl;
  std::cout << system.RunningProcesses() << std::endl;
  
  
  //ORIGINAL: NCursesDisplay::Display(system);

  
}