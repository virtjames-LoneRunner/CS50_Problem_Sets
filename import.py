import cs50
from cs50 import SQL
from sys import argv, exit
import csv

# Print an error message if the right number of arguments is not provided
if len(argv) != 2:
    print("Usage: import.py [CSV Filename]")
    exit(1)

# Create database object
db = SQL("sqlite:///students.db")

# Open the CSV file and write contents to a list as dictionaries
csv_filename = argv[1]
with open(csv_filename, 'r') as csv_file:
    cursor = csv.DictReader(csv_file)

    data_list = []

    # Appends each dictionary into a list for looping and indexing
    for row in cursor:
        data_list.append(row)

# Separate the name of each person into first, middle, and last names
for data in data_list:
    name = data["name"]

    # Returns a list of the names using the spaces as separator
    name = name.split()

    # Create a dictionary for storing separated names
    name_dict = {}

    # If length of list "name" is 3 then there is a middle name
    if len(name) == 3:
        name_dict["last"] = name[2]
        name_dict["middle"] = name[1]
        name_dict["first"] = name[0]

    # Else leave middle name to NULL
    else:
        name_dict["last"] = name[1]
        name_dict["middle"] = None
        name_dict["first"] = name[0]

    # Changes the value of the key name to a dictionary of separated names
    data["name"] = name_dict


# Inserting data into the database
for item in data_list:
    first_name = item["name"]['first']
    middle_name = item["name"]["middle"]
    last_name = item["name"]["last"]
    house = item["house"]
    birth = item["birth"]
    
    # Insert each item into database
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
               first_name, middle_name, last_name, house, birth)