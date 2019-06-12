#ifndef ERROR_H
#define ERROR_H

namespace Sokoban {
;

enum class Error
{
    NoError = 0,
    FileNotFound,
    InvalidMapFileStructure,
    NoMapsFound,
    FileError,
};

constexpr const char* errorToChars(const Error error)
//inline operator char*(const Error& error)
{
    switch (error)
    {
        case Error::NoError:
            return "No Error";
        case Error::FileNotFound:
            return "File not found";
        case Error::FileError:
            return "File Error";
        case Error::InvalidMapFileStructure:
            return "Invalid map file structure";
    }

    return  "Unknow";
}

inline bool operator !(Error err)
{
    return  err == Error::NoError;
}

}

#endif // ERROR_H
