import timeit
import numpy as np 



def matMultInt():
    
    R1 = 100
    C1 = 200
    R2 = C1
    C2 = R1

    mat1 = np.random.randint(-10, high=10, size=(R1, C1), dtype='l')
    mat2 = np.random.randint(-10, high=10, size=(R2, C2), dtype='l')

    rslt = np.zeros((R1, R1), dtype=int)
    
    
    for i in range(0, R1):
        for j in range(0, C2):
            for k in range(0, R2):
                rslt[i][j] += mat1[i][k] * mat2[k][j]



print([timeit.timeit(f'matMultInt()',
               number=50,
               globals=globals())])







