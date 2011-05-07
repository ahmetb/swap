#include <stdio.h>
#include <stdlib.h>

#define USAGE "usage:\tswap FILE1 FILE2\n\texchange names of two files or folders"
#define TMP_FILENAME_TEMPLATE ".%s.swap.tmp" //some magic string
#define TMP_FILENAME_BUFSIZE 1000
#define REN_ERR "Unable to rename" 
#define REN_ERR_EXITCODE 2

int main(int argc,char** argv){
	if (argc!=3){
		printf("%s\n", USAGE);
		exit(1);
	}
	
	char* fn1 = argv[1];
	char* fn1_tmp = (char*)(malloc(sizeof(char)*TMP_FILENAME_BUFSIZE));
	sprintf(fn1_tmp, TMP_FILENAME_TEMPLATE, fn1);
	char* fn2 = argv[2];
		
	// first rename
	if (rename(fn1, fn1_tmp) == -1){
		perror(REN_ERR);
		exit(REN_ERR_EXITCODE);
	}
	
	// second rename
	if (rename(fn2, fn1) == -1){
		// recover previous rename
		rename(fn1_tmp, fn1); // do not handle err
		
		perror(REN_ERR);
		exit(REN_ERR_EXITCODE);
	}
	
	// third rename
	if (rename(fn1_tmp, fn2) == -1){
		// recover previous renames
		rename(fn1, fn2); // do not handle error
		rename(fn1_tmp, fn1); // do not handle error
		
		perror(REN_ERR);
		exit(REN_ERR_EXITCODE);
	}
	
	return 0;
}