#!/bin/bash
# Address Book Program using Bash Shell

FILE="addressbook.txt"

# Create the address book file if it doesn’t exist
if [ ! -f "$FILE" ]; then
    touch "$FILE"
fi

# Function to display the menu
show_menu() {
    echo "===================================="
    echo "        ADDRESS BOOK MENU           "
    echo "===================================="
    echo "1. Search Address Book"
    echo "2. Add Entry"
    echo "3. Remove Entry"
    echo "4. Edit Entry"
    echo "5. Display All Entries"
    echo "6. Quit"
    echo "===================================="
}

# 1️⃣ Search an entry
search_entry() {
    echo -n "Enter name or ID to search: "
    read keyword
    echo "------------------------------------"
    grep -i "$keyword" "$FILE" | awk -F ":" '{print "ID: "$1", Name: "$2", Phone: "$3}'
    if [ $? -ne 0 ]; then
        echo "No matching record found."
    fi
    echo "------------------------------------"
}

# 2️⃣ Add a new entry
add_entry() {
    echo -n "Enter ID: "
    read id
    grep -q "^$id:" "$FILE"
    if [ $? -eq 0 ]; then
        echo "Error: ID already exists!"
        return
    fi

    echo -n "Enter Name: "
    read name
    echo -n "Enter Phone Number: "
    read phone

    echo "${id}:${name}:${phone}" >> "$FILE"
    echo "Entry added successfully!"
}

# 3️⃣ Remove an entry
remove_entry() {
    echo -n "Enter ID to remove: "
    read id
    grep -q "^$id:" "$FILE"
    if [ $? -ne 0 ]; then
        echo "No entry found with ID $id."
        return
    fi

    grep -v "^$id:" "$FILE" > temp.txt && mv temp.txt "$FILE"
    echo "Entry with ID $id removed successfully!"
}

# 4️⃣ Edit an entry
edit_entry() {
    echo -n "Enter ID to edit: "
    read id
    grep -q "^$id:" "$FILE"
    if [ $? -ne 0 ]; then
        echo "No entry found with ID $id."
        return
    fi

    # Extract old record
    old_record=$(grep "^$id:" "$FILE")

    old_name=$(echo "$old_record" | awk -F ":" '{print $2}')
    old_phone=$(echo "$old_record" | awk -F ":" '{print $3}')

    echo "Old Name: $old_name"
    echo "Old Phone: $old_phone"

    echo -n "Enter new Name (leave blank to keep old): "
    read new_name
    echo -n "Enter new Phone (leave blank to keep old): "
    read new_phone

    # Use old values if new ones not given
    if [ -z "$new_name" ]; then
        new_name=$old_name
    fi
    if [ -z "$new_phone" ]; then
        new_phone=$old_phone
    fi

    # Replace old record with new one
    grep -v "^$id:" "$FILE" > temp.txt
    echo "${id}:${new_name}:${new_phone}" >> temp.txt
    mv temp.txt "$FILE"

    echo "Entry updated successfully!"
}

# 5️⃣ Display all entries
display_entries() {
    echo "------------------------------------"
    echo "        ADDRESS BOOK RECORDS        "
    echo "------------------------------------"
    if [ ! -s "$FILE" ]; then
        echo "No records found."
    else
        awk -F ":" '{print "ID: "$1", Name: "$2", Phone: "$3}' "$FILE"
    fi
    echo "------------------------------------"
}

# Main menu loop
while true
do
    show_menu
    echo -n "Enter your choice [1-6]: "
    read choice

    case $choice in
        1) search_entry ;;
        2) add_entry ;;
        3) remove_entry ;;
        4) edit_entry ;;
        5) display_entries ;;
        6) echo "Exiting program..."; exit 0 ;;
        *) echo "Invalid choice. Please select 1-6." ;;
    esac
done
