#include "structures.h"
#include "functions.h"
#include "view.h"
#include <stdio.h>
#include <conio.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	FILE* db = db_init("./student.dat");
	if(errno) {
		printf("Fatal error: unable to initialize database file ./student.dat. error code #%d", errno);
		return 1;
	}

	print_insert();
	return 0;
}