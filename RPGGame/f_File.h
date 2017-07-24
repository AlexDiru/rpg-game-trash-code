#ifndef __file_function_H__
#define __file_function_H__

#include <vector>

int open_write(char* strFileName);
int open_read(char* strFileName);
int open_appened();

int close_file(char* mode);

int write_string(char* i);
int write_int(int i);
int write_float(float i);

char* read_string();
int read_int();
float read_float();

bool file_eof(char* mode);


#endif