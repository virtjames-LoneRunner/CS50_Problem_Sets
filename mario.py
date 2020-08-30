rows = 0


while rows not in range(1, 9):
    try:
        rows = int(input("Height: "))
    except:
        continue



for x in range(1, rows + 1):
    print(" " * (rows - x) + "#" * x + "  " + "#" * x)



