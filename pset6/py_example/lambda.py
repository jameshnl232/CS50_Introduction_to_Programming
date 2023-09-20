x = lambda a : a + 10 #lambda can take any number of arguments but can have only one expression
print(x(5))

x = lambda a, b : a * b
print(x(5, 6))

#in function
def myfunc(n):
  return lambda a : a * n

mydoubler = myfunc(2) #lambda is returned to mydoubler

print(mydoubler(11))

#Python Lambda Functions are anonymous function means that the function is without a name. 
#as already know that the def keyword is used to define a normal function in Python. 
#the lambda keyword is used to define an anonymous function in Python.