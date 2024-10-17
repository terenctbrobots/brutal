#ifndef HELPER_H
#define HELPER_H
#include <string>

using std::string;

string GetJSONFilename(string const &file_name) 
{
    string return_string;

    // Scan from back to front to then copy remaining string
    for (auto it=file_name.end(); it != file_name.begin(); it--)
    {
        if (*it == '.')
        {
            for (auto copyit=file_name.begin(); copyit != it; copyit++) 
            {
                return_string += *copyit;
            }
            break;
        }
    }

    if (return_string.length() > 0) {
        return_string += ".json";
        return_string;
    }

    return return_string;
}


#endif