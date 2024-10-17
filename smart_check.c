#include <stdio.h>
#include <stdlib.h>

void get_usb_info() {
    printf("=== USB Device Information ===\n");

    // Get USB devices information using lsusb
    FILE *fp = popen("lsusb", "r");
    if (fp == NULL) {
        perror("Failed to run lsusb");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
}

int main() {
    get_usb_info();
    return 0;
}
