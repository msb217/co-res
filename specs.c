#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(){

	DIR* Cache_Directory = opendir("/sys/devices/system/cpu/cpu0/cache/");
	struct dirent *ep;
	char **Cache_Directory_Contents;
	int i = 0;
	if(Cache_Directory != NULL){
		Cache_Directory_Contents = malloc[10][10];
		while(ep = readdir(Cache_Directory)){
			Cache_Directory_Contents[i] = ep->d_name;
			i++;
		}
		(void) closedir(Cache_Directory);
	}
	else{
		perror("Couldn't open cache diretory");
	}

	//FILE* LLC_size = fopen("/sys/devices/system/cpu/cpu0/cache/index3/size", r);
	//printf("%s", LLC_size);

	return 0;
}