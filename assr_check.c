#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_built_in_input_device_info() {
    printf("=== Built-in Input Device Information (Keyboard and Touchpad) ===\n");

    // Execute xinput list command
    FILE *fp = popen("xinput list", "r");
    if (fp == NULL) {
        perror("Failed to run xinput list");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Check if the line contains keyboard or touchpad identifiers
        if (strstr(line, "keyboard") || strstr(line, "Touchpad") || strstr(line, "pointer")) {
            // Extract device name
            char *device_name = strtok(line, "\n");
            printf("Device: %s\n", device_name);
            printf("---------------------------------\n");
        }
    }
    pclose(fp);
}

int main() {
    get_built_in_input_device_info();
    return 0;
}
