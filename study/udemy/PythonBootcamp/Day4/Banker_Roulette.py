names_string = 'Angela, Ben, Jenny, Michael, Chloe'
names = names_string.split(", ")
# names_string contains the input values provided.
# The code above converts the input into an array seperating
# each name in the input by a comma and space.
# 🚨 Don't change the code above 👆

import random
num_items = len(names)

random_number = random.randint(0, num_items-1)
print(names[random_number] + " is going to buy the meal today!")