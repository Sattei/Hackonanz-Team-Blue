#include <stdio.h>
#include <stdlib.h>

void get_ram_info() {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Failed to open /proc/meminfo");
        return;
    }

    char buffer[256];
    long total_memory = 0;
    long free_memory = 0;
    long available_memory = 0;
    long buffers = 0;
    long cached = 0;
    long swap_total = 0;
    long swap_free = 0;

    // Read memory information
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "MemTotal: %ld kB", &total_memory) == 1) {
            // Total memory found
        } else if (sscanf(buffer, "MemFree: %ld kB", &free_memory) == 1) {
            // Free memory found
        } else if (sscanf(buffer, "MemAvailable: %ld kB", &available_memory) == 1) {
            // Available memory found
        } else if (sscanf(buffer, "Buffers: %ld kB", &buffers) == 1) {
            // Buffers memory found
        } else if (sscanf(buffer, "Cached: %ld kB", &cached) == 1) {
            // Cached memory found
        } else if (sscanf(buffer, "SwapTotal: %ld kB", &swap_total) == 1) {
            // Total swap memory found
        } else if (sscanf(buffer, "SwapFree: %ld kB", &swap_free) == 1) {
            // Free swap memory found
        }
    }

    fclose(file);

    // Print RAM information
    printf("Total RAM: %ld MB\n", total_memory / 1024);
    printf("Free RAM: %ld MB\n", free_memory / 1024);
    printf("Available RAM: %ld MB\n", available_memory / 1024);
    printf("Buffers: %ld MB\n", buffers / 1024);
    printf("Cached: %ld MB\n", cached / 1024);
    printf("Total Swap: %ld MB\n", swap_total / 1024);
    printf("Free Swap: %ld MB\n", swap_free / 1024);
}

int main() {
    get_ram_info();
    return 0;
}
