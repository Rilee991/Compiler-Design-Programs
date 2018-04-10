#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"closure_goto.h"
#include"parsingtable.h"
#include"first_follow.h"
#include"parse.h"

int main() {
	start();	//Compute closure and goto.
	printf("OK-1\n");
	initialize_first_follow();
	printf("OK-2\n");
	compute_first();
	printf("OK-3\n");
	compute_follow();
	printf("OK-4\n");

	create_parsing_table();
	printf("OK-5\n");

	parse();	//Parse the input string.

	return 0;
}
