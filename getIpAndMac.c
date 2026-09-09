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
        IP_ADAPTER_UNICAST_ADDRESS *unicast = adapter->FirstUnicastAddress;

        while (unicast)
        {
            char addressBuffer[INET6_ADDRSTRLEN];

            if (unicast->Address.lpSockaddr->sa_family == AF_INET)
            {
                struct sockaddr_in *ipv4 =
                    (struct sockaddr_in *)unicast->Address.lpSockaddr;

                InetNtopA(
                    AF_INET,
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
        adapter = adapter->Next;
    }
    free(addresses); // Release the allocated memory

    return 0; // Indicate success
}