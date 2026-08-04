#include <stdio.h>
#include <string.h>
#include "command.h"
void run_bonjour()
{
    printf("help\n");
    printf("scan - for scanning your IpAddress and Default Gateway Ip And Then Finding Online Devices\n");
    printf("clear\n");
    printf("exit\n");
}

void net_scan_table()
{
    printf("Scanning Your Ip Address And Your default GateAway");
    getIpAndMac();
}

void scan_network()
{
    printf("Scanning network...\n");
    net_scan_table();
}
