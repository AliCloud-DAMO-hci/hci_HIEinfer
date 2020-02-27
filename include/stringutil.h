#pragma once

#include <string>
#include <vector>

class StringUtil final
{
public:
    static bool EndsWith(const std::string & value,const std::string & ending)
    {
        if (ending.size()>value.size()) return false;
        return std::equal(ending.rbegin(),ending.rend(),value.rbegin());
    }

    static void Trim(std::string & str) 
    {
        str.erase(str.find_last_not_of(" \t\r\n") + 1);
        str.erase(0, str.find_first_not_of(" \t\r\n"));
    }

    static std::vector<std::string> Split(const std::string& text, const char* sepStr)
    {
        return Split(text.c_str(),sepStr);
    }
    
    static std::vector<std::string> Split(const char * text, const char* sepStr)
    {
        std::vector<std::string> vec;
        std::string str(text);
        std::string sep(sepStr);
        size_t n = 0, old = 0;
        while (n != std::string::npos)
        {
            n = str.find(sep,n);
            if (n != std::string::npos)
            {
                if (n != old) 
                    vec.push_back(str.substr(old, n-old));
                n += sep.length();
                old = n;
            }
        }
        vec.push_back(str.substr(old, str.length() - old));
        return vec;
    }
};
