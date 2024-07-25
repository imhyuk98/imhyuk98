#Password Generator Project
import random
letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
numbers = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
symbols = ['!', '#', '$', '%', '&', '(', ')', '*', '+']

print("Welcome to the PyPassword Generator!")
nr_letters= int(input("How many letters would you like in your password?\n"))
nr_symbols = int(input(f"How many symbols would you like?\n"))
nr_numbers = int(input(f"How many numbers would you like?\n"))

length_letters = len(letters)
length_numbers = len(numbers)
length_symbols = len(symbols)

final_letters = ''
choose_letters = ''
for l in range(1, nr_letters+1):
    random_letters = (random.randint(0, length_letters - 1))
    choose_letters = str(letters[random_letters])
    final_letters += choose_letters

final_numbers = ''
choose_numbers = ''
for n in range(1, nr_numbers+1):
    random_numbers = (random.randint(0, length_numbers - 1))
    choose_numbers = str(numbers[random_numbers])
    final_numbers += choose_numbers

final_symbols = ''
choose_symbols = ''
for s in range(1, nr_symbols+1):
    random_symbols = (random.randint(0, length_symbols - 1))
    choose_symbols = str(symbols[random_symbols])
    final_symbols += choose_symbols

password = str(final_letters + final_numbers + final_symbols)
print(password)


#Eazy Level - Order not randomised:
#e.g. 4 letter, 2 symbol, 2 number = JduE&!91


#Hard Level - Order of characters randomised:
#e.g. 4 letter, 2 symbol, 2 number = g^2jk8&P

# password_list = []
#
# for char in range(1, nr_letters + 1):
#   password_list.append(random.choice(letters))
#
# for char in range(1, nr_symbols + 1):
#   password_list += random.choice(symbols)
#
# for char in range(1, nr_numbers + 1):
#   password_list += random.choice(numbers)
#
# print(password_list)
# random.shuffle(password_list)
# print(password_list)
#
# password = ""
# for char in password_list:
#   password += char
#
# print(f"Your password is: {password}")