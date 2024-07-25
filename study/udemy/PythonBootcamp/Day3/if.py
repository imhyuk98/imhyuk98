print("Welcome to the rollercoaster!")
height = int(input("What is your height in cm? "))
bill = 0

if height > 120:
    print("You can ride the rollercoaster!")
    age = int(input("What is your age? "))
    if age >= 18:
        bill = 10
        print("Adult tickets are $10.")
    elif 12 <= age < 18:
        bill = 9
        print("Youth tickets are $9.")
    elif age >= 45 and age <= 55:
        print("Everything is going to be ok. Have a free ride on us!")
    else:
        bill = 7
        print("Child tickets are $7.")

    wants_photo = input("Would you want a photo taken? Y or N")
    if wants_photo == "Y":
        bill += 3
        print("Your bill is: $" + str(bill))
    else:
        print("Your bill is: $" + str(bill))
else:
    print("You can't ride the rollercoaster!")
