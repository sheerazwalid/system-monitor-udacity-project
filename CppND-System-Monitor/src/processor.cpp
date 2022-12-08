#include "processor.h"
#include <string>
#include <vector>
#include "linux_parser.h"

using std::string;
using std::vector;

Processor::Processor() : prevTotalCPUtime(0.0), prevIdleCPUtime(0.0){};

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  // read current cpu values from file system
  vector<long> cpuValues = convertToLong(LinuxParser::CpuUtilization());
  // total cpu time since boot = user+nice+system+idle+iowait+irq+softirq+steal
  float totalCpuTime =
      cpuValues[LinuxParser::kUser_] + cpuValues[LinuxParser::kNice_] +
      cpuValues[LinuxParser::kSystem_] + cpuValues[LinuxParser::kIdle_] +
      cpuValues[LinuxParser::kIOwait_] + cpuValues[LinuxParser::kIRQ_] +
      cpuValues[LinuxParser::kSoftIRQ_] + cpuValues[LinuxParser::kSteal_];
  // idle time since boot = idle + iowait
  float idleCpuTime =
      cpuValues[LinuxParser::kIdle_] + cpuValues[LinuxParser::kIOwait_];

  // calculate the cpu usage since last update
  float diffIdle = idleCpuTime - prevIdleCPUtime;
  float diffTotal = totalCpuTime - prevTotalCPUtime;
  float diffUsage = (diffTotal - diffIdle) / diffTotal;
  // remember the total and idle times for next check
  prevIdleCPUtime = idleCpuTime;
  prevTotalCPUtime = totalCpuTime;
  return diffUsage;
}

// convert the given string vector into a long vector
vector<long> Processor::convertToLong(vector<string> values) {
  vector<long> convertedValues{};

  for (int it = 0; it < (int)values.size(); it++) {
    try {
      convertedValues.push_back(std::stol(values[it]));
    } catch (const std::invalid_argument& arg) {
      convertedValues.push_back((long)0);
    }
  }
  return convertedValues;
}