import math

character_list = []

letters = 0
words = 1
sentences = 0

user_input = input("Text: ")

for character in user_input:
    character_list.append(character.lower())

for char in character_list:
    if char.isalpha():
        letters += 1
    elif char.isspace():
        words += 1
    elif char == "." or char == "?" or char == "!":
        sentences += 1

#print(str(letters) + " letter(s)")
#print(str(words) + " word(s)")
#print(str(sentences) + " sentence(s)")

index = 0.0588 * (letters/words * 100) - 0.296 * (sentences/words * 100) - 15.8
index = int(round(index))

if index < 1:
    print("Before Grade 1")

elif index >= 16:

    print("Grade 16+")

else:
    print("Grade " + str(index))
