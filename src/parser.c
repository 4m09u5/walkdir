#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

struct Options parseOptions(int argc, char** argv) {
    struct Options options = {NULL, 0, 0, 0, 0};
    
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') {
            for(int j = 1; argv[i][j] != '\0'; j++) {
                switch(argv[i][j]) {
                    case 'l':
                        options.onlySymlinks = 1;
                        break;
                    case 'd':
                        options.onlyDirectories = 1;
                        break;
                    case 'f':
                        options.onlyFiles = 1;
                        break;
                    case 's':
                        options.sort = 1;
                        break;
                    default:
                        printf("Unknown option '%c'\n", argv[i][j]);
                        exit(1);
                }
            }
        }
        else {
            if(!options.directory) {
                options.directory = argv[i];
            }
            else {
                printf("Path was already provided (first match: '%s', confict: '%s')\n", options.directory, argv[i]);
                exit(1);
            }
        }
    }

    if((options.onlySymlinks || options.onlyDirectories || options.onlyFiles) == 0) {
        options.onlySymlinks = 1;
        options.onlyDirectories = 1;
        options.onlyFiles = 1;
    }

    if(options.directory == 0) {
        options.directory = "./";
    }

    return options;
}