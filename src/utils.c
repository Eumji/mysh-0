#include "utils.h"
#include <string.h>
#include<malloc.h>

void mysh_parse_command(const char* command, int *argc, char*** argv)
{
	int len = strlen(command);
	char ss[100][100]={0}; // to save datas(words) temporary
	int wordnum=-1; // number of words
	int isblank=1; // 0 : not blank, 1 : blank
	int wwhi=0; // it use for add characters(index)
	

	for(int i=0;i<len;i++){
		// if next character is blank
		if(command[i]==' ' || command[i] == '\t' || command[i] == '\n'){
			if(isblank==0)
				isblank=1;
		}

		// not blank
		else{
			if(isblank==1){ // if previous character is blank
				wordnum++; // increse number of word
				wwhi=0; // initialize index
				ss[wordnum][wwhi++] = command[i]; // add first character in next words
				isblank=0; // check not blank
			}
			else{
				ss[wordnum][wwhi++] = command[i]; // add next character in current words
			}
		}
	}

	if(wordnum == -1){ // if there is no words
		*argc = 1; 
		*argv = (char **)malloc(sizeof(char*));
		(*argv)[0] = (char*)malloc(sizeof(char));
		return;
	}

	// use malloc for words
	*argv = (char **)malloc(sizeof(char*) * (wordnum+1));
	for(int i=0;i<=wordnum;i++){
		// use malloc and copy words
		(*argv)[i]=(char*)malloc(sizeof(char)*(strlen(ss[i])+1));
		strcpy((*argv)[i], ss[i]);
	}

	*argc=wordnum+1;
}


