import os
import sys

i=5

A='import os%cimport sys%c%ci=%d%c%cA=%c%s%c%c%cif __name__ == %c__main__%c and i > 0:%c    if %c_%c in __file__: i -= 1%c    fn=%cSully_%c + str(i) + %c.py%c%c    f=open(fn, %cw%c)%c    sys.stdout=f%c    print(A %% (10,10,10,i,10,10,39,A,39,10,10,39,39,10,39,39,10,39,39,39,39,10,39,39,10,10,10,10,39,39))%c    f.close()%c    os.system(%cpython %c + fn)'

if __name__ == '__main__' and i > 0:
    if '_' in __file__: i -= 1
    fn='Sully_' + str(i) + '.py'
    f=open(fn, 'w')
    sys.stdout=f
    print(A % (10,10,10,i,10,10,39,A,39,10,10,39,39,10,39,39,10,39,39,39,39,10,39,39,10,10,10,10,39,39))
    f.close()
    os.system('python ' + fn)
