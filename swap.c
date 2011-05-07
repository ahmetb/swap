/* swap - exchange names of two files or folders

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* 
 * Authors : ahmet alp balkan <ahmetalpbalkan at gmail.com>
 */

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
		// revert previous rename
		rename(fn1_tmp, fn1); // do not handle err
		
		perror(REN_ERR);
		exit(REN_ERR_EXITCODE);
	}
	
	// third rename
	if (rename(fn1_tmp, fn2) == -1){
		// revert previous renames
		rename(fn1, fn2); // do not handle error
		rename(fn1_tmp, fn1); // do not handle error
		
		perror(REN_ERR);
		exit(REN_ERR_EXITCODE);
	}
	
	return 0;
}
