from cs50  import get_string

s = get_string("Before: ")
print("After: ", end="")

for i in s:  #for each letter in string s
    print(i.upper(), end="")
print()