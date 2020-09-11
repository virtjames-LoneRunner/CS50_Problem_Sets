# Mario (more) sentimental

# Define rows
rows = 0

# Ensure that the user's input is within the desired range
while rows not in range(1, 9):
    
    # Try if conversion returns an error to determine if it's actually an integer
    try:
        rows = int(input("Height: "))
    
    # If the conversion returned an error, go back to the while loop
    except:
        continue

# Print the pyramid
for x in range(1, rows + 1):
    print(" " * (rows - x) + "#" * x + "  " + "#" * x)