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

Process::Process(int pid){
    this->pid = pid;
    this->cpu = Process::CpuUtilization();
    this->cmd = Process::Command();
    this->mem = Process::Ram();
    this->user = Process::User();
    this->uptime = Process::UpTime();
}
//Return this process's ID
int Process::Pid() { 
    return this->pid;
}

//Return this process's CPU utilization
float Process::CpuUtilization() { 
    this->cpu = LinuxParser::CpuUtilization(this->pid);
    return this->cpu;
}

//Return the command that generated this process
string Process::Command() {
    this->cmd = LinuxParser::Command(this->pid);
    return this->cmd;
}

//Return this process's memory utilization
string Process::Ram() { 
    this->mem = LinuxParser::Ram(this->pid);
    return this->mem;
}

//Return the user (name) that generated this process
string Process::User() { 
    this->user = LinuxParser::User(this->pid);
    return this->user;
}

//Return the age of this process (in seconds)
long int Process::UpTime() { 
    this->uptime = LinuxParser::UpTime(this->pid);
    return this->uptime;
 }

//Overload the "less than" comparison operator for Process objects
//Compare about RAM usage
bool Process::operator<(const Process& a) const { 
    long double procMem = stold(this->mem);
    long double procaMem = stold(a.mem);
    if (procMem < procaMem){
       return true;
    }
    return false;
}


void test_operatorless(int pid1, int pid2){
    Process p(pid1);
    Process p2(pid2);
    cout << p.Ram() << endl;
    cout << p2.Ram() << endl;
    cout << (p < p2) << endl;
}
