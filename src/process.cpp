#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

//#include "process.h"
#include "../include/process.h"
#include "../include/linux_parser.h"
#include <iostream>
using namespace std;


using std::string;
using std::to_string;
using std::vector;


// TODO: Return this process's ID
int Process::Pid() { 
    return this->pid;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() {
    this->cmd = LinuxParser::Command(this->pid);;
    return this-> cmd;
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    this->mem = LinuxParser::Ram(this->pid);
    return this->mem;
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    this->user = LinuxParser::User(this->pid);
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

// int main(){
//     Process proc(2145);
//     cout << proc.Pid() << endl;
//     cout << proc.Command() << endl;
//     cout << proc.Ram() << endl;
//     cout << proc.User() << endl;
//     cout << proc.UpTime() << endl;
// }