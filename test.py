import numpy as np
import random
from decimal import *

def matrix_read (path):
    file = open(path, "r")
    rows, cols = [int(x) for x in next(file).split()]
    A = np.zeros((rows, cols))
    for line in file:
        i, j, value = [float(x) for x in line.split()]
        A[int(i-1)][int(j-1)] = Decimal(value)
    file.close()
    return A

def matrix_save (A, path):
    file = open(path, "w")
    file.write(str(len(A)) + " " + str(len(A[0])) + "\n")
    for i in range(len(A)):
        for j in range(len(A[0])):
            if (A[i][j] != 0):
                file.write(str(i+1) + " " + str(j+1) + " " + str(A[i][j]) + "\n")
    file.close()

def matrix_random (rows, cols, min, max):
    A = np.zeros((rows, cols))
    for i in range(len(A)):
        for j in range(len(A[0])):
            # A[i][j] = random.randint(min, max)
            A[i][j] = random.uniform(min, max)
    return A

def check (e):
    A = matrix_read("matrix/A_python.txt")
    B = matrix_read("matrix/B_python.txt")
    C = matrix_read("matrix/C.txt")
    AB = np.dot(A, B)
    if (len(C) != len(AB) or len(C[0]) != len(AB[0])):
        print("Algo errado!")
        return
    for i in range(len(C)):
        for j in range(len(C[0])):
            if(abs(AB[i][j] - C[i][j]) >= e):
                print("Algo errado!")
                return
    print("Tudo certo!")

def main ():
    check(0.5)
    # matrix_save(matrix_random(200, 100, -100, 100), "matrix/A_python.txt")
    # matrix_save(matrix_random(100, 200, -100, 100), "matrix/B_python.txt")

main()
