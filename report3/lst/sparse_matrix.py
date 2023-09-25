from typing import Tuple, List
from abc import ABC, abstractmethod
import numpy as np


class SparseMatrix(ABC):
    @abstractmethod
    def get(self, i: int, j: int=None) -> float:
        pass

    @abstractmethod
    def size(self) -> int:
        pass

    @abstractmethod
    def is_symmetric() -> bool:
        pass


class SparseMatrixCOO(SparseMatrix):
    def __init__(self, symmetric=False) -> None:
        self.symmetric = symmetric
        self.row = []
        self.col = []
        self.data = []

    def get(self, i: int, j: int=None) -> float:
        # self._validate_index(i, j)

        if j == None:
            return self._get_by_row(i)

        if self.symmetric:
            i, j = self._get_symmetric_index(i, j)

        idx_pairs = zip(self.row, self.col)

        for idx, pair in enumerate(idx_pairs):
            ir, ic = pair

            if ir == i and ic == j:
                return self.data[idx]

        return 0

    def _get_by_row(self, i):
        rez = [(self.col[idx], self.data[idx]) for idx in range(len(self.row)) if self.row[idx] == i]
        return rez

    def set(self, i: int, j: int, x: float) -> None:
        # self._validate_index(i, j)

        if self.symmetric:
            i, j = self._get_symmetric_index(i, j)

        idx_pair = zip(self.row, self.col)

        for idx, pair in enumerate(idx_pair):
            ir, ic = pair

            if ir == i and ic == j:
                if x == 0:
                    self.row.pop(idx)
                    self.col.pop(idx)
                    self.data.pop(idx)
                else:
                    self.data[idx] = x
                return

        if x != 0:
            self._add_value(i, j, x)

    def size(self) -> int:
        max_row = max(self.row) + 1
        max_col = max(self.col) + 1
        return max(max_row, max_col)

    def is_symmetric(self) -> bool:
        return self.symmetric

    def to_symmetric(self):
        m = SparseMatrixCOO(symmetric=True)
        for i, j, d in zip(self.row, self.col, self.data):
            m.set(i, j, d)
        return m

    def to_CSR(self):
        row = np.array(self.row)
        col = np.array(self.col)
        data = np.array(self.data)

        permutation = sorted(range( len(self.row) ), key=lambda idx: row[idx])

        row = row[permutation]
        col = col[permutation]
        data= data[permutation]

        new_row = []

        for r in np.unique(row):
            index = row == r
            new_row.append( row.tolist().index(r) )

            col_per_row = col[index]
            data_per_row = data[index]

            permutation = sorted(range( len(col_per_row) ), key=lambda idx: col_per_row[idx])

            col_per_row = col_per_row[permutation]
            data_per_row = data_per_row[permutation]

            col[index] = col_per_row
            data[index] = data_per_row

        row = np.array(new_row)

        return SparseMatrixCSR(row, col, data, symmetric=self.symmetric)

    def _add_value(self, i: int, j: int, x: float) -> None:
        self.row.append(i)
        self.col.append(j)
        self.data.append(x)

    def _validate_index(self, i: int, j: int) -> None:
        if i < 0 or j < 0:
            raise KeyError()

    def _get_symmetric_index(self, i: int, j: int) -> Tuple[int, int]:
        return (j, i) if j > i else (i, j)


class SparseMatrixCSR(SparseMatrix):
    def __init__(self, row: np.ndarray, col: np.ndarray, data: np.ndarray, symmetric=False) -> None:
        self.symmetric = symmetric
        self.row = row
        self.col = col
        self.data = data

    def get(self, i: int, j: int=None) -> float:
        # self._validate_index(i, j)

        if j == None:
            return self._get_by_row(i)

        if self.symmetric:
            i, j = self._get_symmetric_index(i, j)

        sz = self.size()

        ic1 = self.row[i]
        ic2 = None if i + 1 == sz else self.row[i + 1]

        try:
            idx = ic1 + self.col[ic1:ic2].tolist().index(j)
        except ValueError:
            return 0

        return self.data[idx]

    def _get_by_row(self, i):
        sz = self.size()

        ic1 = self.row[i]
        ic2 = None if i + 1 == sz else self.row[i + 1]

        col = self.col[ic1:ic2].tolist()
        data = self.data[ic1:ic2].tolist()

        return [(j, d) for j, d in zip(col, data)]

    def size(self) -> int:
        return self.col.max() + 1

    def is_symmetric(self) -> bool:
        return self.symmetric

    def _validate_index(self, i: int, j: int) -> None:
        sz = self.size()
        if i < 0 or i > sz:
            raise KeyError()
        if j < 0 or j > sz:
            raise KeyError()

    def _get_symmetric_index(self, i: int, j: int) -> Tuple[int, int]:
        return (j, i) if j > i else (i, j)