#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Typedefs
typedef struct{
    char* username;
    char* password;
} User;

typedef struct{
    char* name;
    char* phone_num;
    char* email;   
} Contact;

// Function Declarations
void merge(Contact *arr, int left, int mid, int right, int option);
void merge_sort(Contact *arr, int left, int right, int option);
int endswith(const char *str, const char *suffix);
int alphanumeric(const char* str);
int validate(char* name_x, char* phone_num_x, char* email_x);
void toLowercase(char *str, char *lowerStr);
int check(char username[], char password[]);
int Display(char* file);
int Sort(char* file, int option);
int SignUp();
char* LogIn(char* file);
int Add(char* file);
int Delete(char* file);
int Search(char* file, int mode);
int Edit(char* file);


#endif // CONTACT_MANAGER_H
