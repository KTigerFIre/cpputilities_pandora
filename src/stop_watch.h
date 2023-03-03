#pragma once

#include <chrono>

namespace pandora
{
    class StopWatch
    {
    public:
        // Type aliases for clarity
        using clock_t = std::chrono::steady_clock;
        using time_point_t = std::chrono::time_point<clock_t >;

        // Default constructor (no initialization needed)
        StopWatch() = default;

        /**
         * Start the stopwatch by recording the current time point.
         */
        void Start()
        {
            mStart = clock_t::now();
        }

        /**
         * Stop the stopwatch and return the elapsed time in seconds.
         *
         * @tparam T The duration type to use. Defaults to double.
         * @return The elapsed time in seconds.
         */

        template<typename T = double>
        T Stop()
        {
            mEnd = clock_t::now();
            std::chrono::duration<T> elapsed_seconds = mEnd - mStart;
            mStart = mEnd;

            return elapsed_seconds.count();
        }

        /**
         * Reset the stopwatch by recording the current time point.
         */
        void reset()
        {
            mStart = clock_t::now();
        }

        /**
         * Pause the stopwatch by recording the elapsed time since the last start/reset.
         */
        void pause()
        {
            mPausedTime += clock_t::now() - mStart;
        }

        /**
         * Resume the stopwatch by subtracting the paused time from the current time point.
         */
        void resume()
        {
            mStart = clock_t::now() - mPausedTime;
            mPausedTime = time_point_t::duration::zero();
        }

    protected:
        time_point_t  mStart;
        time_point_t  mEnd;
        time_point_t::duration mPausedTime = time_point_t::duration::zero();
    };
}