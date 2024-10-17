#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_display_info() {
    printf("=== Display Information ===\n");

    // Using xrandr to get detailed display information
    FILE *fp = popen("xrandr --verbose", "r");
    if (fp == NULL) {
        perror("Failed to run xrandr");
        return;
    }

    char buffer[256];
    int found = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Print different types of display information
        if (strstr(buffer, " connected")) {
            printf("Display: %s", buffer);
            found = 1;
        }   if (strstr(buffer, "Manufacturer")) {
            printf("Manufacturer: %s", buffer + strlen("  Manufacturer: "));
            found = 1;
        }   if (strstr(buffer, "Model")) {
            printf("Model: %s", buffer + strlen("  Model: "));
            found = 1;
        }   if (strstr(buffer, "Refresh Rate")) {
            printf("Refresh Rate: %s", buffer + strlen("  Refresh Rate: "));
            found = 1;
        }   if (strstr(buffer, "Dimensions")) {
            printf("Dimensions: %s", buffer + strlen("  Dimensions: "));
            found = 1;
        }   if (strstr(buffer, "Size")) {
            printf("Size: %s", buffer + strlen("  Size: "));
            found = 1;
        }
    }

    pclose(fp);

    if (!found) {
        printf("No display information found.\n");
    }
}

int main() {
    get_display_info();
    return 0;
}
