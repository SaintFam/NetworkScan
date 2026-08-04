#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

int getIpAndMac(void)
{
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    ULONG family = AF_UNSPEC; // IPv4 + IPv6
    ULONG bufferSize = 15000;
    IP_ADAPTER_ADDRESSES *addresses = NULL; // Just Know Structure of value it will point to  The Data type of pointer but for now it is null
    IP_ADAPTER_ADDRESSES *adapter = NULL;
    addresses = (IP_ADAPTER_ADDRESSES *)malloc(bufferSize); // Link it A memory where pointer will point too

    if (addresses == NULL) // Check if memory allocation was successful
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    // Call GetAdaptersAddresses to retrieve adapter information
    DWORD result = GetAdaptersAddresses(
        family,
        flags,
        NULL,
        addresses,
        &bufferSize);

    if (result == ERROR_BUFFER_OVERFLOW)
    {
        free(addresses);
        addresses = (IP_ADAPTER_ADDRESSES *)malloc(bufferSize);

        result = GetAdaptersAddresses(
            family,
            flags,
            NULL,
            addresses,
            &bufferSize);
    }

    if (result != NO_ERROR)
    {
        printf("GetAdaptersAddresses failed.\n");
        free(addresses);
        return 1;
    }
    adapter = addresses; // Set adapter to point to the first adapter in the list
    while (adapter)
    {
        printf("====================================================\n");
        adapter = adapter->Next;
    }
}