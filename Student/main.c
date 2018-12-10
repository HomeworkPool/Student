#include "structures.h"
#include "functions.h"
#include "view.h"
#include <stdio.h>
#include <conio.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	FILE* db = db_init("./student.dat");
	FILE* index = db_init("./student.index");
	if(errno) {
		printf("Fatal error: unable to initialize database file ./student.dat. error code #%d", errno);
		return 1;
	}
	//student gg[] = {print_insert()};
	//db_write(db, index, gg, 1);
	unsigned num = 0;
	student* stu = db_read(db, index, &num);
	while (true) {
		stu = print_index(stu, num, db, index);
	}
	fclose(db);
	fclose(index);
	return 0;
}