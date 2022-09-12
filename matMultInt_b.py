import timeit
import numpy as np 
from time import process_time


def matMultInt():
    
    R1 = 100
    C1 = 200
    R2 = C1
    C2 = R1

    mat1 = np.random.randint(-10, high=10, size=(R1, C1), dtype='l')
    mat2 = np.random.randint(-10, high=10, size=(R2, C2), dtype='l')

    rslt = np.zeros((R1, R1), dtype=int)

    for j in range(0, C2):
        for i in range(0, R1):
            for k in range(0, C1):
                rslt[i][j] += mat1[i][k] * mat2[k][j]

time_ex_int = [timeit.timeit(f'matMultInt()',
               number=100,
               globals=globals())]


time_CPU_int = 0
for i in range(0,100):
    t_st = process_time() 
    
    matMultInt()
    
    t_end = process_time() 
    
    time_CPU_int += t_end - t_st 

print("Execution time of matMultInt part b: ",time_ex_int)
print("CPU time of matMultInt part b: ",time_CPU_int)






