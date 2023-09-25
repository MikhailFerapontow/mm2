from sparse_matrix import *
from model import _cholesky_decomp
from linalg import *

B = [3.56, 1.27, 0, 1.20, 0, 0, 0, 0, 0,
        1.27, 5.82, 1.58, 0, 1.81, 0, 0, 0, 0,
        0, 1.58, 3.31, 1.33, 0, 1.83, 0, 0, 0,
        1.20, 0, 1.33, 5.08, 1.20, 0, 1.87, 0, 0,
        0, 1.81, 0, 1.20, 5.67, 1.94, 0, 1.24, 0,
        0, 0, 1.83, 0, 1.94, 3.44, 1.78, 0, 1.25,
        0, 0, 0, 1.87, 0, 1.78, 4.03, 1.70, 0,
        0, 0, 0, 0, 1.24, 0, 1.70, 5.29, 1.64,
        0, 0, 0, 0, 0, 1.25, 0, 1.64, 5.64,]

Nx = 2
Ny = 2

N = (Nx + 1) * (Ny + 1)

A = SparseMatrixCOO()

k = 0
for i in range(N):
    for j in range(N):
        x = B[k]
        k += 1
        A.set(i, j, x)

sz = A.size()

print("A")
for i in range(sz):
    for j in range(sz):
        v = A.get(i, j)
        if v == 0:
            print(f"{v} & ", end="")
        else:
            print(f"{v:.2f} & ", end="")
    print()

L = _cholesky_decomp(A, Nx, Ny)

print("L")
for i in range(sz):
    for j in range(sz):
        v = L.get(i, j)
        if v == 0:
            print(f"{v} & ", end="")
        else:
            print(f"{v:.2f} & ", end="")
    print()

L = mul_mm(L, transpose(L))

print("B")
for i in range(sz):
    for j in range(sz):
        v = L.get(i, j)
        if v == 0:
            print(f"{v} & ", end="")
        else:
            print(f"{v:.2f} & ", end="")
    print()