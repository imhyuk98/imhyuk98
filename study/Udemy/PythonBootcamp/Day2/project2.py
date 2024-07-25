print("Welecome to the tip calculator")
total = input("What was the total bill? $")
percentage = input("What percentage would you like to give? 10, 12, or 15?")
people = input("How many people to split the bill?")
tip = float(total) * (int(percentage) / 100)
pay = "{:.2f}".format((float(total) + tip) / float(people) , 2)

print(f"Each person should take the bill : ${pay}")