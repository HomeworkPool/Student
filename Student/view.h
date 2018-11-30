#ifndef INC_GUARD_VIEW
#define INC_GUARD_VIEW

#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include "structures.h"

inline void clean() {
	printf("%c[2K", 27);
	printf("\33[2K\r");
}

inline int give_opinions(int length, const char* opinions[]) {
	puts("Please choose an opinion: ");
	for (int i = 0; i < length; i++) {
		printf("%d. %s\n", i, opinions[i]);
	}
	int input;
	while (true) {
		input = _getch() - 48;
		if(input >= 0 && input < length) break;
	}
	return input;
}

inline int print_index() {
	clean();
	puts("================= Student Information Manager =================");
	const char* opinions[] = {"Show All Students", "Insert a new record"};
	return give_opinions(2, opinions);
}

inline student print_insert() {
	clean();
	puts("================= Insert Record =================");
	student stu;
	stu.id = malloc(31);
	stu.name = malloc(101);
	stu._class = malloc(31);
	get_line_info("ID", &stu.id, 30);
	get_line_info("Name", &stu.name, 100);
	stu.age = 0;
	printf("Age: ");
	scanf_s("%d", &stu.age);
	printf("Sex: ");
	stu.sex = give_opinions(2, sexes);
	get_line_info("Class", &stu._class, 100);
	return stu;
}

#endif