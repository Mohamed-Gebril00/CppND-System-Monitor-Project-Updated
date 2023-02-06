#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
 System();
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // TODO: See src/system.cpp
  std::string OperatingSystem();      // TODO: See src/system.cpp

  // TODO: Define any necessary private members
 private:
  int TotalProcesses_{0};
  int RunningProcesses_{0};
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::string OperatingSystem_{""};
  std::string Kernel_{""};
  long UpTime_{0};
  float MemoryUtilization_{0.0};
};

#endif