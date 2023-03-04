#pragma once

#include <string>
#include "stop_watch.h"
#include <unordered_map>
#include <iostream>

namespace pandora
{
    class TimeLogger
    {
    public:
        TimeLogger(bool enableModule = false);

        static const int TIME_LOGGER_MICROSECOND = 0;
        static const int TIME_LOGGER_MILLISECOND = 1;
        static const int TIME_LOGGER_SECOND = 2;

        bool bEnable;
        void operator() (const std::string& item, bool resetTime = true);

        void Reset();
        void Start();
        double GetTime(const std::string& item) const;
        double GetTotalTime() const;
        std::string ShowResult(int type = TIME_LOGGER_MILLISECOND) const;

    private:
        StopWatch watch;
        std::unordered_map<std::string, double> ptimes;
        double mTimeSum;
    };

}