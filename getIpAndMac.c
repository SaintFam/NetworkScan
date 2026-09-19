#include <stdio.h>
#include <stdlib.h> // CHANGE 1: Added for malloc() and free()
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

int getIpAndMac(void)
{

    printf("\n\n==============================\n");
    printf("I AM RUNNING THE NEW getIpAndMac.c\n");
    printf("==============================\n\n");

        ULONG flags = GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_INCLUDE_GATEWAYS;
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

        printf("\n\n***** NEW VERSION OF PROGRAM *****\n\n");
        printf("====================================================\n");

        printf("Adapter Name      : %s\n", adapter->AdapterName);

        wprintf(L"Friendly Name     : %ls\n", adapter->FriendlyName);

        printf("MAC Address       : ");
        for (DWORD i = 0; i < adapter->PhysicalAddressLength; i++)
        {
            printf("%02X", adapter->PhysicalAddress[i]);

            if (i < adapter->PhysicalAddressLength - 1)
                printf("-");
        }

        printf("\n");

        { /** IP_ADAPTER_UNICAST_ADDRESS: This is a built-in Windows data structure. It holds information about a single unicast IP address  (such as an IPv4 or IPv6 address) assigned to a network interface, along with its properties (like prefix length or lease lifetime). */
        }
        { /** *unicast: This declares a pointer variable named unicast that points to a structure of the type mentioned above */
        }

        //---------------------------------------------------
        // IP Addresses
        //---------------------------------------------------
        // Create a pointer called unicast that can point to an IP_ADAPTER_UNICAST_ADDRESS structure
        // Create a pointer called unicast and make it point to the first unicast address belonging to this network adapter
        IP_ADAPTER_UNICAST_ADDRESS *unicast = adapter->FirstUnicastAddress;

        while (unicast)
        {
            char addressBuffer[INET6_ADDRSTRLEN];
            // Check If the current address is IPv4
            if (unicast->Address.lpSockaddr->sa_family == AF_INET)
            {

                // Creates an IPv4 blueprint pointer named ipv4.
                struct sockaddr_in *ipv4 =
                    // Forces the compiler to change lenses and read generic data as IPv4 data.
                    (struct sockaddr_in *)unicast->Address.lpSockaddr;

                // Internet Network-to-Presentation"
                InetNtopA(
                    // The input is an IPv4 address
                    AF_INET,
                    // The source data. It gives the function the memory address (&) of the raw, binary IP bytes inside your IPv4 structure.
                    &(ipv4->sin_addr),
                    addressBuffer,
                    sizeof(addressBuffer));

                printf("IPv4 Address      : %s\n", addressBuffer);
            }
            else if (unicast->Address.lpSockaddr->sa_family == AF_INET6)
            {
                struct sockaddr_in6 *ipv6 =
                    (struct sockaddr_in6 *)unicast->Address.lpSockaddr;

                InetNtopA(
                    AF_INET6,
                    &(ipv6->sin6_addr),
                    addressBuffer,
                    sizeof(addressBuffer));

                printf("IPv6 Address      : %s\n", addressBuffer);
            }

            unicast = unicast->Next;
        }
        //---------------------------------------------------
        // Default Gateway (Router)
        //---------------------------------------------------

        IP_ADAPTER_GATEWAY_ADDRESS_LH *gateway = adapter->FirstGatewayAddress;
        if (gateway == NULL)
        {
            printf("FirstGatewayAddress = NULL\n");
        }
        else
        {
            while (gateway)
            {
                char gatewayBuffer[INET6_ADDRSTRLEN];

                getnameinfo(
                    gateway->Address.lpSockaddr,
                    gateway->Address.iSockaddrLength,
                    gatewayBuffer,
                    sizeof(gatewayBuffer),
                    NULL,
                    0,
                    NI_NUMERICHOST);

                if (gateway->Address.lpSockaddr->sa_family == AF_INET)
                {
                    printf("Gateway IPv4      : %s\n", gatewayBuffer);
                }
                else if (gateway->Address.lpSockaddr->sa_family == AF_INET6)
                {
                    printf("Gateway IPv6      : %s\n", gatewayBuffer);
                }

                gateway = gateway->Next;
            }
        }
        adapter = adapter->Next;
    }
    free(addresses); // Release the allocated memory

    return 0; // Indicate success
}