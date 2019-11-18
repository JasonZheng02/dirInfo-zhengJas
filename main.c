#include <stdio.h>
#include <dirent.h>

int main(){
	DIR *stream;
	stream = opendir(".");
	struct dirent *entry = readdir(stream);
	int size;
	
	printf("Statistics for directory:\n");
	
	printf("Total Directory Size: %d Bytes\n", size);
	
	printf("Directories:\n");
	
	printf("%d\n", entry->d_ino);
	printf("%s\n", entry->d_name);
}