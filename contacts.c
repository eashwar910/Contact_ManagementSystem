#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "contacth.h"

int main(void)
{
    int user_choice;
    char contactfile[60] = "";
    char* login_result;
    user_choice = -1;

    // interface
    while (user_choice)
    {
        printf("\n\033[1;34m=========================================\033[0m\n");
        printf("\033[1;36m         CONTACT MANAGEMENT SYSTEM       \033[0m\n");
        printf("\033[1;34m=========================================\033[0m\n");
        printf("\n\033[1;33m1.\033[0m Log In\n\033[1;33m2.\033[0m Sign Up\n\033[1;33m0.\033[0m Quit\n");
        printf("\033[1;36mPlease enter an operation: \033[0m");
        
        // prompt user for operation
        scanf("%d", &user_choice);
        getchar();
        printf("\n");

        // cases for user_choice (operations by unidentified user)
        switch (user_choice)
        {
            case 0:
                break;
                printf("\033[1;32mThank you for using the Contact Management System! Goodbye!\033[0m\n");
            case 1:
                login_result = LogIn(contactfile);
                if (login_result == NULL) 
                {
                    printf("\033[1;31mLogin failed. Returning to main menu.\033[0m\n");
                    break;
                }
                strcpy(contactfile, login_result);
                break;
            case 2:
                SignUp();
                break;
            default:
                printf("\033[1;31mInvalid operation. Please try again.\033[0m\n");
                break;
        }

        int choice;
        int option;

        // interface
        choice = -1;
        while (choice && strlen(contactfile) > 0)
        {
            printf("\n\033[1;34m=========================================\033[0m\n");
            printf("\033[1;36m              CONTACT MENU              \033[0m\n");
            printf("\033[1;34m=========================================\033[0m\n");
            printf("\n\033[1;33m1.\033[0m Add Contact\n\033[1;33m2.\033[0m Delete Contact\n\033[1;33m3.\033[0m Edit Contact\n");
            printf("\033[1;33m4.\033[0m Search Contact\n\033[1;33m5.\033[0m Display Contacts\n\033[1;33m6.\033[0m Sort Contacts\n\033[1;33m0.\033[0m Log Out\n");
            printf("\033[1;36mPlease enter an operation: \033[0m");

            scanf("%d", &choice);
            getchar();
            printf("\n");

            // cases for choice (operations by identified user)
            switch (choice)
            {
                case 0:
                    strcpy(contactfile, "");
                    printf("\033[1;32mLogged out successfully.\033[0m\n");
                    break;
                case 1:
                    Add(contactfile);
                    break;
                case 2:
                    Delete(contactfile);
                    break;
                case 3:
                    Edit(contactfile);
                    break;
                case 4:
                    Search(contactfile, 0);
                    break;
                case 5:
                    Display(contactfile);
                    break;
                case 6:
                    printf("\033[1;36mEnter your sort option (1 for name, 2 for phone number): \033[0m");
                    scanf("%d", &option);
                    printf("\n");
                    if (option >= 1 && option <= 2)
                    {
                        Sort(contactfile, option);
                    }
                    else
                    {
                        printf("\033[1;31mError! Option not valid.\033[0m\n");
                    }
                    break;
                default:
                    printf("\033[1;31mInvalid operation. Please try again.\033[0m\n");
                    break;
            }
        }
    }
}