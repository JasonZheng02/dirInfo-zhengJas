#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>

void dirInfo(DIR *stream){
	struct dirent *entry = readdir(stream);
	int size;
	struct stat file;
	
	printf("Statistics for directory: %s\n", entry -> d_name);
	while(entry != NULL){
		stat(entry->d_name, &file);
		size += file.st_size;
		entry = readdir(stream);
	}
	printf("Total Directory Size: %d Bytes\n", size);
	
	printf("Directories:\n");
	rewinddir(stream);
	entry = readdir(stream);
	while (entry != NULL){
		stat(entry->d_name, &file);
		if (S_ISDIR(file.st_mode)){
			printf("\t%s\n", entry -> d_name);
		}
		entry = readdir(stream);
	}
	
	printf("Regular files:\n");
	rewinddir(stream);
	entry = readdir(stream);
	while (entry != NULL){
		stat(entry->d_name, &file);
		if (S_ISREG(file.st_mode)){
			printf("\t%s\n", entry -> d_name);
		}
		entry = readdir(stream);
	}
}

int main(int argc, char *argv[]){
	char* name = malloc(100);
	if(argc <= 1) {
        printf("Input directory name:\n");
        fgets(name,100,stdin);
		name[strlen(name)-1] = 0;
	}
	else {
		name = argv[1];
	}
	
	DIR *stream;
	stream = opendir(name);
	
	if (stream == NULL) {
    printf("Error: %s.\n Can not open %s\n", strerror(errno), name);
	}
	
	dirInfo(stream);
}