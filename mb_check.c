#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for strstr

void read_motherboard_info(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        char line[256];
        if (fgets(line, sizeof(line), file) != NULL) {
            printf("%s: %s", filename, line);
        }
        fclose(file);
    } else {
        perror("Failed to open file");
    }
}

void get_motherboard_info() {
    printf("=== Motherboard Information ===\n");

    read_motherboard_info("/sys/class/dmi/id/board_vendor");
    read_motherboard_info("/sys/class/dmi/id/board_name");
    read_motherboard_info("/sys/class/dmi/id/board_version");
    read_motherboard_info("/sys/class/dmi/id/board_serial");
}

int main() {
    get_motherboard_info();
    return 0;
}
