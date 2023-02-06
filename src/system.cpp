#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
//using LinuxParser::OperatingSystem;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

System::System(){
    vector<int> Processes;
    Processes = LinuxParser::Pids();
    for(int idx=0;idx<Processes.size();idx++)
    {
        processes_.push_back(Process(Processes[idx]));
    }
    OperatingSystem_ = LinuxParser::OperatingSystem();
    Kernel_ = LinuxParser::Kernel();
    TotalProcesses_=LinuxParser::TotalProcesses();
    RunningProcesses_=LinuxParser::RunningProcesses();
    UpTime_= LinuxParser::UpTime();
    MemoryUtilization_ = LinuxParser::MemoryUtilization();

}

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    
    return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    
    return Kernel_; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return MemoryUtilization_; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 

return OperatingSystem_; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return RunningProcesses_; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return TotalProcesses_; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return UpTime_; }
