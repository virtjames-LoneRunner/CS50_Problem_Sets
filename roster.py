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
list_of_students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)

# If the query does not return anything then the house argument is wrong
if list_of_students == []:
    print("House not found. Houses: Gryffindor, Hufflepuff, Ravenclaw, Slytherin")

# If query is successful check middle name for content
else:
    # Iterate through the list
    for item in list_of_students:
        first = item["first"]
        middle = item["middle"]
        last = item["last"]
        birth = item["birth"]

        # If there is no middle name then exclude
        if middle == None:
            print(first + " " + last + ", born " + str(birth))

        # If there is a middle name then include
        else:
            print(first + " " + middle + " " + last + ", born " + str(birth))