#include <stdio.h>
#include <string.h>
#include "command_Loop.h"
#include "command.h" // Gives access to run_bonjour() and scan_network

void command_loop()
{
    char command[100];

    while (1)
    {
        printf(">");
        fgets(command, sizeof(command), stdin);

        // Clean the Leftover Newline Character from the Input Buffer
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "bonjour") == 0)
        {
            run_bonjour();
        }
        else if (strcmp(command, "scan") == 0)
        {
            scan_network();
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("Unknown command.\n");
        }
    }
}
