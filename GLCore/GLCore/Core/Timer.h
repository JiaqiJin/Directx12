#pragma once
#include <chrono>

namespace Kawaii
{
    class Timer final
    {
    public:
        static double getTime()
        {
            auto now = std::chrono::system_clock::now();

            return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count() / double(SECOND);
        }

    private:
        static const long long SECOND = 1000000000L;
    };
}