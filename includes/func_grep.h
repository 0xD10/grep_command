#ifndef FUNC_GREP_H_
#define FUNC_GREP_H_

void manual(int argc, char** argv);
FILE* open_file(char *file);
char* read_file(FILE* file);
void find_pattern(char* pattern, char* file_content);
char* adjust_pointer(char* file_content, char* result);
void output_colored(char* startofline, char* pattern);

#endif 
