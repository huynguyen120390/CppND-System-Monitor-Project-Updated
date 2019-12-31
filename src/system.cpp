#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "../include/process.h"
#include "../include/processor.h"
#include "../include/system.h"
#include "../include/linux_parser.h"
#include "../include/format.h"

#include <iostream>
using namespace std;


using std::set;
using std::size_t;
using std::string;
using std::vector;
using Format::ElapsedTime;


// TODO: Return the system's CPU
Processor& System::Cpu() { 
    Processor processor(-1); //the overall cpu
    this->cpu_ = processor;
    return this->cpu_; 
}

// TODO: Return a container composed of the system's processes
void swap(Process * p1, Process * p2){
    Process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
void sort_processes(vector<Process>& processes){
    int size = processes.size();
    for(int i = 0; i < size ; i++ ){
        for(int j = 0; j < size-i-1; j++){
            if(processes[j] < processes[j+1]){
                swap(processes[j],processes[j+1]);
            }
        }
    }
}

vector<Process>& System::Processes() { 
    vector<int> pids =  LinuxParser::Pids();
    this->processes_ = {};
    for(auto p : pids){
        Process proc(p);
        this->processes_.push_back(proc);
    }
    sort_processes(this->processes_);
    return this->processes_; 
}



// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();; 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long System::UpTime() { 
    return LinuxParser::UpTime(); 
}



// int main(){
//     System sys;
// //    cout << sys.Cpu().Utilization() << endl;
    
//     for(auto p : sys.Processes()){
//         cout << p.Pid() <<":" <<p.Ram() << endl;
//     }
//     cout << endl;

// //     cout << sys.TotalProcesses() << endl;
// //     cout << sys.RunningProcesses() << endl;
// //     cout << sys.OperatingSystem() << endl;
// //     cout << sys.MemoryUtilization() << endl;
// //     cout << sys.Kernel() << endl;

//  //   cout << Format::ElapsedTime(sys.UpTime()) << endl;
// }
