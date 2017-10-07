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

	getcwd(buf, sizeof(buf));

	if (!validate_cd_argv(argc, argv))
		return 1;

	if(argv[1][0] != '~') chdir(argv[1]);
	else chdir(temp);

	return 0;
}

int do_pwd(int argc, char** argv) {
	if (!validate_pwd_argv(argc, argv))
		return 1;

	getcwd(buf, sizeof(buf));
	printf("%s\n", buf);

	return 0;
}

int validate_cd_argv(int argc, char** argv) {

	if(argc == 1) return 0;

	if(argc > 2) return 0;

	if(strcmp(argv[0], "cd")!=0) return 0;

	getcwd(cur_buf, sizeof(cur_buf));

	int flag = 0;

	if(argv[1][0] == '~'){

		memset(temp, 0, sizeof(temp));

		// get user id
		struct passwd *pw;

		uid_t uid;

		uid = geteuid();

		pw = getpwuid(uid);
		


		strcpy(temp, "/home/");

		strcat(temp,pw->pw_name);

		strcat(temp, argv[1]+1); 

		flag = chdir(temp);
	}

	else flag = chdir(argv[1]);

	chdir(cur_buf);

	if(flag == -1) return 0;

	return 1;
}

int validate_pwd_argv(int argc, char** argv) {
	if(argc>1) return 0;

	if(strcmp(argv[0],"pwd")!=0) return 0;

	return 1;
}

