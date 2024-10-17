#include <stdio.h>
#include <stdlib.h>

void run_cpu_stress_test();
void run_ram_test();
void run_smart_check();
void run_battery_check();
void run_usb_detection();

int main() {
    int choice;
    while (1) {
        printf("BIOS-Level Hardware Diagnostics Tool\n");
        printf("1. CPU Stress Test\n");
        printf("2. RAM Test\n");
        printf("3. SMART Check\n");
        printf("4. Battery Check\n");
        printf("5. USB Detection\n");
        printf("6. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                run_cpu_stress_test();
                break;
            case 2:
                run_ram_test();
                break;
            case 3:
                run_smart_check();
                break;
            case 4:
                run_battery_check();
                break;
            case 5:
                run_usb_detection();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void run_cpu_stress_test() {
    system("./cpu_stress_test");
}

void run_ram_test() {
    system("./ram_test");
}

void run_smart_check() {
    system("./smart_check");
}

void run_battery_check() {
    system("./battery_check");
}

void run_usb_detection() {
    system("./usb_detection");
}
