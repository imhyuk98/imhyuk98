print("Thank you for choosing Python Pizza Deliveries!")
size = input() # What size pizza do you want? S, M, or L
add_pepperoni = input() # Do you want pepperoni? Y or N
extra_cheese = input() # Do you want extra cheese? Y or N
# 🚨 Don't change the code above 👆
# Write your code below this line 👇
bill = 0
if size == 'L':
  bill = 25
  if add_pepperoni == 'Y':
    bill += 3
elif size == 'M':
  bill = 20
  if add_pepperoni == 'Y':
    bill += 3
elif size == 'S':
  bill = 15
  if add_pepperoni == 'Y':
    bill += 2
else:
  print("사이즈를 다시 입력하시오.")

if extra_cheese == 'Y':
  bill +=1
print(f"Your final bill is: ${bill}.")