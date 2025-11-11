#!/bin/bash
# ---------------------------------------
# File Management Program (Bash Script)
# ---------------------------------------

# Function to test if a file exists
test_file() {
    read -p "Enter filename to test: " filename
    if [ -f "$filename" ]; then
        echo " File '$filename' exists."
    else
        echo " File '$filename' does NOT exist."
    fi
}

# Function to read (display) file content
read_file() {
    read -p "Enter filename to read: " filename
    if [ -f "$filename" ]; then
        echo "------ Contents of $filename ------"
        cat "$filename"
        echo "----------------------------------"
    else
        echo " File '$filename' not found!"
    fi
}

# Function to delete a file
delete_file() {
    read -p "Enter filename to delete: " filename
    if [ -f "$filename" ]; then
        rm "$filename"
        echo "🗑️ File '$filename' deleted successfully."
    else
        echo " File '$filename' not found!"
    fi
}

# Function to list all files in the current directory
list_files() {
    echo "📂 Files in current directory:"
    ls -1
}

# Main menu function
menu() {
    while true; do
        echo "============================="
        echo "📁 File Management Menu"
        echo "============================="
        echo "1. Test if file exists"
        echo "2. Read a file"
        echo "3. Delete a file"
        echo "4. Display list of files"
        echo "5. Quit"
        echo "============================="
        read -p "Enter your choice (1-5): " choice

        case $choice in
            1) test_file ;;
            2) read_file ;;
            3) delete_file ;;
            4) list_files ;;
            5) echo "👋 Exiting program."; break ;;
            *) echo "⚠️ Invalid choice! Try again." ;;
        esac
        echo
    done
}


menu