/********* definitions.c ********
    Student Name 	= Liam Bennet
    Student Number	= 101264851
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
    Function that creates a new user and adds it to a sorted (ascending order) linked list at
    the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password) {
    user_t *new_user = (user_t *)malloc(sizeof(user_t));
    assert(new_user != NULL);

    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->friends = NULL;
    new_user->posts = NULL;
    new_user->next = NULL;

    // if users if null or if the new user username should be before the first given username
    if (users == NULL || strcmp(username, users->username) < 0) {
        new_user->next = users;
        return new_user; 
    }

    // iterates through the linked list and puts new user username in the right place
    user_t *current = users;
    while (current->next != NULL && strcmp(username, current->next->username) > 0) {
        current = current->next;
    }

    new_user->next = current->next;
    current->next = new_user;
    return users;
    }

/*
    Function that searches if the user is available in the database
    Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username) {
    user_t *temp = users;

    // looks for user
    while (temp != NULL) {
        // checks if usernames match, if they do a user is found 
        if (strcmp(temp->username, username) == 0) { 
            return temp;
        }
        temp = temp->next;
    }

    // if user is not found
    printf("-----------------------------------------------\n");
    printf("                User not Found.                \n");
    printf("-----------------------------------------------\n");
    return NULL; 
}

/*
    Function that creates a new friend's node.
    Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
    friend_t *new_friend = (friend_t *)malloc(sizeof(friend_t));
    assert(new_friend != NULL);

    // copy the friend's username to the new friend node
    strncpy(new_friend->username, username, sizeof(new_friend->username) - 1);
    new_friend->username[sizeof(new_friend->username) - 1] = '\0'; // makes sure it ends with null character
    new_friend->next = NULL;
    return new_friend;
}

/*
    Function that links a friend to a user. The friend's name should be added into
    a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend) {
    friend_t *new_friend = create_friend(friend);
    assert(new_friend != NULL);
    friend_t *current = user->friends;
    friend_t *prev = NULL;

    // iterates through the linked list to find the right place
    while (current != NULL && strcmp(friend, current->username) > 0) {
        prev = current;
        current = current->next;
    }

    // inserts the new friend username at the correct position
    // if new friend username goes at the beginning 
    if (prev == NULL) {
        new_friend->next = user->friends;
        user->friends = new_friend;
    } else {
        // if new friend username goes in the middle or end
        prev->next = new_friend;
        new_friend->next = current;
    }
}

/*
    Function that removes a friend from a user's friend list.
    Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name) {
    friend_t *temp = user->friends;
    friend_t *prev = NULL;
    _Bool del_friend = 0;

    // if no friends or user is NULL
    if (user == NULL || user->friends == NULL) {
        return 0; 
    }

    // iterates through user's friends to find the one to be deleted
    while (temp != NULL) {
        // if user's friend's usernames match then it gets deleted
        if (strcmp(temp->username, friend_name) == 0) {
            if (prev == NULL) {
                user->friends = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            del_friend = 1;
            break;
        } 
        prev = temp;
        temp = temp->next;
    }

    // if the friend's name is not found
    if (del_friend == 0) {
        printf("Invalid friend's name\n");
        printf("\n");
        display_user_friends(user);
    }
    return del_friend;
}

/*
    Function that creates a new user's post.
    Return the newly created post.
*/
post_t *create_post(const char *text) {
    post_t *new_post = (post_t *)malloc(sizeof(post_t));
    assert(new_post != NULL);

    // copy the content to the new post
    strncpy(new_post->content, text, sizeof(new_post->content) - 1);
    new_post->content[sizeof(new_post->content) - 1] = '\0'; // makes sure it ends with null-character

    new_post->next = NULL;
    return new_post;
}

/*
    Function that adds a post to a user's timeline. New posts should be added following
    the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text) {
    // create a new post node
    post_t *new_post = create_post(text);
    assert(new_post != NULL);

    // insert the new post at the beginning of the user's post list
    new_post->next = user->posts;
    user->posts = new_post;
}

/*
    Function that removes a post from a user's list of posts.
    Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number) {
    post_t *temp = user->posts;
    post_t *prev = NULL;
    int num_posts = 1;

    // if no posts 
    if (user == NULL || user->posts == NULL) {
        return 0; 
    }

    // iterates through the posts 
    while (temp != NULL && num_posts != number) {
        prev = temp;
        temp = temp->next;
        num_posts += 1;
    }

    // if post number is found deletes the post
    if (temp != NULL && num_posts == number) {
        if (prev == NULL) {
            user->posts = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        return 1; 
    }
    return 0;
    }

    /*
    Function that displays a specific user's posts
    */
    void display_user_posts(user_t *user)
    {
    int num_posts = 1;
    printf("-----------------------------------------------\n");
    printf("              %s's posts                       \n", user->username);
    post_t *temp = user->posts;

    // if there are no posts
    if (temp == NULL) {
        printf("No posts available for %s.\n", user->username);
        printf("-----------------------------------------------\n");
        return;
    }

    // prints all posts of specific user
    while (temp != NULL) {
        printf("%d- %s\n", num_posts, temp->content);
        temp = temp->next;
        num_posts += 1;
    }
    printf("-----------------------------------------------\n");
}

/*
    Function that displays a specific user's friends
*/
void display_user_friends(user_t *user) {
    int num_friends = 1;
    friend_t *temp = user->friends;
    printf("List of %s friends:\n", user->username);

    // if there are no friends
    if (temp == NULL) {
        printf("No friends available for %s.\n", user->username);
        return;
    }

    // prints all friends of specific user
    while (temp != NULL) {
        printf("%d- %s\n", num_friends, temp->username);
        temp = temp->next;
        num_friends += 1;
    }
    printf("\n");
}

/*
    Function that displays all the posts of 2 users at a time from the database.
    After displaying 2 users' posts, it prompts if you want to display
    posts of the next 2 users.
    If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users) {
    user_t *current = users;
    post_t *post = users->posts;
    char cont_posts;
    int num_posts = 0;

    // iterates through all users
    while (current != NULL) {
        // display posts for the first two users
        if (num_posts < 2) {
            format_for_display_all_posts(current);
            num_posts += 1;
        } else {
            printf("\nDo you want to display next 2 users posts? (Y/N): ");
            printf("\n");
            scanf(" %c", &cont_posts);


            // continues if user input is yes
            if (cont_posts == 'Y' || cont_posts == 'y') {
                num_posts = 0; 
                current = current->next;

                // ends if reached the end of all users' posts
                if (current == NULL) {
                printf("All posts have been displayed.\n");
                break;
                }
                format_for_display_all_posts(current);
                num_posts += 1;
            
            // if user input is no
            } else if (cont_posts == 'N' || cont_posts == 'n') {
                break;

            // returns to main menu if answer not yes or no
            } else {
                break;
            }
        }

        // move to the next user
        current = current->next;
        if (current == NULL) {
            printf("All posts have been displayed.\n");
            break;
        }
    }
}

/*
    Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users) {
    user_t *current_user = users;
    user_t *next_user;

    // iterates through all users 
    while (current_user != NULL) {
        next_user = current_user->next;
        post_t *current_post = current_user->posts;
        post_t *next_post;

        // frees memory for each post
        while (current_post != NULL) {
            next_post = current_post->next;
            free(current_post);
            current_post = next_post;
        }

        // frees memory for each user
        free(current_user);
        current_user = next_user;
    }
}

/*
    Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
    // main menu
    printf("\n");
    printf("***********************************************\n");
    printf("                   MAIN MENU:                  \n");
    printf("***********************************************\n");
    printf("1. Register a new User\n");
    printf("2. Manage a user's profile (change password)\n");
    printf("3. Manage a user's posts (display/add/remove)\n");
    printf("4. Manage a user's friends (displpay/add/remove)\n");
    printf("5. Display All Posts\n");
    printf("6. Exit\n");
    printf("\n");
    printf("Enter your choice: ");
}

/*
    Function that updates the password of a user if the username is found
*/
void change_password(user_t *users, const char *username_to_search, const char *new_password) {
    if (users != NULL) {
        // updates the password
        strcpy(users->password, new_password);
        printf("\n");
        printf("**** Password Changed! ****\n");
        printf("\n");
    }
}

/*
    Function that displays the three options a user can pick after choosing to 
    manage a users posts (option 3)
*/
void display_post_menu(user_t *user) {
    int user_choice;

    // controls the logic for all the actions for the posts menu
    do {
        print_display_post_menu();
        scanf("%d", &user_choice);

        // ensures user input is between 1 and 3 
        while (user_choice < 1 || user_choice > 3) {
            printf("Invalid choice. Please try again.\n");
            print_display_post_menu();
            scanf("%d", &user_choice);
        }

        switch (user_choice) {
            // if user chooses to add a post
            case 1: {
                char post_text[250];
                printf("Enter your post content: ");
                scanf(" %[^\n]s", post_text);
                add_post(user, post_text);
                display_user_posts(user);
                break;
            }

            // if user chooses to delete a post
            case 2: {
                int post_to_del;
                printf("Which post do you want to delete? ");
                scanf("%d", &post_to_del);
                // check if user choice is a valid post number
                if (delete_post(user, post_to_del) == 0) {
                printf("Invalid post's number\n");
                display_user_posts(user);
                break;
                }
                printf("Post %d was deleted successfully!\n", post_to_del);
                display_user_posts(user);
                break;
            }

            // if user wants to return to the main menu
            case 3: {
                printf("\n");
                break;
            }
        }
    } while (user_choice != 3);
}

/*
    Function that prints the user's options for updating a post
*/
void print_display_post_menu() {
    // menu for posts actions
    printf("\n");
    printf("1. Add a new user post\n");
    printf("2. Remove a users post\n");
    printf("3. Return to main menu\n");
    printf("\n");
    printf("Your choice: ");
}

/*
    Function that displays the four options a user can pick after choosing to 
    manage a users friends (option 4)
*/
void display_friend_menu(user_t *user) {
    int friend_menu_choice;

    // controls the logic for all the actions for the friends menu
    do {
        print_display_friend_menu(user);
        scanf("%d", &friend_menu_choice);
        printf("\n");

        switch (friend_menu_choice) {

            // if user chooses to display list of all friends
            case 1: {
                display_user_friends(user);
                break;
            }

            // if user chooses to add a new friend
            case 2: {
                char friend_to_add[30];
                printf("Enter a new friends' name: ");
                scanf("%s", friend_to_add);
                add_friend(user, friend_to_add);
                printf("Friend added to the list.\n");
                printf("\n");
                break;
            }

            // if user chooses to delete a friend 
            case 3: {
                int del_friend;
                char friend_to_delete[30];
                display_user_friends(user);
                printf("Enter a friend's name to delete: ");
                scanf("%s", friend_to_delete);
                if (delete_friend(user, friend_to_delete) == 1) {
                display_user_friends(user);
                }
                break;
            }
            // if user chooses to return to the main menu
            case 4: {
                break;
            }

            // if user choice is not valid
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    } while (friend_menu_choice != 4);
}

/*
    Function that prints the user's options for updating friends
*/
void print_display_friend_menu(user_t *user) {
    // menu for friends actions 
    printf("-----------------------------------------------\n");
    printf("              %s's friends                     \n", user->username);
    printf("-----------------------------------------------\n");
    printf("\n");
    printf("1. Display all user's friends\n");
    printf("2. Add a new friend\n");
    printf("3. Delete a friend\n");
    printf("4. Return to main menu\n");
    printf("\nYour choice: ");
}

/*
    Function that displays posts of first two users in proper format
*/
void format_for_display_all_posts(user_t *user) {
    int num_posts = 1;
    post_t *temp = user->posts;

    // if there are no posts
    if (temp == NULL) {
        printf("No posts available for %s.\n", user->username);  
        return;
    }

    // prints all posts of specific user
    while (temp != NULL) {
        printf("%d- %s: %s\n", num_posts, user->username, temp->content);
        temp = temp->next;
        num_posts += 1;
    }
}

/*
    ******** DONT MODIFY THIS FUNCTION ********
    Function that reads users from the text file.
    IMPORTANT: This function shouldn't be modified and used as is
    ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next);

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}

