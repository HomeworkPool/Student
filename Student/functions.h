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

/**
 * Read a line from console
 * @param target target to write result
 * @param max
 */
inline void get_line(char** target, unsigned max) {
	char* buffer = (char*)calloc(max + 1, sizeof(char));
	char input;
	unsigned i = 0;
	for (; (input = getchar()) != '\n' && i < max; i++)
		buffer[i] = input;
	buffer[i+1] = '\0';
	strcpy_s(*target, i+1, buffer);
	free(buffer);
}

inline void get_line_info(const char* info, char** target, unsigned max) {
	printf("%s [Up to %d words]: ", info, max);
	get_line(target, max);
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

inline size_t db_write(FILE* file, student data[]) {
	return fwrite(data, sizeof(student), sizeof(data), file);
}

inline void db_read(FILE* file) {
	
}

#endif