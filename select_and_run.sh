#!/bin/bash
#Define output executable name
sudo apt install hdparm -y
sudo apt-get install dialog -y
sudo apt install xboxdrv -y
OUTPUT="diagnostic_tool"

# List of all possible .c files
FILES=("assr_check.c" "battery_check.c" "cpu_check.c" "desktop_check.c" "mb_check.c" "network_check.c" "ram_test.c" "smart_check.c" "storage_check.c")


# Display menu for file selection
echo "Select the C files to compile (multiple selections allowed):"
echo "Use space to select, and press enter to confirm."

# Generate checklist options
OPTIONS=()
for i in "${!FILES[@]}"; do
    OPTIONS+=("${i}" "${FILES[$i]}" "off")
done

# Use dialog to allow multiple selections
CHOICES=$(dialog --clear \
                 --separate-output \
                 --checklist "Choose C files to compile:" \
                 15 50 8 \
                 "${OPTIONS[@]}" 2>&1 >/dev/tty)

clear

# Check if any files were selected
if [ -z "$CHOICES" ]; then
    echo "No files selected. Exiting..."
    exit 1
fi

# Initialize variables
SRC_FILES=""
MAIN_COUNT=0

# Loop through selected choices to check for main function
for CHOICE in $CHOICES; do
    FILE="${FILES[$CHOICE]}"
    SRC_FILES+="$FILE "
    
    # Check if the file contains a main function
    if grep -q "int main" "$FILE" || grep -q "void main" "$FILE"; then
        MAIN_COUNT=$((MAIN_COUNT + 1))
        echo "Found main in: $FILE"
    else
        echo "No main function in: $FILE"
    fi
done

# Verify the number of main functions found
if [ "$MAIN_COUNT" -gt 1 ]; then
    echo "Error: Multiple definitions of main detected. Only one file should contain a main function."
    exit 1
elif [ "$MAIN_COUNT" -eq 0 ]; then
    echo "Error: No main function detected in the selected files."
    exit 1
fi

# Compiler flags (optional)
CFLAGS="-g -O2 -Wall"  # Debugging, optimization, and warnings

# Clean up any previous executable
if [ -f "$OUTPUT" ]; then
    echo "Removing previous executable..."
    rm -f "$OUTPUT"
fi
if [[ "$SELECTED_FILE" == "cpu_check.c" ]]; then
        echo "Compiling $SELECTED_FILE with sudo..."
        sudo gcc $CFLAGS -o $OUTPUT "$SELECTED_FILE"
    else
        echo "Compiling selected file: $SELECTED_FILE"
        gcc $CFLAGS -o $OUTPUT "$SELECTED_FILE"
    fi
# Compile the selected source files
echo "Compiling selected files: $SRC_FILES"
gcc $CFLAGS -o $OUTPUT $SRC_FILES

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./$OUTPUT
else
    echo "Compilation failed."
    exit 1
fi

