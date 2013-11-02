#ifndef ZPATH_H
#define ZPATH_H

#include "zstring.h"
#include "zarray.h"

#include <iostream>

#ifdef PLATFORM_WINDOWS
    #define ZPATH_DELIM '\\'
#else
    #define ZPATH_DELIM '/'
#endif

namespace LibChaos {

class ZPath {
public:
    ZPath();
    ZPath(const char *);
    ZPath(std::string);
    ZPath(ZString);
    //ZPath(ZString, bool);
    ZPath(ArZ arr);

    //ZPath &operator=(ZPath); // Default overload is fine
    //ZPath &operator=(ArZ);
    //bool operator==(ZPath); // Default overload is fine

    ZPath &concat(ZPath);
    ZPath &operator<<(ZPath);
    ZPath operator+(ZPath);

    ZString &operator[](unsigned);
    ZString &last();

    static ZPath pwd(); // Get a ZPath that represents the present working directory of the program
    ZPath &relTo(ZPath path); // Get a path from an absolute path that is a relative path to the same location, relative to <path>
    ZPath &parent(); // Get the path to the next directory up
    bool childTo(ZPath); // Needs REWRITE
    ZPath &sanitize(); // Gets most direct path (resolves .. in path, as best as possible)

    static ZPath getAbs(ZPath path); // Get absolute representation of path, based on present working directory
    ZPath &getAbs(); // Operates on object

    bool valid();
    ZPath &fix();
    static bool makeDir(ZPath);
    bool createDirsTo();

    ZString str(char delim = ZPATH_DELIM);

    unsigned depth();
    unsigned size();

    ArZ &dat();
    bool &abs();
#ifdef PLATFORM_WINDOWS
    char &drv();
#endif
private:
    void fromStr(ZString);

    ArZ _data;
    bool absolute;
#ifdef PLATFORM_WINDOWS
    char drive;
#endif
};

} // namespace LibChaos

#endif // ZPATH_H
