import pandas as pd


df = pd.read_csv("rez3.txt")

def func(no):
    x = df[df["no"] == no]

    print("\\begin{table}[H]")
    print("\t\\centering")
    print("\t\\begin{tabular}{*6c}")
    print("\t\t\\toprule")
    print("\t\t$N_x$ & $N_y$ & $n$ & $\\delta_1$ & $\\delta_2$ & $\\delta_3$ \\\\")
    print("\t\t\\midrule")

    for row in x.values:
        Nx = int(row[1])
        Ny = int(row[2])

        n = int(row[3])
        d1 = row[4]
        d2 = row[5]
        d3 = row[6]

        print(f"\t\t{Nx} & {Ny} & {n} & {d1:.2e} & {d2:.2e} & {d3:.2e} \\\\")

    print("\t\t\\bottomrule")
    print("\t\\end{tabular}")
    print("\t\\caption{Тест №" + str(no + 1) + " (явный метод)}")
    print("\\end{table}")

    print("\\begin{table}[H]")
    print("\t\\centering")
    print("\t\\begin{tabular}{*6c}")
    print("\t\t\\toprule")
    print("\t\t$N_x$ & $N_y$ & $n$ & $\\delta_1$ & $\\delta_2$ & $\\delta_3$ \\\\")
    print("\t\t\\midrule")


    for row in x.values:
        Nx = int(row[1])
        Ny = int(row[2])

        n = int(row[7])
        d1 = row[8]
        d2 = row[9]
        d3 = row[10]

        print(f"\t\t{Nx} & {Ny} & {n} & {d1:.2e} & {d2:.2e} & {d3:.2e} \\\\")

    print("\t\t\\bottomrule")
    print("\t\\end{tabular}")
    print("\t\\caption{Тест №" + str(no + 1) + " (неявный метод)}")
    print("\\end{table}")

    print()

for i in range(8):
    func(i)