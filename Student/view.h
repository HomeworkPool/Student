#ifndef INC_GUARD_VIEW
#define INC_GUARD_VIEW

#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include "structures.h"
#include "functions.h"
#ifdef _WIN32
#include <windows.h>
#endif
#define PAGE_ITEM_LIMIT 19

unsigned index_current_page = 0;

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
	printf("Age: ");
	stu.age = get_unsigned();
	printf("Sex: ");
	stu.sex = give_opinions(2, sexes);
	return stu;
}

inline void print_edit(student** stu, unsigned key) {
	clean();
	char* page_title = "Edit Record - Student Information Manager";
	title(page_title);
	puts("=============================== Edit Record ==============================");
	printf("%15s | %15s | %13s | %7s | %4s\n", "Student ID", "Full Name", "Class", "Sex", "Age");
	printf("%15s | %15s | %13s | %7s | %4u\n", (*stu)[key].id, (*stu)[key].name, (*stu)[key]._class, get_sex((*stu)[key].sex), (*stu)[key].age);
	puts("==========================================================================");
	char* options[] = {"Back ...", "Student ID", "Full Name", "Class", "Sex", "Age"};
	int target = give_opinions(6, options);
	switch (target) {
		case 1:
			puts("\nEditing: Student ID");
			(*stu)[key].id_length = get_line_info("ID", &(*stu)[key].id, 30);
			break;

		case 2:
			puts("\nEditing: Full Name");
			(*stu)[key].name_length = get_line_info("Name", &(*stu)[key].name, 100);
			break;

		case 3:
			puts("\nEditing: Class");
			(*stu)[key]._class_length = get_line_info("Class", &(*stu)[key]._class, 30);
			break;

		case 4:
			puts("\nEditing: Sex");
			printf("Sex: ");
			(*stu)[key].sex = give_opinions(2, sexes);
			break;

		case 5:
			puts("\nEditing: Age");
			printf("Age: ");
			(*stu)[key].age = get_unsigned();
			break;
	}
}


inline student* print_index(student** stu, unsigned *num, FILE* db, FILE* index) {
	clean();
	title("Student Information Manager");
	puts("======================= Student Information Manager =======================");
	printf("[I] Insert  [D] Delete  [E] Edit  [O] Order By  [Home] First [End] End Page\n\n");
	printf("%6s | %15s | %15s | %13s | %7s | %4s\n", "Key", "Student ID", "Full Name", "Class", "Sex", "Age");
	unsigned i;
	bool allow_pgdn = false;
	for (i = index_current_page * PAGE_ITEM_LIMIT; i < (index_current_page+1) * PAGE_ITEM_LIMIT && i < *num; i++) {
		printf("%6u | %15s | %15s | %13s | %7s | %4u\n", i, (*stu)[i].id, (*stu)[i].name, (*stu)[i]._class, get_sex((*stu)[i].sex), (*stu)[i].age);
	}
	const unsigned index_max_page = *num / PAGE_ITEM_LIMIT;
	if (i < *num) 
		allow_pgdn = true;
	printf("Page: %u / %u %33s %30s\n", index_current_page+1, index_max_page + 1, "[PgDn] Next Page", "[PgUp] Previous Page");
	int key = _getch();
	switch (key) {
		case 0x52:
		case 'i':
		case 49:
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
			printf("[Edit] Key: ");
			unsigned edit_key = get_int();
			if(edit_key <= *num) {
				print_edit(stu, edit_key);
				db_write(db, index, *stu, *num);
			}
			break;

		case 0x53:
		case 'd':
		case 44:
			printf("[Delete] Key: ");
			unsigned delete_key = get_int();
			if(delete_key <= *num) {
				stu_delete(stu, num, delete_key);
				db_write(db, index, *stu, *num);
			}
			break;
			
		case 0x49: //Page Up
			if(index_current_page >= 1)
				index_current_page--;
			break;

		case 0x51: //Page Down
			if(allow_pgdn)
				index_current_page++;
			break;

		case 71:
			index_current_page = 0;
			break;

		case 79:
			index_current_page = index_max_page;
			break;
	}
	//const char* opinions[] = {"Show All Students", "Insert a new record"};
	//return give_opinions(2, opinions);
}

#endif