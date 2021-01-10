#1
def func():
    b=1
if __name__ == "__main__":
    #2
    func()
    a='#1%cdef func():%c    b=1%cif __name__ == "__main__":%c    #2%c    func()%c    a=%r%c    print(a %% (10,10,10,10,10,10,a,10))'
    print(a % (10,10,10,10,10,10,a,10))
