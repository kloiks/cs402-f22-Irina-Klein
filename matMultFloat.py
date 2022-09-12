import timeit
import numpy as np 



def matMultFloat():
    
    R1 = 100
    C1 = 200
    R2 = C1
    C2 = R1

    mat1 = np.random.rand(R1, C1) 
    mat2 = np.random.rand(R2, C2)

    rslt = np.zeros((R1, R1), dtype=float)
    
    for i in range(0, R1):
        for j in range(0, C2):
            for k in range(0, R2):
                rslt[i][j] += mat1[i][k] * mat2[k][j]



print([timeit.timeit(f'matMultFloat()',
               number=50,
               globals=globals())])







