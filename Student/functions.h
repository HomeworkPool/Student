#ifndef INC_GUARD_FUNCTIONS
#define INC_GUARD_FUNCTIONS

#include "structures.h"
#include <io.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define F_OK 0

inline int get_int() {
	setvbuf(stdin, NULL, _IOFBF, 16384);
	int temp;
	scanf_s("%d", &temp);
	return temp;
}

/**
 * Read a line from console
 * @param target target to write result
 * @param max
 * @return length of string
 */
inline int get_line(char** target, unsigned max) {
	setvbuf(stdin, NULL, _IOFBF, 16384);
	char* buffer = (char*)calloc(max + 2, sizeof(char));
	char input = getchar();
	unsigned i;
	if(input == '\n') {
		i = 0;
	} else {
		i = 1;
		buffer[0] = input;
	}
	for (; (input = getchar()) != '\n' && i < max; i++)
		buffer[i] = input;
	buffer[i+1] = '\0';
	strcpy_s(*target, i+1, buffer);
	free(buffer);
	return i+1;
}

inline char* cat(char* a, char* b) {
	const unsigned buffer_size = sizeof(char) * (strlen(a) * strlen(b) + 2);
	char* buffer = malloc(buffer_size);
	strcpy_s(buffer, buffer_size, a);
	strcat_s(buffer, buffer_size, b);
	return buffer;
}

inline int get_line_info(const char* info, char** target, unsigned max) {
	printf("%s [Up to %d words]: ", info, max);
	return get_line(target, max);
}

inline errno_t create_empty_file(const char* path) {
	errno_t err;
	FILE* stream = NULL;
	err = fopen_s(&stream, path, "w");
	fclose(stream);
	return err;
}

inline FILE* db_init(const char* path) {
	errno_t err;
	FILE* stream = NULL;
	if(_access(path, F_OK) == -1)
		create_empty_file(path);
	err = fopen_s(&stream, path, "rb+");
	if(err)
		errno = err;
	return stream;
}

inline void db_write(FILE* file, FILE* index, student* data, unsigned num) {
	fseek(file, 0L, SEEK_SET);
	fseek(index, 0L, SEEK_SET);
	fwrite(data, sizeof(student), num, file);
	fprintf_s(index, "%d\n", num);
	for (unsigned i = 0; i < num; i++) {
		fwrite(data[i].id, data[i].id_length, 1, index);
		fwrite(data[i].name, data[i].name_length, 1, index);
		fwrite(data[i]._class, data[i]._class_length, 1, index);
	}
	fflush(file);
	fflush(index);
}

inline student* db_read(FILE* file, FILE* index, unsigned* _num) {
	fseek(file, 0L, SEEK_END);
	const long size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	student* buffer = malloc(size);
	fread_s(buffer, size, size, 1, file);
	const unsigned num = 0;
	fseek(index, 0L, SEEK_SET);
	fscanf_s(index, "%u\n", &num);
	for (unsigned i = 0; i < num; i++) {
		buffer[i].name = calloc(buffer[i].name_length + 2, sizeof(char));
		buffer[i].id = calloc(buffer[i].id_length + 2, sizeof(char));
		buffer[i]._class = calloc(buffer[i]._class_length + 2, sizeof(char));
		fread_s(buffer[i].id, buffer[i].id_length + 1, buffer[i].id_length, 1, index);
		fread_s(buffer[i].name, buffer[i].name_length + 1, buffer[i].name_length, 1, index);
		fread_s(buffer[i]._class, buffer[i]._class_length + 1, buffer[i]._class_length, 1, index);
		buffer[i].name[buffer[i].name_length + 1] = '\0';
		buffer[i].id[buffer[i].id_length + 1] = '\0';
		buffer[i]._class[buffer[i]._class_length + 1] = '\0';
	}
	*_num = num;
	return buffer;
}

inline char* get_sex(unsigned short in) {
	return in == 1 ? "Female" : "Male";
}

inline bool stu_insert(student** source, unsigned* num, student data) {
	student* new_ptr = realloc(*source, sizeof(*source) + sizeof(student) * sizeof(data));
	if(new_ptr != NULL) {
		*source = new_ptr;
		(*source)[*num].name = data.name;
		(*source)[*num].age = data.age;
		(*source)[*num].id = data.id;
		(*source)[*num].id_length = data.id_length;
		(*source)[*num].name_length = data.name_length;
		(*source)[*num].sex = data.sex;
		(*source)[*num]._class = data._class;
		(*source)[*num]._class_length = data._class_length;
		(*num)++;
		return true;
	} else {
		return false;
	}
	(*num)++;
	return true;
}

inline bool stu_delete(student** source, unsigned* num, unsigned key) {
	for (unsigned i = key; i < *num - 1; i++) {
		(*source)[i].name = (*source)[i + 1].name;
		(*source)[i].age = (*source)[i + 1].age;
		(*source)[i].id = (*source)[i + 1].id;
		(*source)[i].id_length = (*source)[i + 1].id_length;
		(*source)[i].name_length = (*source)[i + 1].name_length;
		(*source)[i].sex = (*source)[i + 1].sex;
		(*source)[i]._class = (*source)[i + 1]._class;
		(*source)[i]._class_length = (*source)[i + 1]._class_length;
	}
	(*num)--;
}

#endif