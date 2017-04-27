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
			printf("%s\n",Cache_Directory_Contents[i]);
			i++;
		}
		(void) closedir(Cache_Directory);
	}
	else{
		perror("Couldn't open cache diretory");
	}

	printf("\n%d\n", i);

	int j, k;
	size_t length;
	char* indexString = {"index"};
	char temp[5];
	char index[6];
	for(j = 0; j < i; ++j){
		for(k = 0; k < 5; ++k){
			temp[k] = Cache_Directory_Contents[j][k];
		}
		if(strcmp(indexString, temp)){
			strcpy(index, indexString);
			printf("%d", Cache_Directory_Contents[j][k]);
			if(isdigit(Cache_Directory_Contents[j][k] - '0')){
				index[5] = Cache_Directory_Contents[j][k];
				printf("%swe're gucci\n", index);
			}
			else{
				printf("Invalid index\n");
			}
			
		}
	}

	//FILE* LLC_size = fopen("/sys/devices/system/cpu/cpu0/cache/index3/size", r);
	//printf("%s", LLC_size);

	return 0;
}