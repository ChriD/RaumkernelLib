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
#include <ctype.h>

namespace Raumkernel
{
    namespace Tools
    {
        class StringUtil
        {
            public:            

                static std::string ltrim(std::string  _s)
                {
                    _s.erase(_s.begin(), std::find_if(_s.begin(), _s.end(), std::not1(std::ptr_fun<int, int>(::isspace))));
                    return _s;
                }


                static std::string rtrim(std::string _s)
                {
                    _s.erase(std::find_if(_s.rbegin(), _s.rend(), std::not1(std::ptr_fun<int, int>(::isspace))).base(), _s.end());
                    return _s;
                }


                static std::string trim(std::string _s)
                {
                    return ltrim(rtrim(_s));
                }


                static std::string padL(std::string _s, const size_t _num, const char _paddingChar = ' ')
                {
                    if (_num > _s.size())
                        _s.insert(0, _num - _s.size(), _paddingChar);
                    return _s;
                }


                static std::string padR(std::string _s, const size_t _num, const char _paddingChar = ' ')
                {
                    _s.resize( _num, _paddingChar);
                    return _s;
                }


                static std::string center(std::string _s, int _width)
                {
                    _s = StringUtil::ltrim(StringUtil::rtrim(_s));
                    return std::string((_width - _s.length()) / 2, ' ') + _s;
                }
        };
            
    }
}