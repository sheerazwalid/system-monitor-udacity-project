#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : _processId_(pid) {
  // initialize all values
  calculateCpuUsage();
  determineCommand();
  determineRam();
  determineUptime();
  determineUser();
}

// TODO: Return this process's ID
int Process::Pid() { return _processId_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { return _cpuUsage_; }

// TODO: Return the command that generated this process
string Process::Command() { return _command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return _ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return _user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return _uptime_; }

// get user's name that created this process and keep it on variable _user_
void Process::determineUser() { _user_ = LinuxParser::User(Pid()); }

// variable _command_ holds the commands that made process
void Process::determineCommand() { _command_ = LinuxParser::Command(Pid()); }

// memory usage of that process is in _ram_
void Process::determineRam() {
  // read kB value from file
  string val = LinuxParser::Ram(Pid());
  // convert into MB
  try {
    long conv = std::stol(val) / 1000;
    _ram_ = std::to_string(conv);
  } catch (const std::invalid_argument& arg) {
    _ram_ = "0";
  }
}

// calculate the CPU utilization of this process and save in cpuUsage_
void Process::calculateCpuUsage() {
  // read values from filesystem
  long uptime = LinuxParser::UpTime();
  vector<float> val = LinuxParser::CpuUtilization(Pid());
  // only if the values could be read sucessfully
  if (val.size() == 5) {
    // add utime, stime, cutime, cstime (they are in seconds)
    float totaltime =
        val[kUtime_] + val[kStime_] + val[kCutime_] + val[kCstime_];
    float seconds = uptime - val[kStarttime_];
    // calculate the processes CPU usage
    _cpuUsage_ = totaltime / seconds;
  } else
    _cpuUsage_ = 0;
}

// how long the process has been going is in _uptime_
void Process::determineUptime() {
  // TODO depending on kernel version get jiffies or clock ticks
  _uptime_ = LinuxParser::UpTime(Pid());
}

