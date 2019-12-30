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
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
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
          //cout << "Total Mem" << to_string(totalMem) << " FreeMem " << to_string(freeMem);
        }else if (key == "MemFree"){
          freeMem = stof(value);
          //cout << "Total Mem" << to_string(totalMem) << " FreeMem " << to_string(freeMem);
          not_done = false;
        }
      }
    }

  }
  return totalMem - freeMem;
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
    //cout << uptime <<endl;
  }
  return uptime; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  string line;
  string userS, niceS, systemS,idleS,iowaitS, irqS, softirqS, stealS, guestS, guestNiceS;
  long userJ,niceJ, systemJ, idleJ, iowaitJ,irqJ, softirqJ, stealJ, questJ, guestNiceJ;


  
  return 0; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

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
      userJ = stoi(userS);
      niceJ = stoi(niceS);
      systemJ = stoi(systemS);
      idleJ = stoi(idleS);
      iowaitJ = stoi(iowaitS);
      irqJ = stoi(irqS);
      softirqJ = stoi(softirqS);
      stealJ = stoi(stealS);
      guestJ = stoi(guestS);
      guestNiceJ = stoi(guestNiceS);
    }
  }
  activeJiffies = userJ + niceJ + systemJ + irqJ + softirqJ + stealJ + guestJ + guestNiceJ;
  return activeJiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

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
        }
      }

    }
  }
  return runningProcessNum; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }


int main(){
  //PASSED
  //cout << "Operating System : " << LinuxParser::OperatingSystem() << endl;
  //cout << "MemoryUtilization : " << LinuxParser::MemoryUtilization() << endl;
  //cout << "UpTime : " << LinuxParser::UpTime() << endl;
  //cout << "Total Processes : " << LinuxParser::TotalProcesses() << endl;
  //cout << "Running Processes : " << LinuxParser::RunningProcesses() << endl;

  //UNDERTEST
  //cout << "Active Jiffies" << LinuxParser::ActiveJiffies() << endl;


  //UNDERIMPLEMTATION

}