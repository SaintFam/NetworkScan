#include <stdio.h>
#include <string.h>
#include "command.h"

int main()
{
    char username[20];
    char password[20];

    // Correct credentials
    char correctUsername[] = "hacpro";
    char correctPassword[] = "khan";

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0)
    {
        printf("Login successful!\n");
        getchar();

        // Command loop
        command_loop();
    }
    else
    {
        printf("Invalid username or password.\n");
        while (getchar() != '\n')
            ;      // keeps reading until \n is gone
        getchar(); // buffer empty now, waits for real!
    }

    return 0;
}