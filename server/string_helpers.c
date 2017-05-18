//
// Created by pdata on 09.05.17.
//


#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

 char* concat_with_space( char *s1,  char *s2)
{

    int new_string_size = strlen(s1)+strlen(s2)+strlen(" ")+1;
    char *result =malloc(new_string_size);


    //in real code you would check for errors in malloc here
    strcpy(result, s1);

    strcat(result, " ");
    strcat(result, s2);

    return result;

}
 char* concat_with_new_line( char *s1,  char *s2)
{

    strcat(s1, "\n");
    strcat(s1, s2);


    return s1;
}