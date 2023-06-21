from src.impl.SECONDCHANCE import secondchance
from src.impl.FIFO import fifo
from src.impl.NRU import nru
from src.impl.LRU import lru
from typing import List
from time import time


def parseTestData():
    file = open("./resources/data", "r")
    p: List
    for line in file:
        p = line.split(", ")
    file.close()
    return p


def run(func, *args):
    start = time()
    r = func(*args)
    end = time()
    return r, (end - start)


p = parseTestData()

print("\n- FIFO -")
r0, t0 = run(fifo, p)
print(f"Total page faults: {r0}")
print(f"Total elapsed time: {t0}")

print("\n- SECOND CHANCE -")
r1, t1 = run(secondchance, p)
print(f"Total page faults: {r1}")
print(f"Total elapsed time: {t1}")

print("\n- NRU -")
r2, t2 = run(nru, p)
print(f"Total page faults: {r2}")
print(f"Total elapsed time: {t2}")

print("\n- LRU -")
r3, t3 = run(lru, p)
print(f"Total page faults: {r3}")
print(f"Total elapsed time: {t3}")

print()
