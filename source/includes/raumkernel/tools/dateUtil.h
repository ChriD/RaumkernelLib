//
// The MIT License (MIT)
//
// Copyright (c) 2015 by ChriD
//
// Permission is hereby granted, free of charge,  to any person obtaining a copy of
// this software and  associated documentation  files  (the "Software"), to deal in
// the  Software  without  restriction,  including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software,  and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this  permission notice  shall be included in all
// copies or substantial portions of the Software.
//
// THE  SOFTWARE  IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE  LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY, WHETHER
// IN  AN  ACTION  OF  CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <chrono>

#include <raumkernel/tools/stringUtil.h>

namespace Raumkernel
{
    namespace Tools
    {
        struct DateTimeStamp
        {
            unsigned int day;
            unsigned int month;
            unsigned int year;
            unsigned int hour;
            unsigned int minute;
            unsigned int second;
            unsigned int millisecond;
        };
            

        class DateUtil
        {
            public:

                static DateTimeStamp getCurrentDateTimeStamp()
                {
                    auto timePoint = std::chrono::steady_clock::now();
                    auto timeNow = std::chrono::steady_clock::to_time_t(timePoint);
                    auto miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());
                    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(miliseconds);
                    std::size_t fractionalSeconds = miliseconds.count() % 1000;                    

                    // localtime is not thread save! There would be localtime_r(Linux) and localtime_s(Windows)
                    struct tm *localTimeNow = localtime(&timeNow);

                    DateTimeStamp cur;
                    cur.day         = localTimeNow->tm_mday;
                    cur.month       = localTimeNow->tm_mon + 1;
                    cur.year        = localTimeNow->tm_year + 1900;
                    cur.hour        = localTimeNow->tm_hour;
                    cur.minute      = localTimeNow->tm_min;
                    cur.second      = localTimeNow->tm_sec;
                    cur.millisecond = fractionalSeconds;
                    return cur;
                }                                
                
        };

    }
}