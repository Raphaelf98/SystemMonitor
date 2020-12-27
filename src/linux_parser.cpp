#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"


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
  string os, kernel;
  string line, version;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version>>kernel;
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
float LinuxParser::MemoryUtilization()
{std::string line;
 float MemTotalUsed, MemFree;
 std::string Type, Quantity;
 std:vector <std::string> mems;
 std::ifstream filestream(kProcDirectory+kMeminfoFilename);
 if (filestream.is_open())
 {
     while(true)
     {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream >> Type >> Quantity;
      if (Type == "MemTotal:") {mems.push_back(Quantity);}
      if (Type == "MemFree:") {mems.push_back(Quantity);}
      if (Type == "Buffers:") {mems.push_back(Quantity);}
      if (Type == "Cached:") {mems.push_back(Quantity);}
      if (Type == "Shmem:") {mems.push_back(Quantity);}
      if (Type == "SReclaimable:") {mems.push_back(Quantity); break;}
      Quantity.erase();
     }

    MemTotalUsed = std::stol(mems[0]) - std::stol(mems[1]);
    long CachedMem = std::stol(mems[3]) + std::stol(mems[5])-std::stol(mems[4]);
    long NonCBMem = MemTotalUsed -( std::stol(mems[2]) + CachedMem);


    return (MemTotalUsed/std::stol(mems[0]));
}
}
// TODO: Read and return the system uptime
long LinuxParser::UpTime()
{   std::string  uptime, line;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open())
    {

      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> uptime ;
    }
    return std::stol(uptime);
}



// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization()
{
    std::string line;
    std::vector<std::string> proclist;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open())
    {
        std::getline(stream,line);
        std::istringstream linestream(line);
        for (int i = 0; i < 11 ; i++)
        {   std::string val;
            linestream >> val;
            proclist.push_back(val);
        }
    proclist.erase(proclist.begin());
    }
    return proclist;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
    std::string id, number;
    std::string line;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open())
    {
        while(std::getline(stream,line))
        {
            std::istringstream linestream(line);
            linestream >> id >> number;
            if ( id == "processes")
            {
                break;
            }
            id.erase();
            number.erase();
        }
    }
    return std::stoi(number);

}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
    std::string id, number;
    std::string line;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open())
    {
        while(std::getline(stream,line))
        {
            std::istringstream linestream(line);
            linestream >> id >> number;
            if ( id == "procs_running")
            {
                break;
            }
            id.erase();
            number.erase();
        }
    }
    return std::stoi(number);


}
std::vector<string> LinuxParser::CpuUtilization(int pid)
{
 std::vector<string> numbers;
 std::string line;
 std::ifstream stream(kProcDirectory + "/" + std::to_string(pid)+ kStatFilename);
 if (stream.is_open())
 {

     std::getline(stream, line);

     std::istringstream stream(line);

     for (int i = 0; i<22;i++)
     {   std::string val;
         stream >> val;
         if (i==13){ numbers.push_back(val);}
         if (i==14){ numbers.push_back(val);}
         if (i==15){ numbers.push_back(val);}
         if (i==16){ numbers.push_back(val);}
     }
 }

 return numbers;
}
// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid)
{
    std::string line;
    std::ifstream stream(kProcDirectory + "/" + std::to_string(pid)+ kCmdlineFilename);
    if (stream.is_open())
    {
        std::getline(stream, line);
    }

    return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid)
{   std::string id, value;
    std::string line;
    std::ifstream stream(kProcDirectory + "/" + std::to_string(pid)+ kStatusFilename);
    if (stream.is_open())
    {
        while(std::getline(stream, line))
        {
            std::istringstream stream(line);
            stream >> id >> value;
            if (id == "VmSize:"){break;}
            id.erase();
            value.erase();
        }
    if (value.empty()){value = "0";}
    }


    return value;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid)
{
    std::string id, value;
        std::string line;
        std::ifstream stream(kProcDirectory + "/" + std::to_string(pid)+ kStatusFilename);
        if (stream.is_open())
        {
            while(std::getline(stream, line))
            {
                std::istringstream stream(line);
                stream >> id >> value;
                if (id == "Uid:"){break;}
                id.erase();
                value.erase();
            }

        }

        return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid)
{   std::string line;
    std::string name, x, uid;
    std::ifstream stream(kPasswordPath);
    if(stream.is_open())
    {
    while (std::getline(stream, line))
       {
           std::replace(line.begin(), line.end(), ':', ' ');
           std::istringstream stream(line);
           stream >> name >> x >> uid;
           if (uid == Uid(pid))
           {
               break;
           }
           name.erase();
           x.erase();
           uid.erase();
       }
    }
    return name;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid)
{
        std::string value;
        std::string line;
        std::ifstream stream(kProcDirectory + "/" + std::to_string(pid)+ kStatFilename);
        if (stream.is_open())
        {

            std::getline(stream, line);

            std::istringstream stream(line);
            for (int i = 0; i<22;i++)
            {   std::string val;
                stream >> val;
                if (i==21){value = val;}
            }
        }



        return std::stol(value);
}
