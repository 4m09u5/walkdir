#pragma once

struct Options {
    char* directory;
    char onlySymlinks;
    char onlyDirectories;
    char onlyFiles;
    char sort;
};

struct Options parseOptions(int argc, char** argv);