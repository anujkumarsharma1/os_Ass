#!/bin/bash

file="addressbook.txt"

while true
do
    echo
    echo "===== ADDRESS BOOK ====="
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    echo

    read -p "Enter your choice: " choice

    case $choice in
        1)
            touch "$file"
            echo "Address book created."
            ;;
        2)
            if [ -f "$file" ]; then
                cat "$file"
            else
                echo "Address book does not exist yet."
            fi
            ;;
        3)
            read -p "Enter name: " name
            read -p "Enter phone: " phone
            echo "$name $phone" >> "$file"
            echo "Record inserted."
            ;;
        4)
            read -p "Enter name to delete: " name
            sed -i "/^$name /d" "$file"
            echo "Record deleted."
            ;;
        5)
            read -p "Enter name to modify: " name
            sed -i "/^$name /d" "$file"
            read -p "Enter new name: " newname
            read -p "Enter new phone: " newphone
            echo "$newname $newphone" >> "$file"
            echo "Record modified."
            ;;
        6)
            echo "Exiting."
            exit 0
            ;;
        *)
            echo "Invalid choice."
            ;;
    esac
done
