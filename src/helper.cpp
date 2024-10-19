#include <fstream>

#include "helper.h"

std::string GetJSONFilename(std::string const &file_name) 
{
    std::string return_string;

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

std::optional<std::string> LoadTextFile(std::string const& file_name)
{
    std::ifstream file(file_name);

    if (!file.good()) 
    {
        return std::nullopt;
    }

    std::string file_contents((std::istreambuf_iterator<char> (file)),std::istreambuf_iterator<char>());

    return file_contents;
}
