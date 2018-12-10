#ifndef INC_GUARD_STRUCTURES
#define INC_GUARD_STRUCTURES
#include <stdbool.h>

const char* sexes[] = {"Male", "Female"};

typedef enum {
	male, female
} SEX;

typedef struct __student {
	char* id;
	int id_length;
	char* name;
	int name_length;
	SEX sex;
	unsigned short age;
	char* _class;
	int _class_length;
	struct __student* next;
} student;

#endif