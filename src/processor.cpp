#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> Cpu_Stats;
    Cpu_Stats=LinuxParser::CpuUtilization();
    float user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    float Cpu_Usage=0, Total, Total_Idle, Total_diff, Idle_diff;
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

    Total=user+nice+system+idle+iowait+irq+softirq+steal+guest+guest_nice;
    Total_Idle=iowait+idle;
    Total_diff=Total-Prev_Total;
    Idle_diff=Total_Idle-Prev_Idle;
    Prev_Total=Total;
    Prev_Idle=Total_Idle;
    Cpu_Usage=(Total_diff-Idle_diff)/Total_diff;
    return Cpu_Usage; }