#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_cpu_info() {
    FILE *fp;
    char buffer[256];
    char model_name[256] = "";
    int core_count = 0;
    int low_freq_count = 0;
    int medium_freq_count = 0;
    int high_freq_count = 0;

    // Get CPU information from /proc/cpuinfo
    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/cpuinfo");
        return;
    }

    printf("CPU Information:\n");

    // Read the file line by line
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Check for model name
        if (strstr(buffer, "model name")) {
            sscanf(buffer, "model name : %[^\n]", model_name);
        }
        // Check for frequency
        if (strstr(buffer, "cpu MHz")) {
            // Extract the frequency value
            float frequency;
            sscanf(buffer, "cpu MHz : %f", &frequency);
            core_count++;

            // Categorize frequency
            if (frequency < 1000) {
                low_freq_count++;
            } else if (frequency >= 1000 && frequency <= 2500) {
                medium_freq_count++;
            } else {
                high_freq_count++;
            }
        }
    }

    fclose(fp);

    // Print the model name once
    printf("Model Name: %s\n", model_name);
    
    // Display core frequency categorization
    printf("\nCore Frequency Categorization:\n");
    printf("Total Cores: %d\n", core_count);
    printf("Low Frequency Cores (< 1 GHz): %d\n", low_freq_count);
    printf("Medium Frequency Cores (1-2.5 GHz): %d\n", medium_freq_count);
    printf("High Frequency Cores (> 2.5 GHz): %d\n", high_freq_count);
}

int main() {
    get_cpu_info();
    return 0;
}
