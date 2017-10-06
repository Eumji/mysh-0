#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <unistd.h>

// this guy, jusuk bbae!
#include "commands.h"

int validate_cd_argv(int argc, char** argv);
int validate_pwd_argv(int argc, char** argv);

char buf[256], change_buf[256], cur_buf[256];
int do_cd(int argc, char** argv) {
	
	getcwd(buf, sizeof(buf));

	if (!validate_cd_argv(argc, argv))
		return -1;

	char c =  argv[1][0];

	if(!strcmp(argv[1],"..")){
		int len = strlen(buf);
		int whi=0;
		for(int i=len-1;i>0;i--){
			if(buf[i]=='/'){whi=i; break;}
		}
		
		strncpy(change_buf,buf,whi);
		chdir(change_buf);
		
	}
	else if(!strcmp(argv[1], ".")){
		chdir(buf);	
	}
	else if(c=='/'){
		chdir(argv[1]);
	}
	else if(c=='~'){
		char usrname[256];
		
		getlogin_r(usrname, sizeof(usrname));
		
		strcpy(buf, "/home/");
		strcat(buf, usrname);

		if(strlen(argv[1])>1){
			strcpy(change_buf, argv[1]+1);
			strcat(buf,change_buf);
		}

		chdir(buf);
	}
	else{
		strcat(buf, argv[1]);

		chdir(buf);
	}


	return 0;
}

int do_pwd(int argc, char** argv) {
	if (!validate_pwd_argv(argc, argv))
		return -1;

	getcwd(buf, sizeof(buf));
	printf("%s\n", buf);
	

	return 0;
}

int validate_cd_argv(int argc, char** argv) {
	if(argc==1) return 0;
	if(argc>2) return 0;
	//else if (!(!strcmp(argv[1], "..")||!strcmp(argv[1], ".")||argv[1][0]=='/')) return 0;
	if(strcmp(argv[0], "cd")!=0) return 0;
	if(argv[1][0]=='.'){
		if(strlen(argv[1])>2){
			if(argv[1][2]=='.') return 0;
		}
	}
	return 1;
}

int validate_pwd_argv(int argc, char** argv) {
	if(argc>1) return 0;
	if(strcmp(argv[0],"pwd")!=0) return 0;

	return 1;
}

