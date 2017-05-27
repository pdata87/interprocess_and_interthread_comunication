//
// Created by pdata on 09.05.17.
//


#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

const char* concat_with_space(const char *s1, const char *s2)
{

    int new_string_size = strlen(s1)+strlen(s2)+2;
    char *result = malloc(new_string_size);//+1 for the zero-terminator


    //in real code you would check for errors in malloc here
    strcpy(result, s1);

    strcat(result, " ");
    strcat(result, s2);
    return result;

}
const char* concat_with_new_line(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, "\n");
    strcat(result, s2);
    return result;
}