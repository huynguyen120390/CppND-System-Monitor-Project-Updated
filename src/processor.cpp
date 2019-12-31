//#include "processor.h"

#include "../include/processor.h"
#include "../include/linux_parser.h"
#include <iostream>
using namespace std;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string> cpus = LinuxParser::CpuUtilization();
    //cout << " String " << cpus[this->coreId+1] << endl;
    this->cpuUsage = stof(cpus[this->coreId+1]);
    return this->cpuUsage; 
}

// int main(){
//     vector<Processor> processors;
//     for(int i = 0; i < 8; i++){
//         Processor proc(i);
//         processors.push_back(proc);
//     }

//     for(auto p : processors){
//         cout << p.Utilization() << endl;
//     }
    
// }