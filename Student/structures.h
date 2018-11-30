#ifndef INC_GUARD_STRUCTURES
#define INC_GUARD_STRUCTURES

const char* sexes[] = {"Male", "Female"};

typedef enum {
	male, female
} SEX;

typedef struct {
	char* id;
	char* name;
	SEX sex;
	unsigned short age;
	char* _class;
} student;

#endif