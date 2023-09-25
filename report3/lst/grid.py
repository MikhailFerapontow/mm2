from typing import Tuple, Callable


def get_x(a: float, b: float, Nx: int) -> Tuple[Callable[[int], float], Callable[[int], float]]:
    hx = (b - a) / Nx

    def inner1(i: int) -> float:
        """returns x_{i}"""
        if i < 0 or i > Nx:
            raise KeyError()

        return a + i * hx

    def inner2(i: int) -> float:
        """returns x_{i+1/2}"""
        if i < 0 or i >= Nx:
            raise KeyError()

        return a + (i + 0.5) * hx

    return (inner1, inner2)


def get_y(c: float, d: float, Ny: int) -> Tuple[Callable[[int], float], Callable[[int], float]]:
    hy = (d - c) / Ny

    def inner1(j: int) -> float:
        """returns y_{j}"""
        if j < 0 or j > Ny:
            raise KeyError()

        return c + j * hy

    def inner2(j: int) -> float:
        """returns y_{j+1/2}"""
        if j < 0 or j >= Ny:
            raise KeyError()

        return c + (j + 0.5) * hy

    return (inner1, inner2)
