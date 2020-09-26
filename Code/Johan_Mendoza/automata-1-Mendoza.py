
"""
L'ho fatto su python, ma successivamente lo faro in C++ e lo carichero.
"""

if __name__ == '__main__':
    #inputsize = 4
    inputs = ['a','a','b','c']
    stato = "S0" #di default
    print("Stato iniziale:",stato)
    for i in inputs:
        if i == "a" and stato == "S0":
            stato = "S2"
        elif i == "a" and stato == "S2":
            stato = "S0"
        elif i == "b" and stato == "S0":
            stato = "S1"
        elif i == "b" and stato == "S1":
            stato = "S1"
        elif i == "c" and stato == "S0":
            stato = "S3"
            break
        elif i == "c" and stato == "S1":
            stato = "S3"
            break
        else:
            print("Error")
            break
        print("Stato attuale:",stato)
    print("Stato finale:",stato)
    print("Done")