#include <stdio.h>
#include <string.h>
void run_bonjour()
{
    printf("help\n");
    printf("scan - for scanning your IpAddress and Default Gateway Ip And Then Finding Online Devices\n");
    printf("clear\n");
    printf("exit\n");
}

void net_scan_table()
{
    FILE *file;
    int no;
    char ip[20];
    char mac[30];
    char os[20];
    char status[20];

    file = fopen("network_data.txt", "r");

    if (file == NULL)
    {
        printf("Error: Could not open network_data.txt\n");
        return;
    }

    // Table Header
    printf("+-----+---------------+-------------------+-----------+-----------+\n");
    printf("| %-3s | %-13s | %-17s | %-9s | %-9s |\n",
           "No", "IP Address", "Mac Address", "OS", "Status");
    printf("+-----+---------------+-------------------+-----------+-----------+\n");

    while (fscanf(file,
                  "%d,%19[^,],%29[^,],%19[^,],%19[^\n]",
                  &no, ip, mac, os, status) == 5)
    {
        printf("| %-3d | %-13s | %-17s | %-9s | %-9s |\n",
               no, ip, mac, os, status);
    }

    printf("+-----+---------------+-------------------+-----------+-----------+\n");

    fclose(file);
}

void scan_network()
{
    printf("Scanning network...\n");
    net_scan_table();
}
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
