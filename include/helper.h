#ifndef HELPER_H
#define HELPER_H
#include <string>

using std::string;

string GetJSONFilename(string const &file_name) 
{
    string return_string;

    for (auto it=file_name.begin(); it != file_name.end(); it++)
    {
        if (*it == '.')
        {
            break;
        }
        return_string+=*it;
    }

    return_string += ".json";

    return return_string;
}


#endif