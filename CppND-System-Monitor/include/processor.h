#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
    public:
        float Utilization();  // TODO: See src/processor.cpp
        
        Processor(); // constructor 
        
    // TODO: Declare any necessary private members
    private:
        float prevTotalCPUtime;
        float prevIdleCPUtime;
        vector<long> convertToLong(vector<string> values);
};

#endif