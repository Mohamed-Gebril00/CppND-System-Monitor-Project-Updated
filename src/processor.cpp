#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> Cpu_Stats;
    Cpu_Stats=LinuxParser::CpuUtilization();
    float user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    float Cpu_Usage=0;
    user=std::stof(Cpu_Stats[0]);
    nice=std::stof(Cpu_Stats[1]);
    system=std::stof(Cpu_Stats[2]);
    idle=std::stof(Cpu_Stats[3]);
    iowait=std::stof(Cpu_Stats[4]);
    irq=std::stof(Cpu_Stats[5]);
    softirq=std::stof(Cpu_Stats[6]);
    steal=std::stof(Cpu_Stats[7]);
    guest=std::stof(Cpu_Stats[8]);
    guest_nice=std::stof(Cpu_Stats[9]);

    Cpu_Usage=user+nice+system+idle+iowait+irq+softirq+steal+guest+guest_nice;
    
    return Cpu_Usage; }