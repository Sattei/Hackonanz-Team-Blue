#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_storage_info() {
    printf("=== Storage Device Information ===\n");

    // Run lsblk to get model and manufacturer, excluding loop devices
    FILE *fp = popen("lsblk -o NAME,MODEL,SIZE,TYPE,SERIAL | grep -v loop", "r");
    if (fp == NULL) {
        perror("Failed to run lsblk");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);

    // Get additional information using hdparm
    printf("\n=== Additional Storage Device Information ===\n");
    
    // Example: Get information for /dev/sda (change as necessary)
    fp = popen("sudo hdparm -I /dev/sda", "r"); // Change /dev/sda as necessary
    if (fp == NULL) {
        perror("Failed to run hdparm");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "Model Number") || 
            strstr(buffer, "Serial Number") || 
            strstr(buffer, "Transport") || 
            strstr(buffer, "Cache") || 
            strstr(buffer, "Firmware revision")) {
            printf("%s", buffer);
        }
    }

    pclose(fp);
}

void measure_read_write_speed(const char *device) {
    char command[256];

    // Measure read speed
    snprintf(command, sizeof(command), "sudo hdparm -T %s", device);
    printf("\n=== Read Speed Measurement for %s ===\n", device);
    system(command);

    // Measure write speed (using a temporary file)
    printf("\n=== Write Speed Measurement for %s ===\n", device);
    snprintf(command, sizeof(command), "sudo dd if=/dev/zero of=/tmp/testfile bs=1G count=1 oflag=direct; rm -f /tmp/testfile");
    system(command);
}

int main() {
    get_storage_info();

    // Measure speeds for /dev/sda (change as necessary)
    measure_read_write_speed("/dev/sda");
    measure_read_write_speed("/dev/sdb");
    measure_read_write_speed("/dev/nvme0n1");

    return 0;
}
