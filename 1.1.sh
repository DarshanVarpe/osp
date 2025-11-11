#!/bin/bash

FILE="address.txt"

if [ ! -f "$FILE" ]; then
    touch "$FILE"
fi

show_menu() {
    echo "=============================="
    echo "      ADDRESS BOOK MENU       "
    echo "=============================="
    echo "1. Search Address Book"
    echo "2. Add an Address Book Entry"
    echo "3. Remove an Address Book Entry"
    echo "4. Quit"
    echo "=============================="
}

search_entry() {
    echo -n "Enter name or ID to search: "
    read keyword
    echo "--------------------------------"
    grep -i "$keyword" "$FILE" | awk -F ";" '{print "ID: " $1 ", Name: " $2 ", Phone: " $3}'
    if [ $? -ne 0 ]; then
        echo "No matching record found."
    fi
    echo "--------------------------------"
}

add_entry() {
    echo -n "Enter ID: "
    read id
    grep -q "^$id;" "$FILE"
    if [ $? -eq 0 ]; then
        echo "Error: ID already exists!"
        return
    fi

    echo -n "Enter Name: "
    read name
    echo -n "Enter Phone Number: "
    read phone

    echo "$id;$name;$phone" >> "$FILE"
    echo "Entry added successfully!"
}

remove_entry() {
    echo -n "Enter ID to remove: "
    read id
    grep -q "^$id;" "$FILE"
    if [ $? -ne 0 ]; then
        echo "No entry found with ID $id."
        return
    fi

    grep -v "^$id;" "$FILE" > temp.txt && mv temp.txt "$FILE"
    echo "Entry with ID $id removed successfully!"
}

while true
do
    show_menu
    echo -n "Enter your choice [1-4]: "
    read choice

    case $choice in
        1) search_entry ;;
        2) add_entry ;;
        3) remove_entry ;;
        4) echo "Exiting Address Book. Goodbye!"; exit 0 ;;
        *) echo "Invalid choice. Please select 1-4." ;;
    esac
done




