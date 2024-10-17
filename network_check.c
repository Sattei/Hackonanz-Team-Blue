#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_network_info() {
    printf("=== Network Adapter Information ===\n");

    // Get basic network interface information
    FILE *fp = popen("ip addr show", "r");
    if (fp == NULL) {
        perror("Failed to run ip addr show");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Print lines related to interfaces, IP addresses, and MAC addresses
        if (strstr(buffer, "inet ") || strstr(buffer, "link/ether")) {
            printf("%s", buffer);
        }
    }
    pclose(fp);

    // Get detailed information for wireless interfaces
    printf("\n=== Wireless Adapter Information ===\n");
    fp = popen("nmcli device show | grep -E 'DEVICE|IP4.ADDRESS|GENERAL.STATE|GENERAL.TYPE|GENERAL.WIRELESS' | grep -v '^$'", "r");
    if (fp == NULL) {
        perror("Failed to run nmcli");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
}

void get_pci_info() {
    printf("\n=== PCIe Adapter Information ===\n");

    // Get PCIe devices information
    FILE *fp = popen("lspci", "r");
    if (fp == NULL) {
        perror("Failed to run lspci");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Print only network-related devices (e.g., Ethernet, Wi-Fi)
        if (strstr(buffer, "Ethernet") || strstr(buffer, "Wireless") || strstr(buffer, "Network")) {
            printf("%s", buffer);
        }
    }
    pclose(fp);
}

int main() {
    get_network_info();
    get_pci_info();
    return 0;
}
