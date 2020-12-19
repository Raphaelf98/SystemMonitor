#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cmath>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

void Process::Pid(int pid)
{
    pid_ = pid;
}
// TODO: Return this process's ID
int Process::Pid()
{
    return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    std::vector<string> numbers;
    numbers = LinuxParser::CpuUtilization(pid_);
    //TODO: compute CPU process util and return percentage
    float total_time = std::stof(numbers[0])+std::stof(numbers[1])+std::stof(numbers[2])+std::stof(numbers[3]);
    float seconds = LinuxParser::UpTime() - LinuxParser::UpTime(pid_)/sysconf(_SC_CLK_TCK);
    CPU_ = 100*((total_time/sysconf(_SC_CLK_TCK))/seconds);
    return CPU_;

}

// TODO: Return the command that generated this process
string Process::Command()
{
    return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram()
{
    RAM_ = std::stoi(LinuxParser::Ram(pid_)) / 1024;
    return std::to_string(RAM_);
}

// TODO: Return the user (name) that generated this process
string Process::User()
{
    return LinuxParser::User(pid_);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime()
{
    return LinuxParser::UpTime(pid_)/sysconf(_SC_CLK_TCK);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator < (Process const& a) const
{

    return a.RAM_ > RAM_;

}
double Process::Round_(double f)
{
    return std::trunc(f);
}
