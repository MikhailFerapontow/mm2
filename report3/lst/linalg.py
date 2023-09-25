import math
from typing import List
from sparse_matrix import *


def is_symmetric(m: SparseMatrix):
    sz = m.size()

    for i in range(sz):
        for j in range(sz):
            if m.get(i, j) != m.get(j, i):
                return False

    return True


def add_vv(v1: List[float], v2: List[float]) -> List[float]:
    sz = len(v1)
    rez = [0] * sz

    for i in range(sz):
        rez[i] = v1[i] + v2[i]

    return rez

def mul_sv(a: float, v: List[float]) -> List[float]:
    sz = len(v)
    rez = [0] * sz

    for i in range(sz):
        rez[i] = v[i] * a

    return rez

def sub_vv(v1: List[float], v2: List[float]) -> List[float]:
    return add_vv(v1, mul_sv(-1, v2))

def mul_vv(v1: List[float], v2: List[float]) -> float:
    sz = len(v1)
    rez = 0

    for i in range(sz):
        rez += v1[i] * v2[i]

    return rez

def mul_mv(m: SparseMatrix, v: List[float]) -> List[float]:
    sz = len(v)
    rez = [0] * sz

    for i in range(sz):
        for j, d in m.get(i):
            if i == j:
                continue
            rez[i] += d * v[j]
            if m.is_symmetric():
                rez[j] += d * v[i]

    for i in range(sz):
        rez[i] += m.get(i, i) * v[i]

    return rez

def mul_mm(m1: SparseMatrix, m2: SparseMatrix) -> SparseMatrixCOO:
    sz = m1.size()
    rez = SparseMatrixCOO()

    for i in range(sz):
        for j in range(sz):
            acc = 0
            for k in range(sz):
                acc += m1.get(i, k) * m2.get(k, j)

            rez.set(i, j, acc)

    return rez

def transpose(m: SparseMatrix) -> SparseMatrixCOO:
    sz = m.size()
    rez = SparseMatrixCOO()

    for i in range(sz):
        for j, d in m.get(i):
            rez.set(j, i, d)

    return rez

def copy_v(v: List[float]) -> List[float]:
    sz = len(v)
    rez = [0] * sz

    for i in range(sz):
        rez[i] = v[i]

    return rez

def _cholesky_solve(L: SparseMatrix, r: List[float]) -> List[float]:
    sz = len(r)

    LT = transpose(L)

    z = [0] * sz
    for i in range(sz):
        acc = r[i]
        for j, d in L.get(i):
            if j < i:
                acc -= d * z[j]

        z[i] = acc / L.get(i, i)

    w = [0] * sz
    for i in range(sz - 1, -1, -1):
        acc = z[i]
        for j, d in LT.get(i):
            if j > i:
                acc -= d * w[j]

        w[i] = acc / LT.get(i, i)

    return w

def conjgrad(A: SparseMatrix, b: List[float], x: List[float],
             eps: float, maxiter: int=10000, L: SparseMatrix=None) -> List[float]:
    nsteps = 0

    if L == None:
        r = sub_vv(b, mul_mv(A, x))
        p = copy_v(r)
        gamma = math.sqrt( mul_vv(b, b) )

        rsold = mul_vv(r, r)

        while nsteps < maxiter:
            nsteps += 1

            Ap = mul_mv(A, p)
            alpha = rsold / mul_vv(p, Ap)

            x = add_vv(x, mul_sv(alpha, p))
            r = sub_vv(r, mul_sv(alpha, Ap))

            rsnew = mul_vv(r, r)
            if math.sqrt(rsnew) < gamma * eps:
                break

            p = add_vv(r, mul_sv(rsnew / rsold, p))
            rsold = rsnew
    else:
        r = sub_vv(b, mul_mv(A, x))
        w = _cholesky_solve(L, r)
        p = w
        g = _cholesky_solve(L, b)
        gamma = math.sqrt( mul_vv(g, b) )

        rsold = mul_vv(w, r)

        while nsteps < maxiter:
            nsteps += 1

            Ap = mul_mv(A, p)
            alpha = rsold / mul_vv(p, Ap)

            x = add_vv(x, mul_sv(alpha, p))
            r = sub_vv(r, mul_sv(alpha, Ap))
            w = _cholesky_solve(L, r)

            rsnew = mul_vv(w, r)
            if math.sqrt(rsnew) < gamma * eps:
                break

            p = add_vv(w, mul_sv(rsnew / rsold, p))
            rsold = rsnew

    return (x, nsteps)