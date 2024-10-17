#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void get_battery_info() {
    DIR *dir;
    struct dirent *entry;
    char path[512]; // Increased buffer size
    char buffer[256];
    char battery_name[256];
    int capacity = -1;
    char status[32] = "";
    float voltage = -1;
    float energy_now = -1;
    float energy_full_design = -1; // Design capacity
    char manufacturer[256] = "Unknown";
    float health_percentage = -1; // Battery health percentage

    // Open the power supply directory
    dir = opendir("/sys/class/power_supply/");
    if (dir == NULL) {
        perror("Failed to open /sys/class/power_supply/");
        return;
    }

    // Read the entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Look for battery entries
        if (strstr(entry->d_name, "BAT")) {
            snprintf(battery_name, sizeof(battery_name), "%s", entry->d_name);

            // Get battery capacity
            snprintf(path, sizeof(path), "/sys/class/power_supply/%s/capacity", battery_name);
            FILE *capacity_file = fopen(path, "r");
            if (capacity_file) {
                fgets(buffer, sizeof(buffer), capacity_file);
                capacity = atoi(buffer);
                fclose(capacity_file);
            }

            // Get battery status
            snprintf(path, sizeof(path), "/sys/class/power_supply/%s/status", battery_name);
            FILE *status_file = fopen(path, "r");
            if (status_file) {
                fgets(status, sizeof(status), status_file);
                status[strcspn(status, "\n")] = '\0'; // Remove newline character
                fclose(status_file);
            }

            // Get battery voltage
            snprintf(path, sizeof(path), "/sys/class/power_supply/%s/voltage_now", battery_name);
            FILE *voltage_file = fopen(path, "r");
            if (voltage_file) {
                fgets(buffer, sizeof(buffer), voltage_file);
                voltage = atof(buffer) / 1000000.0; // Convert from microvolts to volts
                fclose(voltage_file);
            }

            // Get battery energy now
            snprintf(path, sizeof(path), "/sys/class/power_supply/%s/energy_now", battery_name);
            FILE *energy_now_file = fopen(path, "r");
            if (energy_now_file) {
                fgets(buffer, sizeof(buffer), energy_now_file);
                energy_now = atof(buffer) / 1000000.0; // Convert from nanowatt-hours to watt-hours
                fclose(energy_now_file);
            }

            

            // Get battery design capacity
            snprintf(path, sizeof(path), "/sys/class/power_supply/%s/energy_full_design", battery_name);
            FILE *energy_full_design_file = fopen(path, "r");
            if (energy_full_design_file) {
                fgets(buffer, sizeof(buffer), energy_full_design_file);
                energy_full_design = atof(buffer) / 1000000.0; // Convert from nanowatt-hours to watt-hours
                fclose(energy_full_design_file);
            }

            // Calculate battery health
            if (energy_full_design > 0) {
                health_percentage = (energy_now / energy_full_design) * 100;
            }

            // Get battery manufacturer
            snprintf(path, sizeof(path), "/sys/class/power_supply/%s/manufacturer", battery_name);
            FILE *manufacturer_file = fopen(path, "r");
            if (manufacturer_file) {
                fgets(manufacturer, sizeof(manufacturer), manufacturer_file);
                manufacturer[strcspn(manufacturer, "\n")] = '\0'; // Remove newline character
                fclose(manufacturer_file);
            }

            // Print the battery information
            printf("Battery Name: %s\n", battery_name);
            printf("Capacity: %d%%\n", capacity);
            printf("Status: %s\n", status);
            printf("Voltage: %.2f V\n", voltage);
            printf("Energy Now: %.2f Wh\n", energy_now);
            if (energy_full_design > 0) {
                printf("Design Capacity: %.2f Wh\n", energy_full_design);
                printf("Battery Health: %.2f%%\n", health_percentage);
            }
            printf("Manufacturer: %s\n", manufacturer);
            printf("\n");
        }
    }
    closedir(dir);
}

int main() {
    get_battery_info();
    return 0;
}
