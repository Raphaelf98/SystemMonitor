#include "processor.h"
#include "linux_parser.h"
#include <vector>

using std::vector;
// TODO: Return the aggregate CPU utilization
float PrevIdle =0;
float PrevTotal =0;
float PrevNonIdle =0;

float Processor::Utilization()
{
    float user, nice, system, idle, iowait, irq, softirq, steal, Idle, NonIdle, Total;
    std::vector<std::string> proclist;
    proclist = LinuxParser::CpuUtilization();

    //Idle = idle + iowait
    Idle = std::stof(proclist[3])+ std::stof(proclist[4]);
    //NonIdle = user + nice + system + irq + softirq + steal
    NonIdle = std::stof(proclist[0]) + std::stof(proclist[1]) + std::stof(proclist[2]) +
            std::stof(proclist[5])+ std::stof(proclist[6]) +std::stof(proclist[7]);
    Total = Idle + NonIdle;
    // differentiate actual - previous
    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;
    // CPUPercentage = (totald - idled) / totald
    PrevIdle = Idle;
    PrevTotal = Total,
    PrevNonIdle = NonIdle;
    return (totald - idled) / totald;



}
