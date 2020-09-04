from sys import argv, exit
import csv

# Make sure there are 3 arguments
if len(argv) != 3:
    print("Usage python3 dna.py [database file] [sequence file]")
    exit(1)


# Open the database
database = argv[1]
rows = []

# This gives us the headers of the given database
with open(database, 'r') as file:
    headers = list(csv.reader(file))
    headers[0].remove("name")
    headers = headers[0]

# This creates a list of the individual rows appended as dictionaries for random access
with open(database, 'r') as file:
    csv_reader = csv.DictReader(file)

    # Append each row (as dictionaries) to the rows list
    for row in csv_reader:  
        rows.append(row)


# Open the sequence file
in_sequence = argv[2]
with open(in_sequence, 'r') as seq:
    main_sequence = seq.readline()

# Variables for parsing through the sequence
cursor = ''
list_of_values = []
dictionary_of_values = {}

# Create a dictionary with the headers as keys and a default value of 0
for header in headers:
    dictionary_of_values[header] = 0

# Iterate through the sequence
for header in headers:
    i = 0
    count = 0
    max_count = 0

    # This resets the sequence for each header check as sequences gets erased
    sequence = main_sequence
    while i < len(sequence):
        cursor = sequence[0:len(header)]
        if cursor == header:
            count += 1
            
            # Assign the greater of the two values into max_count
            max_count = max(max_count, count)

            # If the headers match then we need to remove the matching STR so it's characters
            # won't be included in parsing anymore
            sequence = sequence[len(header):]

        else:
            count = 0

            # If the headers doesn't match, it's enough to remove the first part of that strand
            sequence = sequence[1:]

    dictionary_of_values[header] = max_count
    

# Check for a match
for x in range(len(rows)):
    valid = 0

    # Determines if each header values match
    for header in headers:
        # If the header values don't match, add one to valid to disqualify it
        if dictionary_of_values[header] != int(rows[x][header]):
            valid += 1

    # If valid remains 0 then all the headers match up
    if valid == 0:
        print(rows[x]["name"])
        exit(0)

# If none of the dictionaries match, it's not in the list
print("No match")
