#include <stdio.h>
#include "../includes/func_grep.h"

int main(int argc, char** argv){
    FILE *file;
    char *file_content;
    
    manual(argc,argv);
    file = open_file(argv[argc-2]);
    file_content = read_file(file);
    find_pattern(file_content, argv[argc-1]);
        
    return 0;
}


