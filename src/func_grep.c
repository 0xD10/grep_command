#include <stdio.h>
#include <stdlib.h>
#include "../includes/func_grep.h"

long unsigned int strlen(char* x)
{
    int size_content = 0;
    
    while(x[size_content]!='\0'){
        size_content++;
    }
    
    return size_content;
}

char* strstr(char* file_content, char* pattern)
{
    int i,j;
    int size_fc = strlen(file_content);
    int size_pattern = strlen(pattern);
    
    for (i=0; i<size_fc; i++){
        if (file_content[i] == pattern[0]){
            j = i;
            while (file_content[j] == pattern[j-i]){
                j++;
            }
            if (j == (size_pattern+i)){
                return (file_content+i);
            }
        }
        
    }
    return NULL;
}

void find_pattern(char* file_content, char* pattern)
{
    int size_line;
    char *result;
    char temp_char;
    char *startofline;
    char *temp_start;

    while (strlen(file_content)>1){
        result = strstr(file_content, pattern);
        if(result!=NULL){
            startofline = adjust_pointer(file_content, result);
            size_line=0;
            while(startofline[size_line]!='\n'){
                size_line++;
            }
            temp_char = startofline[size_line+1];
            startofline[size_line+1] = '\0';
            output_colored(startofline, pattern);
            startofline[size_line+1] = temp_char;
            file_content = file_content+(strlen(file_content)-strlen(startofline)+size_line+1);
        }
        else{
            break;
        }
    }
}

void output_colored(char* startofline, char* pattern)
{
    int i, j, temp, count_duplicate;
    int *array_duplticate;
    char *check_duplicate;

    count_duplicate=0;
    check_duplicate = strstr(startofline, pattern);
    while(check_duplicate!=NULL){
        count_duplicate++;
        check_duplicate = strstr((check_duplicate+strlen(pattern)), pattern);
    }

    i=0;
    check_duplicate = strstr(startofline, pattern);
    if (check_duplicate!=NULL){
        array_duplticate = (int *)malloc((count_duplicate+1)*sizeof(int));
        array_duplticate[i] = strlen(startofline) - strlen(check_duplicate);
        for (i=1;i<count_duplicate;i++){
            check_duplicate = check_duplicate + strlen(pattern);
            check_duplicate = strstr(check_duplicate, pattern);
            array_duplticate[i] = strlen(startofline) - strlen(check_duplicate);
        }

        i=0;
        j=0;
        while(startofline[i]!='\n'){
            if (array_duplticate[j]==i){
                for(temp=0; temp<strlen(pattern); temp++){
                    printf("\e[1m\x1b[33m%c\x1b[0m\e[m", startofline[i]);
                    i++;
                }
                if (count_duplicate>0){
                    j++;
                }
            }
            printf("%c", startofline[i]);
            i++;
        }
        printf("%c", startofline[i]);
    }
}

char* adjust_pointer(char* file_content, char* result)
{
    int i; 
    int size;
    
    i=0;
    size = strlen(file_content) - strlen(result);
    while (file_content[size-i]!='\n' && size!=i){
        i++;
    }
    
    return (file_content+(size-i));
   
}

char* read_file(FILE* file)
{
    int fsize = 0;
    char *fcontent = NULL;
    
    fseek(file,0,SEEK_END);
    fsize = ftell(file);
    rewind(file);
    
    fcontent = (char*) malloc(sizeof(char) * fsize);
    fread(fcontent, 1, fsize, file);
    fclose(file);
    
    return fcontent;
}

FILE* open_file(char *file)
{
    FILE *fptr;
    
    fptr = fopen(file,"r");
    if (fptr == NULL){
        printf("Filename %s doesn't exist!\n",file);
        EXIT_FAILURE;
    }
    return fptr;
}

void manual(int argc, char** argv)
{
    switch (argc){
        case 1:
            printf("Usage: grep [FILENAME] [PATTERN]\n");
            exit(EXIT_FAILURE);
        case 2:
            printf("Missing [PATTERN] argument!\n");
            exit(EXIT_FAILURE);
    }
}

