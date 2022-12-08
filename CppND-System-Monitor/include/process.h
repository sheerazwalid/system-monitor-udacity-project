#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  // constructor
  Process(int pid);

  //return process id
  int Pid();                               // TODO: See src/process.cpp
  
  //return user
  std::string User();                      // TODO: See src/process.cpp
  
  //return command
  std::string Command();                   // TODO: See src/process.cpp
  
  //return CPU usage in percentage
  float CpuUtilization() const;            // TODO: See src/process.cpp
  
  //return memory usage in MegaBytes
  std::string Ram();                       // TODO: See src/process.cpp
  
  //return time process has been running
  long int UpTime();                       // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
   // process-ID
  int _processId_;
  // user name that generated this process
  std::string _user_;
  // command that generated this process
  std::string _command_;
  // CPU usage of the process
  float _cpuUsage_;
  // processes memory utilization
  std::string _ram_;
  // age of this process
  long _uptime_;
  // CPU values of a process
  enum ProcessCPUStates {
    kUtime_ = 0,
    kStime_,
    kCutime_,
    kCstime_,
    kStarttime_
  };

  // calculate the CPU utilization of this process and save in cpuUsage_
  void calculateCpuUsage();
  // determine the user name that generated this process and save in user_
  void determineUser();
  // determine the command that generated this process and save in command_
  void determineCommand();
  // determine the memory utilization of that process and save in ram_
  void determineRam();
  // determine the age of this process and save in uptime_
  void determineUptime();
};

#endif