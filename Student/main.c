#include "structures.h"
#include "functions.h"
#include "view.h"
#include <stdio.h>
#include <conio.h>
#include <errno.h>
#include <signal.h>

bool _exit_flag = false;

void signal_int_handler(int sig) {
    _exit_flag = true;
}

int main(int argc, char* argv[]) {
	signal(SIGINT, signal_int_handler); 
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
	//printf("%x", _getch());
	while (!_exit_flag) {
		print_index(&stu, &num, db, index);
	}
	fclose(db);
	fclose(index);
	return 0;
}