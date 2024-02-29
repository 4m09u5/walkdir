#define _POSIX_SOURCE
#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "parser.h"

int comparator(const struct dirent** first, const struct dirent** second) {
	return strcoll((*first)->d_name, (*second)->d_name);
}

void walkDirectory(char* path, struct Options* options) {
	struct dirent** pDirent;
	
	int total = scandir(path, &pDirent, NULL, options->sort ? &comparator : NULL);

	if(total < 0) {
		printf("Cannot open directory %s\n", path);
		return;
	}

	for(int i = 0; i < total; i++) {
		struct stat fileinfo;

		char* newPath = calloc(strlen(path) + strlen(pDirent[i]->d_name) + 2, sizeof(char));
		strcpy(newPath, path);
		strcat(newPath, "/");
		strcat(newPath, pDirent[i]->d_name);

		lstat(newPath, &fileinfo);

		if(!strcmp(".", pDirent[i]->d_name) || !strcmp("..", pDirent[i]->d_name)) {
			free(newPath);
			free(pDirent[i]);
			continue;
		}

		if(S_ISDIR(fileinfo.st_mode)) {
			if(options->onlyDirectories)
				printf("%s\n", newPath);
			walkDirectory(newPath, options);
		}
		else if(S_ISLNK(fileinfo.st_mode) && options->onlySymlinks) {
			printf("%s\n", newPath);
		}
		else if(S_ISREG(fileinfo.st_mode) && options->onlyFiles) {
			printf("%s\n", newPath);
		}
		
		free(pDirent[i]);
		free(newPath);
	}
	free(pDirent);
}

int main(int argc, char** argv) {
	struct Options options = parseOptions(argc, argv);
	
	walkDirectory(options.directory, &options);

	return 0;
}
