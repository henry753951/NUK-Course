import numpy as np
from tabulate import tabulate


def partition(S, p):
    S1 = []
    S2 = []
    S3 = []

    for num in S:
        if num < p:
            S1.append(num)
        elif num == p:
            S2.append(num)
        else:
            S3.append(num)

    return S1, S2, S3


def print_subsets(subsets):
    subset_table = []
    for subset in subsets:
        subset_row = [str(num) for num in subset]
        subset_table.append(subset_row)

    print(tabulate(subset_table, tablefmt="grid"))


def prune_and_search(S, k):
    n = len(S)

    print("\n\n\n")
    # Base case
    if n <= 5:
        S.sort()
        return S[k - 1]

    # 拆分成n/5個子集合
    subsets = [S[i : i + 5] for i in range(0, n, 5)]
    if len(subsets[-1]) < 5:
        subsets[-1] += [float('inf')] * (5 - len(subsets[-1]))
    print("Subsets:")
    print_subsets(subsets)
    
    print("\n\n\n ## Sort each subset")
    # Sort each subset
    subsets = [sorted(subset) for subset in subsets]
    print("Sort Subsets:")
    print_subsets(subsets)

    print("\n\n\n ## 每個subset的中位數")
    # 每個subset的中位數
    medians = [np.median(subset) for subset in subsets]
    print("Medians:")
    print(" ".join([str(num) for num in medians]))
    print("sorted Medians:")
    print(" ".join([F"{num}" for num in sorted(medians)]))

    print("\n\n\n ## 找出中位數的中位數") 
    # 找出中位數的中位數
    p = np.median([m for m in medians if m != float('inf')])
    print(" ".join([F"[{num}]" if num == p else F"{num}" for num in sorted(medians)]))


    print("\n\n\n ## 拆分成三個子集合")
    # 拆分成三個子集合
    S1, S2, S3 = partition(S, p)
    print("S1:")
    print(" ".join([str(num) for num in S1]))
    print("S2:")
    print(" ".join([str(num) for num in S2]))
    print("S3:")
    print(" ".join([str(num) for num in S3]))
    print("Subsets:")
    print_subsets(subsets)

    if len(S1) >= k:
        return prune_and_search(S1, k)
    elif len(S1) + len(S2) >= k:
        return p
    else:
        k_prime = k - len(S1) - len(S2)
        return prune_and_search(S3, k_prime)


S = [
    1,
    18,
    27,
    34,
    20,
    12,
    30,
    2,
    19,
    6,
    29,
    10,
    11,
    28,
    23,
    21,
    25,
    22,
    4,
    35,
    5,
    31,
    7,
    24,
    13,
    26,
    9,
    16,
    3,
    33,
    15,
    17,
    8,
    32,
    14,
]
k = 3

kth_smallest = prune_and_search(S, k)
print(f"The {k}th smallest element is: {kth_smallest}")
