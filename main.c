/********* main.c ********
    Student Name    = Liam Bennet
    Student Number  = 101264851
*/


// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"


int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);


    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
   
    /* IMPORTANT: You must use the users linked list created in the code above.
                  Any new users should be added to that linked list.
    */


    // Your solution goes here
    printf("***********************************************\n");
    printf("        Welcome to Text-Based Facebook         \n");
    printf("***********************************************\n");
    int user_choice;

    do {
        //prints menu and asks for user input
        print_menu();
        scanf("%d", &user_choice);

        //makes sure the user input is in between 1 and 6
        while (user_choice < 1 || user_choice > 6) {
            printf("Invalid choice. Please try again.\n");
            printf("\n");
            print_menu();
            scanf("%d", &user_choice);
        }

        // what action to be done based on user input
        switch(user_choice) {

            // adds user 
            case 1: {
                char username[30];
                char password[15];
                printf("Enter a username: ");
                scanf("%s", username);
                printf("Enter a password up to 15 characters: ");
                scanf("%s", password);
                add_user(users, username, password);
                printf("\n");
                printf("**** User Added! ****\n");
                break;
            }

            // updates password 
            case 2: {
                char username_to_search[30];
                char password_to_update[15];
                printf("Enter username to update their password: ");
                scanf("%s", username_to_search);
                user_t *user_to_update = find_user(users, username_to_search);

                // returns to main menu if user is not found
                if (user_to_update == NULL) {
                    break;
                }
                printf("Enter a new password up to 15 characters: ");
                scanf("%s", password_to_update);
                change_password(users, username_to_search, password_to_update);
                break;
            }

            // manages users' posts
            case 3: {
                char username_to_search[30];
                printf("Enter username to manage their posts: ");
                scanf("%s", username_to_search);
                user_t *user_to_update = find_user(users, username_to_search);

                // returns to main menu if user is not found
                if (user_to_update == NULL) {
                    break;
                }
                display_user_posts(user_to_update);
                display_post_menu(user_to_update);
                break;
            }

            // manages users' friends 
            case 4: {
                char username_to_search[30];
                printf("Enter username to manage their friends: ");
                scanf("%s", username_to_search);
                user_t *user_to_update = find_user(users, username_to_search);

                // returns to main menu if user is not found
                if (user_to_update == NULL) {
                    break;
                }
                display_friend_menu(user_to_update);
                break;
            }

            // displays all posts of first two users
            case 5: {
                display_all_posts(users);
                break;
            }

            // ends the program
            case 6: {
                teardown(users);
                printf("***********************************************\n");
                printf("    Thank you for using Text-Based Facebook    \n");
                printf("                    Goodbye!                   \n");
                printf("***********************************************\n");
                break;
            }
        }
    } while (user_choice != 6);
    return 0;
}
