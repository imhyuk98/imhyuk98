print("The Love Calculator is calculating your score...")
name1 = input() # What is your name?
name2 = input() # What is their name?
# 🚨 Don't change the code above 👆
# Write your code below this line 👇
combined_names = name1 + name2
lower_names = combined_names.lower() # 소문자로 만들기

t = lower_names.count('t')
r = lower_names.count('r')
u = lower_names.count('u')
e = lower_names.count('e')

true_count = t + r + u + e

l = lower_names.count('l')
o = lower_names.count('o')
v = lower_names.count('v')
e = lower_names.count('e')

love_count = l + o + v + e

true_love = int(str(true_count) + str(love_count))

if true_love < 10 or true_love > 90:
    print(f'Your score is {true_love}, you go together like coke and mentos.')
elif true_love >= 40 and true_love <= 50:
    print(f'Your score is {true_love}, you are alright together.')
else:
    print(f'Your score is {true_love}.')