"""This is an implementation of the Reverse Polish Notation calculator"""
import re # regular expression

STACK = [] # the STACK

RANDOM_COUNTER = -1 # the counter for the random numbers



# @return - a random number
def random():
    """This function will return a random number from array of random numbers"""
    global RANDOM_COUNTER

    random_ints = [
        1804289383,
        846930886,
        1681692777,
        1714636915,
        1957747793,
        424238335,
        719885386,
        1649760492,
        596516649,
        1189641421,
        1025202362,
        1350490027,
        783368690,
        1102520059,
        2044897763,
        1967513926,
        1365180540,
        1540383426,
        304089172,
        1303455736,
        35005211,
        521595368,
        1804289383
    ]

    if RANDOM_COUNTER < len(random_ints) - 1:
        RANDOM_COUNTER += 1
    else:
        # if the counter is at the end of the array, then reset the counter
        RANDOM_COUNTER = 0

    return random_ints[RANDOM_COUNTER]



# @params - number to be converted
# @return - the number converted to 32 bits
def int32(number):
    """This function will return the 32-bit representation of the number"""

    if number is not None:
        return \
            2147483647 if number > 2147483647 else \
            -2147483648 if number < -2147483648 else \
            int(number)
    return None



# @params - the operands needed to be handled
# @return - the result of the expression
def divide(ops):
    """This function will divide the first operand by the second operand"""
    if ops[0] == 0:
        print("Divide by 0.")
        # push the operands back to the STACK
        STACK.append(ops[1])
        return ops[0]
    return ops[1] // ops[0]



# @params - the operands needed to be handled
# @return - the result of the expression
def power(ops):
    """This function will return the first operand to the power of the second operand"""
    if ops[0] < 0:
        print("Negative power.")
        # push the operands back to the STACK
        STACK.append(ops[1])
        return ops[0]
    return ops[1] ** ops[0]



# @params - the operands needed to be handled
# @return - the result of the expression
def mod(ops):
    """This function will return the remainder of the first operand divided by the second operand"""
    if ops[0] == 0:
        print("Divide by 0.")
        # push the operands back to the STACK
        STACK.append(ops[1])
        return ops[0]
    return ops[1] % ops[0]



# @params - the operator needed to be handled
# @return - the result of the expression
def handle_operator(operator):
    """This funtion will pop the last two elements from the STACK,
    solve the expression and return the result"""

    ops = [STACK.pop(), STACK.pop()] # operands

    operators = {
        "+": lambda ops: ops[0] + ops[1],
        "-": lambda ops: ops[1] - ops[0],
        "*": lambda ops: ops[0] * ops[1],
        "/": divide,
        "^": power,
        "%": mod
    }

    return operators[operator](ops)


# @params - the feature needed to be handled
def handle_commands(command):
    """This function will handle the features"""

    if command == 'r':
        handle_int(random()) # adds a random number to the STACK
    elif command == 'd': # if the feature is d, then it will print the STACK
        if not STACK:
            print("-2147483648")
        else:
            for element in STACK:
                print(element)
    elif command == '=':
        try:
            print(STACK[-1]) # print the last element in the STACK
        except IndexError:
            print("Stack empty.")



# @params - the operator needed to be handled
def handle_expression(operator):
    """This function will pop the last two elements from the STACK,
    solve the expression, and return the result"""

    if len(STACK) < 2:
        print("Stack underflow.")
    else:
        result = handle_operator(operator) # the result of the expression
        STACK.append(int32(result)) # push the result to the STACK



# @params - the string the user has typed
def handle_int(element):
    """This function will try to append the integer to the STACK,
    and print an error message if the integer is not valid"""

    try: # try to convert the element to a number
        val = int(element)
        if len(STACK) > 22: # if the STACK has more than 23 elements, then print an error
            print("Stack overflow.")
        else:
            STACK.append(int32(val))
    except ValueError:
        # if the element is not a number, then recursively call process_command()
        # with new input from infix_to_postfix()
        process_command(infix_to_postfix(element))



# @params - the string the user has typed
def double_negation(elements):
    """This function will return the elements with double negation removed"""
    for index, element in enumerate(elements):
        if element == '-' and elements[index + 1] == '-':
            elements[index] = '+' # replace the double negation with plus signs
            elements[index + 1] = '+'
    return elements



# @params - the string the user has typed
# @return - the string in postfix notation
def infix_to_postfix(expression):
    """This function will convert the expression to postfix
    notation, using the shunting yard algorithm"""

    precedence = {
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2,
        '^': 3,
        '%': 2,
    }

    postfix = [] # the postfix expression
    used_operators = [] # the operators used

    tokens = re.split(" *(\\D|\\d+) *", expression) # split the expression into tokens
    tokens = [token for token in tokens if token != ''] # remove empty tokens
    tokens = double_negation(tokens) # remove double negation

    command_flag = False # flag to check if the expression is a command
    # the tokens that are left over after the expression is converted to postfix
    tokens_left_over = ''

    for token in tokens:
        if command_flag:
            # if the command_flag is true, then append the token to the tokens_left_over
            tokens_left_over += token
            continue
        if not re.match(' *([+\\-*/^%rd=]|\\d+) *', token):
            # if the token is not a valid command, then print an error message
            print("Unrecognised operator or operand '" + token + "'.")
        elif token in precedence:
            # if the token is an operator, then pop the operators from the used_operators
            # and append them to the postfix queue
            while len(used_operators) > 0 and used_operators[-1] in precedence \
                and precedence[used_operators[-1]] >= precedence[token]:
                postfix.append(used_operators.pop())
            used_operators.append(token)
        elif token in ['r', 'd', '=']:
            # if the token is a command, then set the command_flag to true
            # and add the token to bottom of the used_operators
            used_operators = [token] + used_operators
            command_flag = True
        else:
            # if the token is an integer, then append it to the postfix queue
            postfix.append(token)

    while len(used_operators) > 0:
        # pop the remaining operands from the used_operators and append them to the postfix queue
        postfix.append(used_operators.pop())

    # return the postfix queue by string for process_command()
    return ' '.join(postfix) + ' ' + tokens_left_over



# @params - the string the user has typed
def process_command(command):
    """This function will parse the string and push the numbers to the STACK,
    and call handle_operator()/handle_commands() when an operator/command is found"""
    comment_flag = False
    command = command.split()

    for element in command:
        if element == '#': # if the element is a comment, then set the comment_flag to true
            comment_flag = not comment_flag
        elif comment_flag:
            continue
        elif element in ['r', 'd', '=']: # if the element is a feature, then call handleFeatures()
            handle_commands(element)
        elif element in ['+', '-', '*', '/', '^', '%']:
            # if the element is an operator, then call handle_expression()
            handle_expression(element)
        else: # if the element is not a comment, then try to append the element to the STACK
            handle_int(element)
    return 0



#Entry point of the program
if __name__ == "__main__":
    while True:
        try:
            cmd = input()
            pc = process_command(cmd)
        except EOFError:
            exit()
