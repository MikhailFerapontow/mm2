from sympy import symbols, Float, log, cos, sin
from utils import *

import math

from model import Model
from linalg import *
from grid import *

a = 0
b = 1
c = 0
d = 2

chi2 = 2
chi3 = 3

x, y = symbols("x y")

def print_matrix(m):
    dummy = ""

    sz = m.size()

    print(f"{dummy:3s}", end=" ")
    for i in range(sz):
        print(f"{i:7d}", end=" ")
    print()

    for i in range(sz):
        print(f"{i:3d}", end=" ")
        for j in range(sz):
            x = m.get(i, j)
            if x == 0:
                print(f" {0:+7.2f}", end=" ")
            else:
                print(f" {m.get(i, j):+7.2f}", end=" ")
        print()

def print_matrix2(m):
    dummy = ""

    sz = m.size()

    # print(f"{dummy:3s}", end=" ")
    for i in range(sz):
        for j in range(sz):
            x = m.get(i, j)
            if x == 0:
                pass
            else:
                print("\\fill[color=blue!60] (", i, "," , sz - j, ")" , "rectangle (", j,",", sz - i,");")
        print()

def print_vector(label, v):
    print(f"{label}: ", end="")

    for x in v:
        print(f"{x:+.5f}", end=" ")

    print()


test_cases = [
    # ( (x + y + 1)**2, (x + y + 1)**3, Float(1) * x**2 ),
    # ( (x + y + 1), (x + y + 1), (2 * x + 3 * y + 1) ),
    ( (x + y + 1)**2, (x + y + 1)**2, (2 * x + 3 * y + 1) * x**2 ),
    # ( (x + y + 1)**3, (x + y + 1)**3, (2 * x + 3 * y + 1) ),
    # ( Float(1), Float(1), (2 * x + 3 * y + 1)**2 ),
    # ( (x + y + 1), (x + y + 1), (2 * x + 3 * y + 1)**2 ),
    # ( (x + y + 1), (x + y + 1), (2 * x + 3 * y + 1)**3 * x**2),
    # ( (cos(x * y) + 2), (sin(x) * sin(y) + 2), (x * log(y + 1)) ),
]

fmt = "{:>2s}, {:>3s}, {:>3s}, {:>4s}, {:>8s}, {:>8s}, {:>8s}, {:>4s}, {:>8s}, {:>8s}, {:>8s}"
header = fmt.format(
    "no", "Nx", "Ny",
    "n1", "delta11", "delta12", "delta13",
    "n2", "delta21", "delta22", "delta23"
)
print(header)

for test_num, test_case in enumerate(test_cases):

    k1, k2, u = test_case

    g2 = get_g2(b, chi2, k1, u)
    g3 = get_g3(c, chi3, k2, u)
    g4 = get_g4(d, u)

    f = get_f(u, k1, k2)
    k1 = get_k1(k1)
    k2 = get_k2(k2)
    u = get_u(u)

    mod = Model(a, b, c, d, [k1, k2], f, [chi2, chi3], [g2, g3, g4])

    sizes = [
        # (2, 2),
        (4, 4),
        # (8, 8),
        # (16, 16),
        # (32, 32),
        # (64, 64),
    ]

    for Nx, Ny in sizes:
        A, g, L = mod.init_data(Nx, Ny)
        sz = A.size()

        # for i in g:
        #     print("g =", i)

        x1, _ = get_x(a, b, Nx)
        y1, _ = get_y(c, d, Ny)

        x0 = [0] * sz

        x = []
        for j in range(Ny + 1):
            for i in range(Nx + 1):
                x.append(u(x1(i), y1(j)))

        print_matrix2(A)

        # y, n_steps_1 = conjgrad(A, g, x0, eps=1e-12)

        # # print_vector("x", x)
        # # print_vector("y", y)
        # # print_vector("g", g)
        # # print_vector("Ay", mul_mv(A, y))
        # # print_vector("Ax", mul_mv(A, x))

        # delta = sub_vv(x, y)

        # delta_11 = sum( [abs(i) for i in delta] ) / sum( [abs(i) for i in x] )
        # delta_12 = math.sqrt( mul_vv(delta, delta) / mul_vv(x, x) )
        # delta_13 = abs( max(delta, key=lambda x: abs(x)) / max(x, key=lambda x: abs(x)) )

        # y, n_steps_2 = conjgrad(A, g, x0, eps=1e-8, L=L)

        # delta = sub_vv(x, y)

        # delta_21 = sum( [abs(i) for i in delta] ) / sum( [abs(i) for i in x] )
        # delta_22 = math.sqrt( mul_vv(delta, delta) / mul_vv(x, x) )
        # delta_23 = abs( max(delta, key=lambda x: abs(x)) / max(x, key=lambda x: abs(x)) )

        # fmt = "{:2d}, {:3d}, {:3d}, {:4d}, {:8.5e}, {:8.5e}, {:8.5e}, {:4d}, {:8.5e}, {:8.5e}, {:8.5e}"
        # record = fmt.format(
        #     test_num, Nx, Ny,
        #     n_steps_1, float(delta_11), float(delta_12), float(delta_13),
        #     n_steps_2, float(delta_21), float(delta_22), float(delta_23),
        # )
        # # print(record, flush=True)