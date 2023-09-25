import math
import unittest
from random import random

from sparse_matrix import *
from linalg import *
from model import _cholesky_decomp


class TestConjgrad(unittest.TestCase):

    def _init_data(self, Nx, Ny):

        n = (Nx + 1) * (Ny + 1)
        m = Nx + 1

        A = SparseMatrixCOO()
        x = [0] * n

        for i in range(n):
            a = (random() + 1) * 4
            A.set(i, i, a)

        for i in range(n - 1):
            b = (random() + 1) * 1
            A.set(i, i + 1, b)
            A.set(i + 1, i, b)

        for i in range(n - m):
            c = (random() + 1) * 1
            A.set(i, i + m, c)
            A.set(i + m, i, c)

        for i in range(n):
            x[i] = (random() + 1) * 1

        # A = mul_mm(A, transpose(A))
        b = mul_mv(A, x)

        return (A.to_CSR(), b, x)

    def _func(self, N):

        eps = 1e-5

        Nx = 9
        Ny = 9

        A, b, x = self._init_data(Nx, Ny)
        N = (Nx + 1) * (Ny + 1)
        x0 = [0] * N

        # print(f"x")
        # for v in x:
        #     print(f"{v:.2f},")

        # print(f"b")
        # for v in b:
        #     print(f"{v:.2f},")

        L = _cholesky_decomp(A, Nx, Ny)

        sz = A.size()

        # print("A")
        # for i in range(sz):
        #     for j in range(sz):
        #         v = A.get(i, j)
        #         # if x == 0:
        #         #     x = " "
        #         #     print(f" {x:6s} ", end="")
        #         # else:
        #         #     print(f" {x:+.3f} ", end="")
        #         if v == 0:
        #             print(f"{v} & ", end="")
        #         else:
        #             print(f"{v:.2f} & ", end="")
        #     print()

        # print("L")
        # for i in range(sz):
        #     for j in range(sz):
        #         v = A.get(i, j)
        #         # if x == 0:
        #         #     x = " "
        #         #     print(f" {x:6s} ", end="")
        #         # else:
        #         #     print(f" {x:+.3f} ", end="")
        #         if v == 0:
        #             print(f"{v} & ", end="")
        #         else:
        #             print(f"{v:.2f} & ", end="")
        #     print()

        # B = mul_mm(L, transpose(L))

        # print("B")
        # for i in range(sz):
        #     for j in range(sz):
        #         v = A.get(i, j)
        #         # if x == 0:
        #         #     x = " "
        #         #     print(f" {x:6s} ", end="")
        #         # else:
        #         #     print(f" {x:+.3f} ", end="")
        #         if v == 0:
        #             print(f"{v} & ", end="")
        #         else:
        #             print(f"{v:.2f} & ", end="")
        #     print()

        y, nsteps = conjgrad(A, b, x0, eps)

        # print(f"y1")
        # for v in y:
        #     print(f"{v:.2f},")

        d = sub_vv(x, y)
        # f = math.sqrt( mul_vv(d, mul_mv(A, d)) / mul_vv(x, mul_mv(A, x)) )

        d = math.sqrt( mul_vv(d, d) )

        print(f"nsteps = {nsteps}")
        print(f"{d:.2e} {eps:.2e}")

        y, nsteps = conjgrad(A, b, x0, eps, L=L)
        # print(f"y2")
        # for v in y:
        #     print(f"{v:.2f},")

        d = sub_vv(x, y)
        # f = math.sqrt( mul_vv(d, mul_mv(A, d)) / mul_vv(x, mul_mv(A, x)) )

        d = math.sqrt( mul_vv(d, d) )

        print(f"nsteps = {nsteps}")
        print(f"{d:.2e} {eps:.2e}")


        # self.assertLogs(f"nsteps = {nsteps}", level="INFO")
        # self.assertTrue(d < eps)

    def test_method(self):
        Ns = [10, 50, 100, 1000]
        Ns = [5]

        for N in Ns:
            self._func(N)

if __name__ == "__main__":
    unittest.main()