import numpy as np

# Day 1 Advent of Code
with open("input.txt") as f:
    arrays = np.array(
        [
            [int(x) for x in line.split()]
            for line in f
        ]
    )

difference = np.sum(
    np.abs(
        np.sort(arrays[:, 0]) - np.sort(arrays[:, 1])
    )
)

similarity = np.sum(
    arrays[:, 0] *
    np.bincount(arrays[:, 1])[arrays[:, 0]]
)

print(f"The answer to part 1 is {difference}")
print(f"The answer to part 2 is {similarity}")
