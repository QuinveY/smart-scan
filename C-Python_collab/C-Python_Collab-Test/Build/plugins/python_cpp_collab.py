def test():
		print("Hello from Python")

def getInteger():
    print('Python function getInteger() called')
    c = 100*50/10
    return c

def multiply(a, b):
    # print("Will compute", a, "times", b)
    c = 0
    for i in range(0, a):
        c = c + b
        
    return c

def filterFunction(*args, **kwargs):
    # import numpy
    # c = numpy.pi
    c = 0
    for arg in args:
        c = c + arg
    return c