"""
  Computes next state. Returns the following

    -1 : input sequence not legal
    -2 : we're in final state
"""

import sys

def nextstate(current_state,inputs):

    if inputs == "a" and current_state == "S0":
        current_state = "S2"
    elif inputs == "a" and current_state == "S2":
        current_state = "S0"
    elif inputs == "b" and current_state == "S0":
        current_state = "S1"
    elif inputs == "b" and current_state == "S1":
        current_state = "S1"
    elif inputs == "c" and current_state == "S0":
        current_state = "S3"
        return -2
    elif inputs == "c" and current_state == "S1":
        current_state = "S3"
        return -2
    else:
        return -1
    return current_state

if __name__ == '__main__':
    #print(sys.argv[1])

    #get input from command line
    if len(sys.argv) < 2:
        print("Error, insert an input")
        sys.exit()
    elif len(sys.argv) > 2:
        print("Error, expected only 1 argoment/array")
        sys.exit()
    else:
        inputs = list(map(str, sys.argv[1].rstrip().split(",")))

    #inputs = ['a','a','b','c']

    current_state = "S0" #di default

    for i in inputs:

        print("Current state:", current_state)

        stato = nextstate(current_state,i)

        if stato == -1:
            print("input sequence ({inputs}) not legal for state {stato}".format(inputs=i, stato=current_state))
            break

        elif stato == -2:
            print("we're in final state: S3")
            break
        else:

            print("Next state:",stato)

            current_state = stato

    print("Done")