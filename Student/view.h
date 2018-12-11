#ifndef INC_GUARD_VIEW
#define INC_GUARD_VIEW

#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include "structures.h"
#ifdef _WIN32
#include <windows.h>
#endif

inline void clean() {
#ifdef _WIN32
	system("cls"); // for windows
#else
	printf("\033[2J") // for unix
#endif
}

inline void set_pos(int x, int y) {
#ifdef _WIN32
	COORD point = {x,y};
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
#else
	printf("\033[%d;%dH", (x), (y));
#endif
}

inline void title(char* str) {
#ifdef _WIN32
	system(cat("title ", str)); // for windows
#endif
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


inline student print_insert() {
	clean();
	char* page_title = "Insert Record - Student Information Manager";
	title(page_title);
	puts("============================== Insert Record =============================");
	student stu;
	stu.id = malloc(31);
	stu.name = malloc(101);
	stu._class = malloc(31);
	stu.id_length = get_line_info("ID", &stu.id, 30);
	stu.name_length = get_line_info("Name", &stu.name, 100);
	stu._class_length = get_line_info("Class", &stu._class, 30);
	stu.age = 0;
	printf("Age: ");
	scanf_s("%hu", &stu.age);
	printf("Sex: ");
	stu.sex = give_opinions(2, sexes);
	return stu;
}


inline student* print_index(student** stu, unsigned *num, FILE* db, FILE* index) {
	clean();
	title("Student Information Manager");
	puts("======================= Student Information Manager =======================");
	printf("[I] Insert  [D] Delete  [E] Edit  [PgDn] Next Page  [PgUp] Last Page\n\n");
	printf("%6s | %15s | %15s | %9s | %11s | %4s\n", "Key", "Student ID", "Full Name", "Class", "Sex", "Age");
	for (unsigned i = 0; i < *num; i++) {
		printf("%6u | %15s | %15s | %9s | %11s | %4u\n", i, (*stu)[i].id, (*stu)[i].name, (*stu)[i]._class, get_sex((*stu)[i].sex), (*stu)[i].age);
	}

	switch (_getch()) {
		case 0x52:
		case 'i':
			//printf("[Insert] After Key (0 for end): ");
			//unsigned insert_key;
			//scanf_s("%d", &insert_key);
			student new_student = print_insert();
			if (stu_insert(stu, num, new_student))
				db_write(db, index, *stu, *num);
			else
				puts("Operation Failed. realloc() failed.");
			break;

		case 'E':
		case 'e':
			break;

		case 0x53:
		case 'd':
			printf("[Delete] Key: ");
			unsigned delete_key = get_int();
			stu_delete(stu, num, delete_key);
			db_write(db, index, *stu, *num);
			break;

		case 0x49: //Page Up
			break;

		case 0x51: //Page Down
			break;
	}
	//const char* opinions[] = {"Show All Students", "Insert a new record"};
	//return give_opinions(2, opinions);
}

#endif