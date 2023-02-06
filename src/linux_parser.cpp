#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

#define UP_TIME_STAT      21
#define U_TIME_STAT       13
#define S_TIME_STAT       14
#define CU_TIME_STAT      15
#define CS_TIME_STAT      16

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
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float MemTotal, Memfree, MemUtili, value;
  string line, key;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    for(int i=0;i<2;i++)
    {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> key >> value ;
      if(i) Memfree=value;
      else MemTotal=value;
    }
  }
    MemUtili = MemTotal - Memfree;
    return MemUtili; 
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
   long UpTimeSeconds;
  string line, key;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
  
      std::getline(stream, line);
      std::istringstream linestream(line);
   
      linestream >> UpTimeSeconds ;
     
    }

  return UpTimeSeconds; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> stats(10, "");
  string key, value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i=0;i<11;i++){
      		if(!i)
    			linestream >> key;
      		else
               linestream >> stats[i-1];
    }
  }
  
  return stats; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
string line;
  string key;
  int value;
  int TotalProcessesVal=0;
 
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if(key == "processes")
            {
               TotalProcessesVal = value;             
       }
      }
  }
  return TotalProcessesVal;
   }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  int value;
  int RunningProcessesVal=0;
 
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if(key == "procs_running")
            {
               RunningProcessesVal = value;
               //std::cout<<RunningProcessesVal<<std::endl;
              
       }
      }
  }
  return RunningProcessesVal; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) 
{ 
  string line;
  string key;
  string uid;
  string pid_string=std::to_string(pid);
  string value;
  vector<string> Stats;
 
  std::ifstream stream(kProcDirectory + pid_string + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
   
  
  return line; }


float LinuxParser::CpuUtilization(int pid)
{
  vector<float> stats;
  string line;
  string key;
  string uid;
  string pid_string=std::to_string(pid);
  float value;
  vector<string> Stats;
  float Total_Time=0.0;
  float Seconds=0.0;
  float CpuUsage=0.0;
 
  std::ifstream stream(kProcDirectory + pid_string + kStatFilename);
  if (stream.is_open()) {

    std::getline(stream, line);
   
    std::istringstream linestream(line);
    for(int idx=0 ;idx<UP_TIME_STAT+1;idx++)
    {
      linestream>>value;
      switch(idx)
      {
        case U_TIME_STAT:
            
            stats.push_back(value);
            break;
        case S_TIME_STAT:
            
            stats.push_back(value);
            break;
        case CU_TIME_STAT:
            
            stats.push_back(value);
            break;
        case CS_TIME_STAT:
            
            stats.push_back(value);
            break;
        case UP_TIME_STAT:
          
            stats.push_back(value);
            break;
      }
         
    }
  }
  Total_Time=stats[0]+stats[1]+stats[2]+stats[3];
  Seconds = LinuxParser::UpTime() - stats[4]/sysconf(_SC_CLK_TCK);
  CpuUsage=100*((Total_Time/sysconf(_SC_CLK_TCK))/Seconds);
  return CpuUsage;

}


// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {  
 string line;
  string key;
  string Ram_;
  string pid_string=std::to_string(pid);
  string value;
 
  std::ifstream stream(kProcDirectory + pid_string + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            
            if(key == "VmSize:")
            {
               Ram_ = value;  
            }
      }
  }
  return Ram_;


 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
    string line;
  string key;
  string uid;
  string pid_string=std::to_string(pid);
  string value;
 
  std::ifstream stream(kProcDirectory + pid_string + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            
            if(key == "Uid:")
            {
               uid = value;
               
              
       }
      }
  }
  return uid;
  }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {  
  string line;
  string key;
  string value;
  string uid_file;
  string uid_string;
  string user;
  uid_string=LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> uid_file) {
        if (uid_string == uid_file) {
          user = key;
        }
      }
    }
  }
  return user;
   }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  string key;
  string uid;
  string pid_string=std::to_string(pid);
  string value;
  vector<string> Stats;
 
  std::ifstream stream(kProcDirectory + pid_string + kStatFilename);
  if (stream.is_open()) {
    int i=0;
    std::getline(stream, line);
   
    std::istringstream linestream(line);
for(int idx=0 ;idx<UP_TIME_STAT+1;idx++)
{
   linestream>>value;
     
      
}
  }

  long up_time = std::stol(value)/sysconf(_SC_CLK_TCK);
  return up_time;
  
  
   }
