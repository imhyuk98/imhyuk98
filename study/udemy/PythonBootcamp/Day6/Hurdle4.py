def turn_right():
    turn_left()
    turn_left()
    turn_left()

def jump():
    turn_left()
    move()
    turn_right()
    move()
    turn_right()
    move()
    turn_left()

def wall_front():
    turn_left()
    move()
    turn_right()

while at_goal() != True:
    if front_is_clear() and right_is_clear:
        move()
        turn_right()
    elif wall_in_front() and right_is_clear:
        turn_left()
    elif wall_in_front():
        turn_right()