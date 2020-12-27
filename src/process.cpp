#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

#include <cmath>
#include <chrono>
#include <thread>
#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using namespace std::chrono_literals;

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
    //std::vector<string> numbers1;
    //numbers1 = LinuxParser::CpuUtilization(pid_);
    ////TODO: compute CPU process util and return percentage
    //float idle_time1 = std::stof(numbers1[3]);
    //float total_time1 = std::stof(numbers1[0])+std::stof(numbers1[1])+std::stof(numbers1[2])+std::stof(numbers1[3]);
    //std::vector<string> numbers2;
    //
    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //numbers2 = LinuxParser::CpuUtilization(pid_);
    ////TODO: compute CPU process util and return percentage
    //float idle_time2 = std::stof(numbers2[3]);
    //float total_time2 = std::stof(numbers2[0])+std::stof(numbers2[1])+std::stof(numbers2[2])+std::stof(numbers2[3]);
    //
    //float idle_time_delta = idle_time2 - idle_time1;
    //float total_time_delta = total_time2 - total_time1;
    //CPU_ = (1.0 - idle_time_delta/total_time_delta);
    //return CPU_;
    std::vector<string> numbers;
        numbers = LinuxParser::CpuUtilization(pid_);
        //TODO: compute CPU process util and return percentage
        float total_time = std::stof(numbers[0])+std::stof(numbers[1])+std::stof(numbers[2])+std::stof(numbers[3]);
        float seconds = LinuxParser::UpTime() - LinuxParser::UpTime(pid_)/sysconf(_SC_CLK_TCK);
        CPU_ = ((total_time/sysconf(_SC_CLK_TCK))/seconds);
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

    return LinuxParser::UpTime() - LinuxParser::UpTime(pid_)/sysconf(_SC_CLK_TCK);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator < (Process const& a) const
{
    if (a.CPU_ < CPU_){return true;}
    else return false;

}

