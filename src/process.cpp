#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <linux_parser.h>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int Pid) : Pid_(Pid) {
    CpuUsage_=LinuxParser::CpuUtilization(Pid);
    Command_=LinuxParser::Command(Pid);
    User_=LinuxParser::User(Pid);
    UpTime_=LinuxParser::UpTime(Pid);
    Ram_=LinuxParser::Ram(Pid);
}

// TODO: Return this process's ID
int Process::Pid() { return Pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return CpuUsage_; }

// TODO: Return the command that generated this process
string Process::Command() { return Command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return Ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return User_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return UpTime_; }

bool Process::operator< (Process const& a) const { 
  Process& p1 = const_cast <Process&>(*this);
  Process& p2 = const_cast <Process&>(a);
  return p1.CpuUtilization() < p2.CpuUtilization();
}
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }