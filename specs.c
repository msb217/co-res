#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(){

	DIR* Cache_Directory = opendir("/sys/devices/system/cpu/cpu0/cache/");
	struct dirent *ep;
	char* Cache_Directory_Contents[10];
	int i = 0;
	if(Cache_Directory != NULL){
		while(ep = readdir(Cache_Directory)){
			Cache_Directory_Contents[i] = ep->d_name;
			i++;
		}
		(void) closedir(Cache_Directory);
	}
	else{
		perror("Couldn't open cache diretory");
	}

	int j, k;
	size_t length;
	char* indexString = {"index"};
	char* index;

	for(j = 0; j < i; ++j){
		if(!strncmp("index", Cache_Directory_Contents[j], 5)){
			index = Cache_Directory_Contents[j];
		}
	}
	printf("%s\n", index);
	
	//Biggest Cache folder path
	char filePath[200];
	strcpy(filePath, "/sys/devices/system/cpu/cpu0/cache/");
	strcat(filePath, index);

	//Cache's line size
	char filePathLineSize[200];
	strcpy(filePathLineSize, filePath);
	strcat(filePathLineSize, "/coherency_line_size");

	char filePathNumberOfSets[200];
	strcpy(filePathNumberOfSets, filePath);
	strcat(filePathNumberOfSets, "/number_of_sets");

	char filePathSize[200];
	strcpy(filePathSize, filePath);
	strcat(filePathSize, "/size");

	char filePathWaysOfAssociativity[200];
	strcpy(filePathWaysOfAssociativity, filePath);
	strcat(filePathWaysOfAssociativity, "/ways_of_associativity");



	printf("%s\n", filePath);
	printf("%s\n", filePathLineSize);
	printf("%s\n", filePathNumberOfSets);
	printf("%s\n", filePathWaysOfAssociativity);

	
	int cacheSizeInt = getIntFromFile(filePathSize);
	int waysOfAssInt = getIntFromFile(filePathWaysOfAssociativity);
	int cacheLineSizeInt = getIntFromFile(filePathLineSize);
	int sets = getIntFromFile(filePathNumberOfSets);
	printf("%d\n%d\n%d\n%d\n", cacheSizeInt, waysOfAssInt, cacheLineSizeInt, sets);
	//int numberOf
	//int byteSize;

	return 0;
}

int getIntFromFile(char* filePath){

	FILE* LLC_size = fopen(filePath, "r");

	char c;
	char buf[8];
	int b = 0;
	int multiplier = 1;
	while((c = fgetc(LLC_size)) != EOF){
		if(isdigit(c)){
			buf[b++] = c;
		}
		else if(c == 'K' || c =='k'){
			multiplier = 1024;
		}
	}
	buf[b] = '\0';
	char cacheSize[b];
	strcpy(cacheSize, buf);
	int cacheSizeInt = atoi(cacheSize) * multiplier;

	return cacheSizeInt;
}