#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>


//#include "linux_parser.h"
//>>>> 
#include "../include/linux_parser.h"
#include <iostream>
using std::cout;
using std::endl;

//<<<<
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
  string os, kernel, versionSym;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> versionSym >>kernel;
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
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  float totalMem;
  float freeMem;
  bool not_done = true;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line) && not_done) {
      //cout << line << endl;
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        //cout << "Key :" << key << " Value: " << value << endl;
        if (key == "MemTotal") {
          totalMem = stof(value);
          break;
          //cout << "Total Mem" << to_string(totalMem) << " FreeMem " << to_string(freeMem);
        }else if (key == "MemFree"){
          freeMem = stof(value);
          //cout << "Total Mem" << to_string(totalMem) << " FreeMem " << to_string(freeMem);
          not_done = false;
          break;
          
        }
      }
    }

  }
  return (totalMem - freeMem)/totalMem;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  string uptimeString;
  string idletimeString;
  float uptime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    while(linestream >> uptimeString >> idletimeString){
      uptime = stof(uptimeString);
    }
  }
  return uptime; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  long active = LinuxParser::ActiveJiffies() ;
  long idle =  LinuxParser::IdleJiffies(); 
  return active + idle;
}

// TODO: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) { 
  std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kStatFilename);
  vector <string> values;
  string line,value;
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::stringstream linestream(line);
    while(std::getline(linestream,value,' ')){
        values.push_back(value);
    }
  }
  return stof(values[13]) + stof(values[14]) + stof(values[15]) + stof(values[16]);
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  string line;
  string key, userS, niceS, systemS,idleS,iowaitS, irqS, softirqS, stealS, guestS, guestNiceS; // string type jiffies
  long activeJiffies,userJ,niceJ, systemJ, idleJ, iowaitJ,irqJ, softirqJ, stealJ, guestJ, guestNiceJ; //long type jiffies

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    while(linestream >> key >> userS >> niceS >> systemS >> idleS >> iowaitS >> irqS >> softirqS >> stealS >> guestS >> guestNiceS){
      userJ = stof(userS);
      niceJ = stof(niceS);
      systemJ = stof(systemS);
      //idleJ = stoi(idleS);   //Idle
      //iowaitJ = stoi(iowaitS);  //Idle
      irqJ = stof(irqS);
      softirqJ = stof(softirqS);
      stealJ = stof(stealS);
      //guestJ = stoi(guestS);   //Virtual
      //guestNiceJ = stoi(guestNiceS);  //Virtual
    }
  }
  activeJiffies = userJ + niceJ + systemJ + irqJ + softirqJ + stealJ;
  return activeJiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string line;
  string key, userS, niceS, systemS,idleS,iowaitS, irqS, softirqS, stealS, guestS, guestNiceS; // string type jiffies
  long idleJiffies,userJ,niceJ, systemJ, idleJ, iowaitJ,irqJ, softirqJ, stealJ, guestJ, guestNiceJ; //long type jiffies

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    while(linestream >> key >> userS >> niceS >> systemS >> idleS >> iowaitS >> irqS >> softirqS >> stealS >> guestS >> guestNiceS){
      idleJ = stof(idleS);
      iowaitJ = stof(iowaitS);
    }
  }
  idleJiffies = idleJ + iowaitJ;
  return idleJiffies;
}

long double LinuxParser::CpuUtilization(int pid){
  std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kStatFilename);
  vector <string> values;
  string line,value;
  long double totalTime, startTime, seconds,hertz,uptime;
  long double cpu_usage;
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::stringstream linestream(line);
    while(std::getline(linestream,value,' ')){
      values.push_back(value);
        //cout << value <<endl;
    }
  }

  // for(auto v : values){
  //   cout << v << endl;
  // }

  uptime = (long double)LinuxParser::UpTime();
  hertz = sysconf(_SC_CLK_TCK);
  totalTime = stold(values[13]) + stold(values[14]) + stold(values[15]) + stold(values[16]); //utime + stime + cutime+ cstime
  startTime = stold(values[21]);
  seconds = uptime - (startTime/hertz);
  cpu_usage = ((totalTime/hertz)/seconds);
  return cpu_usage;
}

// TODO: Read and return CPU utilization
// vector<string> LinuxParser::CpuUtilization() { 
//   string line;
//   string utilS, key, userS, niceS, systemS,idleS,iowaitS, irqS, softirqS, stealS, guestS, guestNiceS; // string type jiffies
//   long double utilD,idleJiffies,activeJiffies,userJ,niceJ, systemJ, idleJ, iowaitJ,irqJ, softirqJ, stealJ, guestJ, guestNiceJ; //long type jiffies
//   string coreId;
//   vector<string> utilizationsS;
//   vectpr<long double> utilizationsD; 

//   std::ifstream filestream(kProcDirectory + kStatFilename);
//   if(filestream.is_open()){
//     //std::getline(filestream,line); //ignore first line
//     while(std::getline(filestream,line)){
//       std::istringstream linestream(line);
//       while(linestream >> key >> userS >> niceS >> systemS >> idleS >> iowaitS >> irqS >> softirqS >> stealS >> guestS >> guestNiceS){
//         if(key.substr(0,3) == "cpu"){
//           coreId = key.substr(3);
//           activeJiffies = LinuxParser::calc_activeTime(userS,niceS,systemS,irqS,softirqS,stealS);
//           idleJiffies = LinuxParser::calc_idleTime(idleS,iowaitS);
//           utilD = activeJiffies/idleJiffies);
//         //  cout << "CPU" << coreId << ": ";
//         //   cout <<" A" << activeJiffies;
//         //   cout <<",I" << idleJiffies;
//         //   cout <<",P" << percentage <<endl;

//           percentages.push_back(percentage);
//         }
//       }
//     }
//   }

  
//   return percentages;
// }

vector<vector<long double>> CpuUtilizationHelper(){
    string line;
    string utilS, key, userS, niceS, systemS,idleS,iowaitS, irqS, softirqS, stealS, guestS, guestNiceS; // string type jiffies
    
    long double idleJiffies,activeJiffies,userJ,niceJ, systemJ, idleJ, iowaitJ,irqJ, softirqJ, stealJ; //long type jiffies
    string coreId;
    vector<long double> actives;
    vector<long double> idles;
    vector<vector<long double>> jiffies;
    


    std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if(filestream.is_open()){
      //std::getline(filestream,line); //ignore first line
      while(std::getline(filestream,line)){
        std::istringstream linestream(line);
        while(linestream >> key >> userS >> niceS >> systemS >> idleS >> iowaitS >> irqS >> softirqS >> stealS >> guestS >> guestNiceS){
          if(key.substr(0,3) == "cpu"){
            coreId = key.substr(3);
            activeJiffies = LinuxParser::calc_activeTime(userS,niceS,systemS,irqS,softirqS,stealS);
            idleJiffies = LinuxParser::calc_idleTime(idleS,iowaitS);
            actives.push_back(activeJiffies);
            idles.push_back(idleJiffies);
           // cout << "Adding cpu "<< coreId << " ative :" << activeJiffies << " idle:"  << idleJiffies << endl;
          }
        }
      }
    }
    jiffies.push_back(actives);
    jiffies.push_back(idles);

    return jiffies;
}

vector<string> LinuxParser::CpuUtilization() { 
 
  vector<string> utilizations;
  vector<vector<long double>> jiffies0,jiffies1;
  long double active0,active1,idle0,idle1,total0,total1,ratio;
 
  jiffies0 = CpuUtilizationHelper();// actives & idles at time 0
  usleep(500000);
  jiffies1 = CpuUtilizationHelper();// actives & idles at time 1
 // cout << "Cpu number " << jiffies1[0].size() << endl;
  //cout <<"Calculating:"<<endl;
  for(size_t i = 0; i < jiffies1[0].size(); i++){
    active0 = jiffies0[0][i]; 
    active1 = jiffies1[0][i];
    idle0   = jiffies0[1][i];
    idle1   = jiffies1[1][i];
    total0  = active0 + idle0;
    total1  = active1 + idle1;
    ratio = (active1 - active0)/(total1 - total0);
    //cout <<"Active"<< active0 << " " << active1 << endl;
    //cout <<"Idle  "<<idle0 << " "<< idle1<<endl;
    //cout <<"Total "<<total0 <<" "<< total1<<endl;
    //cout <<"Ratio "<<ratio <<endl;
    
    utilizations.push_back(to_string(ratio));
  }
  return utilizations;
}


long double LinuxParser::calc_activeTime(string userS, string niceS, string systemS, string irqS, string softirqS, string stealS){
  return stold(userS) + stold(niceS) + stold(systemS) + stold(irqS) + stold(softirqS) + stold(stealS);
}

long double LinuxParser::calc_idleTime(string idleS, string iowaitS){
  return stold(idleS) + stold(iowaitS);
}
// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key;
  string value;
  string line;
  int processNum;
  bool not_done = true;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line) && not_done){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        //cout << key << value<<endl;
        if(key == "processes"){
          processNum = stoi(value);
          not_done = false;
          break;
        }
      }
    }
  }
  return processNum; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key;
  string value;
  string line;
  int runningProcessNum;
  bool not_done = true;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line) && not_done){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "procs_running"){
          runningProcessNum = stoi(value);
          not_done = false;
          break;
        }
      }
    }
  }
  return runningProcessNum; 
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kCmdlineFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string key, value, unit, line;
  std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
  bool not_done = true;
  if(filestream.is_open()){
    while(std::getline(filestream,line) && not_done){
      std::replace(line.begin(),line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> key >> value >> unit){
        if(key == "VmSize"){
          not_done = false;
          break;

        }
      }
    }
  }
  return value; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string key, uid, others, line;
  std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
  bool not_done = true;
  if(filestream.is_open()){
    while(std::getline(filestream,line) && not_done){
      std::replace(line.begin(),line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> key >> uid >> others){
        if(key == "Uid"){
          not_done = false;
          break;
        }
      }
    }
  }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string returnedUid = LinuxParser::Uid(pid);
  string user, xSymbol, uid, others,line;
  std::ifstream filestream(kPasswordPath);
  bool not_done = true;
  if(filestream.is_open()){
    while(std::getline(filestream,line) && not_done){
      std::replace(line.begin(),line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> user >> xSymbol >> uid >> others){
        if(returnedUid == uid){
          not_done = false;
          break;
        }
      }
    }
  }
  return user;
}

// TODO: Read and return the uptime of a process
long int LinuxParser::UpTime(int pid) { 
  std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kStatFilename);
  vector <string> values;
  string line,value;

  if(filestream.is_open()){
    std::getline(filestream,line);
    std::stringstream linestream(line);
    while(std::getline(linestream,value,' ')){
      values.push_back(value);
    }
  }
  return (long int) stold(values[21])/sysconf(_SC_CLK_TCK);
}

void test_commands(){
  for (auto i: LinuxParser::Pids()){
      cout << "Command Line for PID "<<i << " : " << LinuxParser::Command(i) << endl;
  }
}

void test_user(){
  for (auto i: LinuxParser::Pids()){
      cout << "Command Line for PID "<<i << " : " << LinuxParser::User(i) << endl;
  }
}

void test_ram(){
  for (auto i: LinuxParser::Pids()){
      cout << "Command Line for PID "<<i << " : " << LinuxParser::Ram(i) << endl;
  }
}


// int main(){
//   //PASSED
//   //cout << "Operating System : " << LinuxParser::OperatingSystem() << endl;
//   //cout << "MemoryUtilization : " << LinuxParser::MemoryUtilization() << endl;
//   //cout << "UpTime : " << LinuxParser::UpTime() << endl;
//   //cout << "Total Processes : " << LinuxParser::TotalProcesses() << endl;
//   //cout << "Running Processes : " << LinuxParser::RunningProcesses() << endl;
//   //test_user();
//   //test_ram();
  
//   //cout << "RAM for PID :" << LinuxParser::Ram(2497) << endl; 
//   //cout << LinuxParser::UpTime(2145);
//   //cout <<"CpuUtilization for PID " << LinuxParser::CpuUtilization(2480) << endl;
  


//   //UNDERTEST
//   //cout << "Active Jiffies" << LinuxParser::ActiveJiffies() << endl;
//   //cout << "Idle Jiffies" << LinuxParser::IdleJiffies() << endl;

  

//   //UNDERIMPLEMTATION

//   cout << "Utilization " << endl;
//   vector<string> percent = LinuxParser::CpuUtilization();
//   for(auto v:percent){
//     cout << v << endl;
//   }
  
// }