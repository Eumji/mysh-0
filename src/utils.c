#include "utils.h"
#include <string.h>
#include<malloc.h>

void mysh_parse_command(const char* command, int *argc, char*** argv)
{
	int len = strlen(command);
	char ss[100][100]={0};
	int wordnum=-1;
	int isblank=1;
	int wwhi=0;
	//argv's (wordnum,wwhi)
	
	for(int i=0;i<len;i++){
		if(command[i]==' ' || command[i] == '\t' || command[i] == '\n'){
			if(isblank==0)
				isblank=1;
		}
		else{
			if(isblank==1){
				wordnum++;
				wwhi=0;
				ss[wordnum][wwhi++] = command[i];
				isblank=0;
			}
			else{
				ss[wordnum][wwhi++] = command[i];
			}
		}
	}

	if(wordnum == -1){
		*argc = 1;
		*argv = (char **)malloc(sizeof(char*));
		(*argv)[0] = (char*)malloc(sizeof(char));
		return;
	}

	*argv = (char **)malloc(sizeof(char*) * (wordnum+1));
	for(int i=0;i<=wordnum;i++){
		(*argv)[i]=(char*)malloc(sizeof(char)*(strlen(ss[i])+1));
		strcpy((*argv)[i], ss[i]);
	}

	*argc=wordnum+1;
}


