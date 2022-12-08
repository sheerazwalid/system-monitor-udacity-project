#ifndef FORMAT_H
#define FORMAT_H

#include <string>

using namespace std;

namespace Format {
    string ElapsedTime(long times);  // TODO: See src/format.cpp

    string Time_String(long time);
};                                    // namespace Format

#endif