from typing import Callable
from sympy import Symbol, symbols, simplify, Subs, N, diff


def get_u(u: Symbol) -> Callable[[float, float], float]:
    def inner(x: float, y: float):
        expr = Subs(u, "x", x)
        expr = Subs(expr, "y", y)
        return N(expr)

    return inner

def get_k1(k1: Symbol) -> Callable[[float, float], float]:
    def inner(x: float, y: float):
        expr = Subs(k1, "x", x)
        expr = Subs(expr, "y", y)
        return N(expr)

    return inner

def get_k2(k2: Symbol) -> Callable[[float, float], float]:
    def inner(x: float, y: float):
        expr = Subs(k2, "x", x)
        expr = Subs(expr, "y", y)
        return N(expr)

    return inner

def get_f(u: Symbol, k1: Symbol, k2: Symbol) -> Callable[[float, float], float]:
    x= symbols("x")
    expr1 = x * k1 * diff(u, "x")
    expr2 = k2 * diff(u, "y")
    f = -( (1 / x) * diff(expr1, "x") + diff(expr2, "y") )
    f = simplify(f)

    # print("f =", f)

    def inner(x: float, y: float):
        expr = Subs(f, "x", x)
        expr = Subs(expr, "y", y)
        return N(expr)

    return inner

# def get_g1(a: float, chi1: float, k1: Symbol, u: Symbol) -> Callable[[float, float], float]:
#     g1 = Subs(chi1 * u - k1 * diff(u, "x"), "x", a)
#     def inner(y: float):
#         return N( Subs(g1, "y", y) )

#     return inner

# def get_g2(b: float, u: Symbol) -> Callable[[float, float], float]:
#     g2 = Subs(u, "x", b)
#     def inner(y: float):
#         return N( Subs(g2, "y", y) )

#     return inner

# def get_g3(c: float, chi3: float, k2: Symbol, u: Symbol) -> Callable[[float, float], float]:
#     g3 = Subs(chi3 * u - k2 * diff(u, "y"), "y", c)
#     def inner(x: float):
#         return N( Subs(g3, "x", x) )

#     return inner

# def get_g4(d: float, chi4: float, k2: Symbol, u: Symbol) -> Callable[[float, float], float]:
#     g4 = Subs(chi4 * u + k2 * diff(u, "y"), "y", d)
#     def inner(x: float):
#         return N( Subs(g4, "x", x) )

#     return inner

def get_g2(b: float, chi2: float, k1: Symbol, u: Symbol) -> Callable[[float, float], float]:
    g2 = Subs(chi2 * u + k1 * diff(u, "x"), "x", b)
    def inner(y:float):
        return N( Subs(g2, "y", y))

    return inner

def get_g3(c: float, chi3: float, k2: Symbol, u: Symbol) -> Callable[[float, float], float]:
    g3 = Subs(chi3 * u - k2 * diff(u, "y"), "y", c)
    def inner(x: float):
        return N( Subs(g3, "x", x))

    return inner

def get_g4(d: float, u: Symbol) -> Callable[[float, float], float]:
    g4 = Subs(u, "y", d)
    def inner(x: float):
        return N( Subs(g4, "x", x))

    return inner