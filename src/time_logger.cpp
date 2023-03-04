
#include "time_logger.h"
#include <iomanip>
#include <sstream>

namespace pandora {

    TimeLogger::TimeLogger(bool enableModule)
        : bEnable(enableModule)
        , mTimeSum(0)
    {}

    void TimeLogger::Reset()
    {
        if (!bEnable) return;
        for (auto & it: ptimes)
        {
            it.second = 0;
        }
        mTimeSum = 0;
    }

    void TimeLogger::Start()
    {
        if (!bEnable) return;
        watch.Stop();
    }

    void TimeLogger::operator() (const std::string& item, bool resetTime)
    {
        if (!bEnable) return;
        double etime = watch.Stop();

        if (resetTime)
        {
            ptimes[item] = etime;
        }
        else
        {
            ptimes[item] += etime;
        }

        watch.Stop();

        mTimeSum += etime;
    }

    double TimeLogger::GetTime(const std::string& item) const
    {
        return ptimes.at(item);
    }

    double TimeLogger::GetTotalTime() const
    {
        return mTimeSum;
    }

    std::string TimeLogger::ShowResult(int type) const
    {
        if (!bEnable) return "";

        int maxStringLength(0);
        for (const auto& it : ptimes)
        {
            maxStringLength = std::max(maxStringLength, static_cast<int>(it.first.size()));
        }

        maxStringLength++;

        double sum_of_time(0.0);
        std::string unit;
        switch (type)
        {
        case TIME_LOGGER_MICROSECOND:
            unit = std::string("[us]");
            break;
        case TIME_LOGGER_MILLISECOND:
            unit = std::string("[ms]");
            break;
        case TIME_LOGGER_SECOND:
            unit = std::string("[ s]");
            break;
        }

        const int maxFieldWidth = (maxStringLength + 16 > std::numeric_limits<int>::max())
            ? std::numeric_limits<int>::max() : maxStringLength + 16;

        std::ostringstream output;

        output << std::left << std::setw(maxStringLength) << "Item" << "Elapsed Time " << unit << std::endl;
        output << std::setfill('-') << std::setw(maxFieldWidth) << "-" << std::endl;
        output << std::setfill(' ');

        // write down on screen
        for (const auto& it : ptimes)
        {
            double etime = static_cast<double>(it.second);
            switch (type)
            {
            case TIME_LOGGER_MICROSECOND:
                etime *= 1000000;
                break;
            case TIME_LOGGER_MILLISECOND:
                etime *= 1000;
                break;
            case TIME_LOGGER_SECOND:
                break;
            }

            output << std::left << std::setw(maxStringLength) << it.first << std::fixed << std::setprecision(4) 
                << std::setw(10) << etime << " " << unit << std::endl;
            sum_of_time += it.second;
        }

        output << std::setfill('-') << std::setw(maxFieldWidth) << "-" << std::endl;
        output << std::setfill(' ');
        output << std::left << std::setw(maxStringLength) << "Total Time : " << std::fixed << std::setprecision(4) 
            << std::setw(10) << sum_of_time << " " << unit << std::endl;


        return output.str();
    }
} 