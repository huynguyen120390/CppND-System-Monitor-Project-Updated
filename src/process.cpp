#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;
using namespace LinuxParser;

// TODO: Return this process's ID
int Process::Pid() { 
    return this->pid;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() { 
    this->cmd = LinuxParser::Command(pid);;
    return this-> cmd;
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    this->mem = LinuxParser::Ram(this->pid);
    return this->mem;
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    this->user = LinuxParser::
    return this->user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    this->uptime = LinuxParser::UpTime(this->pid);
    return this->uptime;
 }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }


#endif