import random

rock = '''
    _______
---'   ____)
      (_____)
      (_____)
      (____)
---.__(___)
'''

paper = '''
    _______
---'   ____)____
          ______)
          _______)
         _______)
---.__________)
'''

scissors = '''
    _______
---'   ____)____
          ______)
       __________)
      (____)
---.__(___)
'''

#Write your code below this line 👇

player_RPS = input("Please enter ROCK, PAPER, SCISSORS: ").upper()
com_num = random.randint(0, 2) # 0 : ROCK 1 : PAPER 2: SCISSORS
if com_num == 0:
    com_RPS = 'ROCK'
    print(f'Computer : {com_RPS}\n' + rock)
elif com_num == 1:
    com_RPS = 'PAPER'
    print(f'Computer : {com_RPS}\n' + paper)
else:
    com_RPS = 'SCISSORS'
    print(f'Computer : {com_RPS}\n' + scissors)

print('====================================\n')
if player_RPS.upper() == 'ROCK':
    print(f'Player : {player_RPS}\n' + rock)
    if com_num == 0:
        print("Draw!")
    elif com_num == 1:
        print("You lose!")
    else:
        print("You win!")
elif player_RPS.upper() == 'PAPER':
    print(f'Player : {player_RPS}\n' + paper)
    if com_num == 0:
        print("You win!")
    elif com_num == 1:
        print("Draw!")
    else:
        print("You lose!")
else:
    print(f'Player : {player_RPS}\n' + scissors)
    if com_num == 0:
        print("You lose!")
    elif com_num == 1:
        print("You win!")
    else:
        print("Draw")

