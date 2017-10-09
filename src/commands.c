#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <pwd.h>
#include "commands.h"

int validate_cd_argv(int argc, char** argv);
int validate_pwd_argv(int argc, char** argv);

char buf[256], change_buf[256], cur_buf[256];
char temp[256]; 
char usr_name[256];

int do_cd(int argc, char** argv) {

	getcwd(buf, sizeof(buf)); // get current directory

	if (!validate_cd_argv(argc, argv)) // validate
		return 1;

	// move directory
	
	if(argv[1][0] != '~') chdir(argv[1]); // i made target directory in validate function. and i use it
	
	else chdir(temp);

	return 0;
}

int do_pwd(int argc, char** argv) {
	if (!validate_pwd_argv(argc, argv)) // validate
		return 1;

	getcwd(buf, sizeof(buf)); // get current directory
	
	fprintf(stderr, "%s\n", buf); // print using stderr stream
	
	return 0;
}

int validate_cd_argv(int argc, char** argv) {

	if(argc == 1) return 0; // cd argc must be 2

	if(argc > 2) return 0; // cd argc must be 2

	if(strcmp(argv[0], "cd")!=0) return 0; // command check

	getcwd(cur_buf, sizeof(cur_buf)); // save current directory

	int flag = 0; // -1 : error

	if(argv[1][0] == '~'){ // '~' need user name

		memset(temp, 0, sizeof(temp));

		struct passwd *pw; // for get user name

		uid_t uid;

		uid = geteuid();

		pw = getpwuid(uid);

		// make target directory
		strcpy(temp, "/home/");

		strcat(temp,pw->pw_name);

		strcat(temp, argv[1]+1); 

		flag = chdir(temp); // check if it work rightly
	}

	// except '~', we can use argv[1] to directory
	else flag = chdir(argv[1]); // check if it work rightly.

	chdir(cur_buf); // move to original directory

	if(flag == -1) return 0;

	return 1;
}

int validate_pwd_argv(int argc, char** argv) {
	if(argc>1) return 0; // pwd argc must be 1

	if(strcmp(argv[0],"pwd")!=0) return 0; // command check

	return 1;
}

