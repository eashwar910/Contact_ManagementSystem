#include "contacth.h"

// merging elements by comparing elements from each half
void merge(Contact *arr, int left, int mid, int right, int option)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Contact L[n1];
    Contact R[n2];

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {

        if (option == 1)
        {
            // comparing elements value (if they are names)
            if (strcmp(L[i].name, R[j].name) <= 0)
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        else if (option == 2)
        {
            // comparing elements value (if they are phone numbers)
            if (strcmp(L[i].phone_num, R[j].phone_num) <= 0)
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
        k++;
        }
    }

    // loading remaining elements from 1st half
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // loading remaining elements frm 2nd half
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// splitting array into halves recursively and merging them
void merge_sort(Contact *arr, int left, int right, int option)
{
    if (left < right)
    {
        int mid = left + ((right - left) / 2);

        merge_sort(arr, left, mid, option);
        merge_sort(arr, mid + 1, right, option);

        merge(arr, left, mid, right, option);
    }
}

// to determine if a string ends with a set sequence of characters
int endswith(const char *str, const char *suffix)
{
    int len;
    int lenx;

    len = strlen(str);
    lenx = strlen(suffix);
    if (lenx > len)
    {
        return 0;
    }
    if (strncmp(str + len - lenx, suffix, lenx) == 0)
    {
        return 1;
    }
    return 0;
}

// to determine if each character in the string is alphanumeric
int alphanumeric(const char* str)
{
    while (*str)
    {
        if (!(isalpha(*str) || isblank(*str)))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

// validations of input name, phone number and email
int validate(char* name_x, char* phone_num_x, char* email_x)
{
    int result;

    result = 1;
    // validation for email
    if (endswith(email_x, "@gmail.com") == 0)
    {
        result = 0;
    }
    // validation for phone numbers
    if (!(strncmp(phone_num_x, "+60", 3) == 0 || strncmp(phone_num_x, "+44", 3) == 0))
    {
        result = 0;
    }
    // validation for names
    if (alphanumeric(name_x) == 0)
    {
        result = 0;
    }
    return result;
}

void toLowercase(char *str, char *lowerStr) {  //function to make search feature case - insensitive
    for (int i = 0; str[i]; i++) {
        lowerStr[i] = tolower((unsigned char)str[i]);
    }
    lowerStr[strlen(str)] = '\0'; 
}

// to validate the username and password for user
int check(char username[], char password[])
{
    int result;

    result = 0;
    // username and password has to have more than 8 characters
    if (strlen(password) <= 8 || strlen(username) <= 8)
    {
        result--;
    }
    else
    {
        // password has to have one uppercase character, one lowercase character, one digit and one special character
        for (int i = 0; i < strlen(password); i++)
        {
            if (isupper(password[i]) || islower(password[i]) || isdigit(password[i]))
            {
                result++;
            }
            else if (!isalnum(password[i]) && !isspace(password[i]))
            {
                result++;
            }
        }
    }

    if (result != strlen(password))
    {
        return 0;
    }
    else
    {
        // all characters in password are valid
        return 1;
    }
}

// to display all the contacts belonging to the user
int Display(char* file) {
    FILE *filept;
    filept = fopen(file, "r");
    Contact scont[100];
    int count = 0;

    // When user does not have contacts
    if (filept == NULL) {
        printf("\033[1;31mError: File does not exist. Please add contacts first.\033[0m\n");
        return 0;
    }

    for (int i = 0; i < 100; i++) {
        scont[i].name = malloc(50 * sizeof(char));
        scont[i].phone_num = malloc(25 * sizeof(char));
        scont[i].email = malloc(50 * sizeof(char));
    }

    // Read contacts from file
    while (fscanf(filept, "%49[^,], %24[^,], %49[^\n]\n", scont[count].name, scont[count].phone_num, scont[count].email) != EOF) {
        count++;
    }

    // Print table header with borders
    printf("\033[1;34m+-----+--------------------------------+-----------------+--------------------------------+\033[0m\n");
    printf("\033[1;34m| %-3s | %-30s | %-15s | %-30s |\033[0m\n", "No.", "Name", "Phone Number", "Email");
    printf("\033[1;34m+-----+--------------------------------+-----------------+--------------------------------+\033[0m\n");

    // Print each contact as a row in the table
    for (int i = 0; i < count; i++) {
        printf("\033[1;34m| \033[1;33m%-3d\033[1;34m | \033[1;32m%-30s\033[1;34m | \033[1;36m%-15s\033[1;34m | \033[1;35m%-30s \033[1;34m|\033[0m\n",
               i + 1, scont[i].name, scont[i].phone_num, scont[i].email);
    }

    // If no contacts exist, display an empty message
    if (count == 0) {
        printf("\033[1;34m| %-3s | %-30s | %-15s | %-30s |\033[0m\n", "", "No contacts to display.", "", "");
    }

    // Print table footer with borders
    printf("\033[1;34m+-----+--------------------------------+-----------------+--------------------------------+\033[0m\n");

    // Free allocated memory
    for (int i = 0; i < 100; i++) {
        free(scont[i].name);
        free(scont[i].phone_num);
        free(scont[i].email);
    }

    fclose(filept);
    return 1;
}

int Sort(char* file, int option)
{
    FILE *filept;
    filept = fopen(file, "r");
    int size = 100;
    Contact scont[size];
    int count = 0;

    // allocate memory for array of structs
    for (int i = 0; i < 100; i++) {
        scont[i].name = malloc(50 * sizeof(char));
        scont[i].phone_num = malloc(25 * sizeof(char));
        scont[i].email = malloc(50 * sizeof(char));
    }

    // read data from file and store in array of structs
    while (fscanf(filept, "%49[^,], %49[^,], %49[^\n]\n", scont[count].name, scont[count].phone_num, scont[count].email) != EOF)
    {
        count++;
    }

    fclose(filept);

    if (option != 2)
    {
        option == 1;
    }
    // call sorting algorithms (sort by 1. name, 2. phone number)
    merge_sort(scont, 0, count - 1, option);

    // write data in array of structs to file
    FILE *writefile;
    writefile = fopen(file, "w");

    int j = 0;
    while(j < count)
    {
        fprintf(writefile, "%s, %s, %s\n", scont[j].name, scont[j].phone_num, scont[j].email);
        j++;
    }

    // free memory
    for (int i = 0; i < 100; i++) {
        free(scont[i].name);
        free(scont[i].phone_num);               
        free(scont[i].email);
    }
    printf("\033[1;32mContacts sorted successfully.\033[0m\n");

    fclose(writefile);
}

int SignUp()
{
    int result;
    int check_details;

    char username[50];
    char password[50];

    FILE *userfile;

    result = 0;
    check_details = 0;

    // prompt user for username
    printf("Enter username (more than 8 alphanumeric or special characters only) : ");
    scanf("%s", username);
    printf("\n");

    // prompt user for password
    printf("Enter password (must include characters: 1 uppercase, 1 lowercase, 1 special & 1 digit): ");
    scanf("%s", password);
    printf("\n");

    // validate username and password
    check_details = check(username, password);

    // create / open user file
    userfile = fopen("users.csv", "r+");
    User SavedUsers[100];

    // allocate memory for array of user structs
    for (int i = 0; i < 100; i++) 
    {
        SavedUsers[i].username = malloc(50 * sizeof(char));
        SavedUsers[i].password = malloc(50 * sizeof(char));
    }

    // read data from file to array of structs
    int count = 0;
    while (fscanf(userfile, "%49[^,], %49[^\n]\n", SavedUsers[count].username, SavedUsers[count].password) != EOF)
    {
        // check if username input by user is already in user file
        if (strcmp(SavedUsers[count].username, username) == 0)
        {
            check_details = 0;
            printf("User already exists\n");
            return result;
        }
        count++;
    }

    fclose(userfile);

    // create new user struct to store username and password and write them to the user file
    userfile = fopen("users.csv", "a");
    if (check_details)
    {
        User new_user;

        new_user.username = username;
        new_user.password = password;
        fprintf(userfile, "%s, %s\n", username, password);
        result = 1;
    }
    else
    {
        printf("Your data input was not valid\n");
    }
    fclose(userfile);

    if (result)
    {
        printf("User is created\n");
    }
    else
    {
        printf("User is not created\n");
    }

    return result;
}

char* LogIn(char* file)
{
    FILE *userfile = fopen("users.csv", "r");
    User SavedUsers[100];
    char contactFile[60] = "contact_";

    if (userfile == NULL) {
        printf("User file does not exist.\n");
        return NULL;
    }

    // Allocate memory for user struct
    for (int i = 0; i < 100; i++) {
        SavedUsers[i].username = malloc(50 * sizeof(char));
        SavedUsers[i].password = malloc(50 * sizeof(char));
    }

    int count = 0;
    // Read the user file into the User struct array
    while (fscanf(userfile, "%49[^,], %49[^\n]\n", SavedUsers[count].username, SavedUsers[count].password) != EOF)
    {
        count++;
    }
    fclose(userfile);

    // LogIn: Enter username and password
    char enteredUsername[50];
    char enteredPassword[50];

    printf("Enter username (username must exist in system): ");
    scanf("%49s", enteredUsername);
    printf("\n");

    printf("Enter password: ");
    scanf("%49s", enteredPassword);
    printf("\n");

    // Check if username and password exist in the user struct
    int userFound = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(SavedUsers[i].username, enteredUsername) == 0 && strcmp(SavedUsers[i].password, enteredPassword) == 0) {
            userFound = 1;

            // Set the user's contact file
            printf("Login successful! Accessing contact file for user: %s\n", enteredUsername);

            strcat(contactFile, enteredUsername);
            strcat(contactFile, ".csv");
            printf("User's contact file: %s\n", contactFile);
            strcpy(file, contactFile);

            break;
        }
    }

    // free memory allocated
    for (int i = 0; i < 100; i++) 
    {
        free(SavedUsers[i].username);
        free(SavedUsers[i].password);
    }

    if (!userFound) {
        printf("Error: Invalid username or password.\n");
        return NULL;
    }
    
    return file;
}


int Add(char* file)
{
    int result;
    int validate_result;

    char name[50];
    char phone_num[50];
    char email[50];

    FILE *filept;
    filept = fopen(file, "a+");

    validate_result = 0;

    // prompt user input of contact name
    printf("\033[1;36mEnter name: \033[0m");
    fgets(name, sizeof(name), stdin);
    printf("\n");
    
    name[strcspn(name, "\n")] = '\0';

    // prompt user input of phone number
    printf("\033[1;36mEnter phone number (UK or MY numbers only): \033[0m");
    scanf("%s", phone_num);
    printf("\n");

    // prompt user input of email
    printf("\033[1;36mEnter email (in '@gmail.com' format): \033[0m");
    scanf("%s", email);
    printf("\n");
    validate_result = validate(name, phone_num, email);

    result = 0;
    if (validate_result)
    {
        // create new contact, create new struct for contact and write new contact into file
        Contact new_contact;

        if (islower(name[0]))
        {
            name[0] = toupper(name[0]);
        }

        new_contact.name = name;
        new_contact.phone_num = phone_num;
        new_contact.email = email;
        fprintf(filept, "%s, %s, %s\n", name, phone_num, email);
        result = 1;
    }
    else
    {
        printf("\033[1;31mInvalid input.\033[0m\n");
    }
    fclose(filept);

    if (result)
    {
        Sort(file, 1);
        printf("\033[1;32mContact added successfully.\033[0m\n");
    }
    else
    {
        printf("\033[1;32mContact not added.\033[0m\n");
    }

    return result;
}

int Delete(char* file) {
    FILE *readfile;
    readfile = fopen(file, "r");
    Contact scont[100];

    if (readfile == NULL) {
        printf("\033[1;31mError: Contact file does not exist. Please add contacts first.\033[0m\n");
        return 0;
    }

    // allocate memory for array of structs to be read from file
    for (int i = 0; i < 100; i++) {
        scont[i].name = malloc(50 * sizeof(char));
        scont[i].phone_num = malloc(25 * sizeof(char));
        scont[i].email = malloc(50 * sizeof(char));
    }

    // read data from file and store in array of structs
    int count = 0;
    while (fscanf(readfile, "%49[^,], %49[^,], %49[^\n]\n", scont[count].name, scont[count].phone_num, scont[count].email) != EOF) {
        count++;
    }

    int choice;
    char sterm[50];

    // interface
    printf("\033[1;34m=========================================\033[0m\n");
    printf("\033[1;36m           DELETE CONTACT MENU          \033[0m\n");
    printf("\033[1;34m=========================================\033[0m\n");
    printf("\033[1;33mDelete by:\033[0m\n"); // Changed from red to yellow
    printf("\033[1;33m  1. Name\033[0m\n");
    printf("\033[1;33m  2. Phone Number\033[0m\n");
    printf("\033[1;33m  3. Email ID\033[0m\n");
    printf("\033[1;36mEnter your choice: \033[0m");
    scanf("%d", &choice);
    getchar();

    printf("\033[1;36mEnter search term: \033[0m");
    scanf(" %49[^\n]", sterm);

    char stermLower[50];
    toLowercase(sterm, stermLower);

    int matchedIndices[100];
    int matchCount = 0;

    for (int i = 0; i < count; i++) {
        int match = 0;

        if (choice < 1 || choice > 3) {
            printf("\033[1;31mInvalid choice! Returning to menu.\033[0m\n");
            break;
        }

        if (choice == 1) {  // Delete by Name
            char fieldLower[50];
            toLowercase(scont[i].name, fieldLower);
            if (strcmp(fieldLower, stermLower) == 0 || strstr(fieldLower, stermLower) != NULL) {
                match = 1;
            }
        } else if (choice == 2) {  // Delete by Phone Number
            char fieldLower[50];
            toLowercase(scont[i].phone_num, fieldLower);
            if (strcmp(fieldLower, stermLower) == 0 || strstr(fieldLower, stermLower) != NULL) {
                match = 1;
            }
        } else if (choice == 3) {  // Delete by Email
            char fieldLower[50];
            toLowercase(scont[i].email, fieldLower);
            if (strcmp(fieldLower, stermLower) == 0 || strstr(fieldLower, stermLower) != NULL) {
                match = 1;
            }
        }

        if (match) {
            matchedIndices[matchCount++] = i;
        }
    }

    // if no matches for the contact searched
    if (matchCount == 0) {
        printf("\033[1;31mNo matching contact found.\033[0m\n");
    // if 1 match for the contact searched
    } else if (matchCount == 1) {
        printf("\033[1;33mMatch Found:\033[0m\n");
        printf("\033[1;36m%d. Name: %s, Phone: %s, Email: %s\033[0m\n", 1, scont[matchedIndices[0]].name, scont[matchedIndices[0]].phone_num, scont[matchedIndices[0]].email);

        // ensure user picked intended content for deletion
        int delete_option = 0;
        printf("\033[1;33mAre you sure about deleting this contact? (1 for yes, 2 for no): \033[0m");
        scanf("%d", &delete_option);

        if (delete_option == 1) 
        {

            // deletion of contact
            printf("\033[1;32mDeleting contact: %s\033[0m\n", scont[matchedIndices[0]].name);
            for (int i = matchedIndices[0]; i < count - 1; i++) {
                scont[i] = scont[i + 1];
            }
            (count)--;
            printf("\033[1;32mContact deleted successfully.\033[0m\n");

        } 
        else
        {
            printf("\033[1;31mDelete operation cancelled.\033[0m\n");
        }

        // free memory allocated
        free(scont[matchedIndices[0]].name);
        free(scont[matchedIndices[0]].phone_num);
        free(scont[matchedIndices[0]].email);

    // if multiple matched for the contact searched
    } else {

        // display contacts that contain search string
        printf("\033[1;33mMultiple contacts found:\033[0m\n");
        for (int i = 0; i < matchCount; i++)
        {
            int idx = matchedIndices[i];
            printf("\033[1;36m%d. Name: %s, Phone: %s, Email: %s\033[0m\n", i + 1, scont[idx].name, scont[idx].phone_num, scont[idx].email);
        }

        // prompt user choice for which contact to display
        int deleteChoice;
        printf("\033[1;36mEnter the serial number of the contact to delete: \033[0m");
        scanf("%d", &deleteChoice);

        if (deleteChoice >= 1 && deleteChoice <= matchCount) {
            int deleteIndex = matchedIndices[deleteChoice - 1];
            printf("\033[1;32mDeleting contact: %s\033[0m\n", scont[deleteIndex].name);

            free(scont[deleteIndex].name);
            free(scont[deleteIndex].phone_num);
            free(scont[deleteIndex].email);

            // delete contact
            for (int i = deleteIndex; i < count - 1; i++) {
                scont[i] = scont[i + 1];
            }
            (count)--;
            printf("\033[1;32mContact deleted successfully.\033[0m\n");

        } 
        else 
        {
            printf("\033[1;31mInvalid choice.\033[0m\n");
        }
    }

    fclose(readfile);

    // write the data in the array of structs back to the contact file
    FILE *writefile;
    writefile = fopen(file, "w");
    for (int i = 0; i < count; i++) {
        fprintf(writefile, "%s, %s, %s\n", scont[i].name, scont[i].phone_num, scont[i].email);
    }

    // free memory
    for (int i = 0; i < count; i++) {
        free(scont[i].name);
        free(scont[i].phone_num);
        free(scont[i].email);
    }

    fclose(writefile);

    return 0;
}


int Search(char* file, int mode)
{
    FILE *readfile;
    readfile = fopen(file, "r");
    Contact scont[100];

    if (readfile == NULL)
    {
        printf("\033[0;31mContact file does not exist. Please add contacts first\n\033[0m");
    }

    // allocate memory for array of structs to be read from file
    for (int i = 0; i < 100; i++) {
        scont[i].name = malloc(50 * sizeof(char));
        scont[i].phone_num = malloc(25 * sizeof(char));
        scont[i].email = malloc(50 * sizeof(char));
    }

    // read data from file and store in array of structs
    int count = 0;
    while (fscanf(readfile, "%49[^,], %49[^,], %49[^\n]\n", scont[count].name, scont[count].phone_num, scont[count].email) != EOF)
    {
        count++;
    }

    int choice;
    int result;
    int searchResult;
    char sterm[50];

    printf("\n\033[1;33mSearch by:\n 1. Name\n 2. Phone Number\n 3. Email ID\n\033[0m");
    printf("\033[0;34mEnter your choice: \033[0m");
    scanf("%d", &choice);
    getchar();

    printf("\033[0;34mEnter search term:  \033[0m");
    scanf(" %49[^\n]", sterm);

    char stermLower[50];
    toLowercase(sterm, stermLower);

    int matchedIndices[100];
    int matchCount = 0;

    // compare lowercase characters so that search is not case-sensitive
    for (int i = 0; i < count; i++) {
        int match = 0;
        char fieldLower[50];

        if (choice < 1 || choice > 3)
        {
            printf("\033[0;31mNot a valid choice\n\033[0m");
            break;
        }

        if (choice == 1)
        {
            toLowercase(scont[i].name, fieldLower);
            if (strstr(fieldLower, stermLower) != NULL)
            {
                match = 1;
            }
        }
        else if (choice == 2)
        {
            toLowercase(scont[i].phone_num, fieldLower);
            if (strstr(fieldLower, stermLower) != NULL)
            {
                match = 1;
            }
        } 
        else if (choice == 3)
        {
            toLowercase(scont[i].email, fieldLower);
            if (strstr(fieldLower, stermLower) != NULL)
            {
                match = 1;
            }
        }
        else
        {
            printf("\033[0;31mNot a valid choice\n\033[0m");
            break;
        }

        if (match) 
        {
            matchedIndices[matchCount++] = i;
        }
    }
    // no matches for searched contact
    if (matchCount == 0) 
    {

        printf("\033[0;31mNo matching contact found.\n\033[0m");

    }
    // if matches found for searched contact
    else if (matchCount >= 1 && matchCount <= 100)
    {
        // interface: display matches found
        printf("\033[1;36m=========================================\033[0m\n");
        printf("\033[1;36m            SEARCH RESULTS              \033[0m\n");
        printf("\033[1;36m=========================================\033[0m\n");
        result = 1;
        for (int i = 0; i < matchCount; i++) 
        {
            int idx = matchedIndices[i];
            printf("\033[1;33m%d.\033[0m \033[1;32mName: %s\033[0m, \033[1;36mPhone: %s\033[0m, \033[1;35mMail: %s\033[0m\n", i + 1, scont[idx].name, scont[idx].phone_num, scont[idx].email);
        }

        int searchChoice;

        if (matchCount == 1)
        {
            searchResult = matchedIndices[0];
        }
        else
        {
            // if search is called in edit function, mode = 1, which will prompt user for contact to edit
            if (mode == 1)
            {
                printf("\033[0;36mEnter the serial number of the contact searched: \033[0m");
                scanf("%d", &searchChoice);
                searchResult = matchedIndices[searchChoice - 1];
            }
        }

    } else {

        printf("\033[0;31mInvalid choice.\n\033[0ms");

    }

    fclose(readfile);

    // write the data in the array of structs back to the contact file
    FILE *writefile;
    writefile = fopen(file, "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(writefile, "%s, %s, %s\n", scont[i].name, scont[i].phone_num, scont[i].email);
    }

    // free memory
    for (int i = 0; i < count; i++) {
        free(scont[i].name);
        free(scont[i].phone_num);
        free(scont[i].email);
    }

    fclose(writefile);

    if (result == 1)
    {
        return searchResult;
    }
    return -1;
}

int Edit(char* file)
{
    FILE *readfile;
    readfile = fopen(file, "r");
    Contact scont[100];

    if (readfile == NULL)
    {
        printf("\033[0;31mContact file does not exist. Please add contacts first\n\033[0m");
        return -1;
    }

    // allocate memory for array of structs
    for (int i = 0; i < 100; i++) {
        scont[i].name = malloc(50 * sizeof(char));
        scont[i].phone_num = malloc(50 * sizeof(char));
        scont[i].email = malloc(50 * sizeof(char));
    }

    // read data from file and store in array of structs
    int count = 0;
    while (fscanf(readfile, "%49[^,], %49[^,], %49[^\n]\n", scont[count].name, scont[count].phone_num, scont[count].email) != EOF)
    {
        count++;
    }

    int searchIndex;
    int searchChoice;
    char temp[50];

    // call search function to obtain index of contact to delete
    searchIndex = Search(file, 1);
    if (searchIndex == -1)
    {
        printf("\033[0;31mNo contact found\n\033[0m");
        return -1;
    }

    // prompt user for choice on details to edit for specific contact chosen
    printf("\n\033[1;33mEdit by \n1.\033[0m Name\n\033[1;33m2.\033[0m Phone Number\n\033[1;33m0.\033[0m Email ID\n");
    printf("Enter your choice: ");
    scanf("%d", &searchChoice);
    getchar();

    if (searchChoice >= 1 && searchChoice <= 3)
    {
        // prompt user for new data value
        printf("Enter the new data: ");
        fgets(temp, 50, stdin);
        temp[strcspn(temp, "\n")] = '\0';

        // if data passes validation, rewrite old data with new data
        if (searchChoice == 1)
        {
            if (validate(temp, scont[searchIndex].phone_num, scont[searchIndex].email))
            {
                strcpy(scont[searchIndex].name, temp);
                Sort(file, 1);
            }
            else
            {
                printf("\033[0;31mData is not valid\033[0m");
                return -1;
            }
        }
        else if (searchChoice == 2)
        {
            if (validate(scont[searchIndex].name, temp, scont[searchIndex].email))
            {
                strcpy(scont[searchIndex].phone_num, temp);
                Sort(file, 1);
            }
            else
            {
                printf("Data is not valid");
                return -1;
            }
        }
        else if (searchChoice == 3)
        {
            if (validate(scont[searchIndex].name, scont[searchIndex].phone_num, temp))
            {
                strcpy(scont[searchIndex].email, temp);
                Sort(file, 1);
            }
            else
            {
                printf("Data is not valid");
                return -1;
            }
        }
    }
    else
    {
            printf("Not a valid choice\n");
            return -1;
    }

    fclose(readfile);

    // write the data in the array of structs back to the contact file
    FILE *writefile;
    writefile = fopen(file, "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(writefile, "%s, %s, %s\n", scont[i].name, scont[i].phone_num, scont[i].email);
    }

    // free memory
    for (int i = 0; i < 100; i++) {
        free(scont[i].name);
        free(scont[i].phone_num);
        free(scont[i].email);
    }

    fclose(writefile);

    printf("Contact was edited\n");

    return 0;
}
