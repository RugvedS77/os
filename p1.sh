#!/bin/bash
# filename: student_db.sh

DB="students.txt"

# Ensure the database file exists
touch "$DB"

while true; do
    echo "===== Student Database Menu ====="
    echo "1. Add Student"
    echo "2. View All Students"
    echo "3. Search by Roll Number"
    echo "4. Delete by Roll Number"
    echo "5. Exit"
    echo "Enter your choice: "
    read choice

    case $choice in
        1)
            echo "Enter Roll Number: "
            read roll
            grep -q "^$roll," "$DB" && echo "Roll number already exists!" && continue
            echo "Enter Name: "
            read name
            echo "Enter Age: "
            read age
            echo "Enter Marks: "
            read marks
            echo "$roll,$name,$age,$marks" >> "$DB"
            echo "Student added."
            ;;
        2)
            echo -e "\nRoll\tName\tAge\tMarks"
            column -t -s ',' "$DB"
            ;;
        3)
            echo "Enter Roll Number to search: "
            read roll
            grep "^$roll," "$DB" | awk -F',' '{printf "Roll: %s\nName: %s\nAge: %s\nMarks: %s\n", $1, $2, $3, $4}'
            ;;
        4)
            echo "Enter Roll Number to delete: "
            read roll
            grep -v "^$roll," "$DB" > temp && mv temp "$DB"
            echo "Deleted (if existed)."
            ;;
        5)
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid choice"
            ;;
    esac
    echo ""
done
