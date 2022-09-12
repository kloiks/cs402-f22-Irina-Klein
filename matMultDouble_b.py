import timeit
import numpy as np 
from time import process_time


def matMultDouble():
    
    R1 = 100
    C1 = 200
    R2 = C1
    C2 = R1

    mat1 = np.random.rand(R1, C1) 
    mat2 = np.random.rand(R2, C2)

    rslt = np.zeros((R1, R1), dtype=float)
    
    for j in range(0, C2):
        for i in range(0, R1):
            for k in range(0, C1):
                rslt[i][j] += mat1[i][k] * mat2[k][j]
    

time_ex_d = [timeit.timeit(f'matMultDouble()',
               number=100,
               globals=globals())]


time_CPU_d = 0
for i in range(0,100):
    t_st = process_time() 
    
    matMultDouble()
    
    t_end = process_time() 
    
    time_CPU_d += t_end - t_st 



print("Execution time of matMultDouble part a: ",time_ex_d)
print("CPU time of matMultDouble part a: ",time_CPU_d)






