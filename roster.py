from sys import argv, exit
from cs50 import SQL

# Print an error message if the right number of arguments is not provided
if len(argv) != 2:
    print("Usage: roster.py [House]")
    exit(1)

# Assign argv[1] to house
house = argv[1].title()

# Create database object
db = SQL("sqlite:///students.db")

# Query students.db for student data
list_of_students =  db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)

if list_of_students == []:
    print("House not found")
else:
    for item in list_of_students:
        first = item["first"]
        middle = item["middle"]
        last = item["last"]
        birth = item["birth"]

        if middle == None:
            print(first + " " + last + ", born " + str(birth))

        else:
            print(first + " " + middle + " " + last + ", born " + str(birth))