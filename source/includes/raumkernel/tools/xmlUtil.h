//
// The MIT License (MIT)
//
// Copyright (c) 2016 by ChriD
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
#ifndef RAUMKERNEL_XMLUTIL_H
#define RAUMKERNEL_XMLUTIL_H

#include <stdio.h>
#include <string>
#include <cstdint>
#include <random>
#include <locale>

#include <math.h>
#include <raumkernel/xml/pugixml/pugixml.hpp>

namespace Raumkernel
{
    namespace Tools
    {
        class XMLUtil
        {
            public:

                static std::string getChildNodeVal(const pugi::xml_node &_parentNode, const std::string &_nodeName, const std::string &_defaultVal = "")
                {
                    pugi::xml_node valueNode;
                    std::string value;

                    if (!_parentNode)
                        return _defaultVal;

                    valueNode = _parentNode.child(_nodeName.c_str());
                    if (!valueNode)
                        return _defaultVal;

                    return valueNode.child_value();
                }


                static std::string getNodeAttributeVal(const pugi::xml_node &_node, const std::string &_attributeName, const std::string &_defaultVal = "")
                {
                    pugi::xml_attribute attrib;
                    std::string value;

                    if (!_node)
                        return _defaultVal;

                    attrib = _node.attribute(_attributeName.c_str());
                    if (!attrib)
                        return _defaultVal;

                    return attrib.value();
                }
        };

    }
}


#endif