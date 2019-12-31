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

// vector<vector<long double>> manage_previousJiffies(vector<vector<long double>> prevJiffies){
//   vector<vector<long double>> jiffies;
//   if (LinuxParser::is_firstParsed){
//     LinuxParser::actives.assign(LinuxParser::coreNum + 1,0.0);
//     LinuxParser::idles.assign(LinuxParser::coreNum + 1,0.0); 
//     jiffies.push_back(LinuxParser::actives);
//     jiffies.push_back(LinuxParser::idles);
//   }else{
//     jiffies = LinuxParser::prevJiffies;
//     LinuxParser::prevJiffies = prevJiffies;
//   }
  
//   return jiffies;
// }

// vector<string> LinuxParser::CpuUtilization() { 
 
//   vector<string> utilizations;
//   vector<vector<long double>> jiffies0,jiffies1;
//   long double active0,active1,idle0,idle1,total0,total1,ratio;
 
//   jiffies1 = CpuUtilizationHelper();// actives & idles at time 1
//   jiffies0 = manage_previousJiffies(jiffies1);
//   cout << "Cpu number " << jiffies1[0].size() << endl;
//   cout <<"Calculating:"<<endl;
//   for(int i = 0; i < jiffies1[0].size(); i++){
//     active0 = jiffies0[0][i]; 
//     active1 = jiffies1[0][i];
//     idle0   = jiffies0[1][i];
//     idle1   = jiffies1[1][i];
//     total0  = active0 + idle0;
//     total1  = active1 + idle1;
//     ratio = (active1 - active0)/(total1 - total0);
//     cout <<"Active"<< active0 << " " << active1 << endl;
//     cout <<"Idle  "<<idle0 << " "<< idle1<<endl;
//     cout <<"Total "<<total0 <<" "<< total1<<endl;
//     cout <<"Ratio "<<ratio<<endl;
    
//     utilizations.push_back(to_string(ratio));
//   }
//   return utilizations;
// }

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