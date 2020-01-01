//#include "processor.h"

#include "../include/processor.h"
#include "../include/linux_parser.h"
#include <iostream>
using namespace std;
// Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string> cpus = LinuxParser::CpuUtilization();
    this->cpuUsage = stof(cpus[this->coreId+1]);
    return this->cpuUsage; 
}


