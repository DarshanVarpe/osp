#!/bin/bash

# Phonebook file
FILE="phonebook.txt"

# Create the file if it doesn’t exist
if [ ! -f "$FILE" ]; then
    touch "$FILE"
fi

# Function to display menu
show_menu() {
    echo "================================="
    echo "         PHONEBOOK MENU          "
    echo "================================="
    echo "1. Add a New Entry"
    echo "2. Search by Name or Number"
    echo "3. Display All (Sorted by Last Name)"
    echo "4. Delete an Entry"
    echo "5. Quit"
    echo "================================="
}

# 1️⃣ Add a new entry
add_entry() {
    echo -n "Enter First Name: "
    read fname
    echo -n "Enter Last Name: "
    read lname
    echo -n "Enter Phone Number: "
    read phone

    # Write data to the file, separated by a TAB
    echo -e "${fname}\t${lname}\t${phone}" >> "$FILE"
    echo "Entry added successfully!"
}

# 2️⃣ Search by name or number
search_entry() {
    echo -n "Enter name or phone number to search: "
    read keyword
    echo "---------------------------------"
    grep -i "$keyword" "$FILE" | awk -F "\t" '{print "First Name: "$1", Last Name: "$2", Phone: "$3}'
    if [ $? -ne 0 ]; then
        echo "No matching record found."
    fi
    echo "---------------------------------"
}

# 3️⃣ Display all entries sorted by last name
display_sorted() {
    echo "---------------------------------"
    echo "Phonebook (sorted by Last Name):"
    echo "---------------------------------"
    sort -k2,2 "$FILE" | awk -F "\t" '{print "First Name: "$1", Last Name: "$2", Phone: "$3}'
    echo "---------------------------------"
}

# 4️⃣ Delete an entry
delete_entry() {
    echo -n "Enter phone number to delete: "
    read phone
    grep -q "$phone" "$FILE"
    if [ $? -ne 0 ]; then
        echo "No entry found with phone number $phone."
        return
    fi

    grep -v "$phone" "$FILE" > temp.txt && mv temp.txt "$FILE"
    echo "Entry deleted successfully!"
}

# Main loop
while true
do
    show_menu
    echo -n "Enter your choice [1-5]: "
    read choice

    case $choice in
        1) add_entry ;;
        2) search_entry ;;
        3) display_sorted ;;
        4) delete_entry ;;
        5) echo "Goodbye!"; exit 0 ;;
        *) echo "Invalid choice, try again!" ;;
    esac
done
