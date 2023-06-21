from typing import List
import random


MAX_SIZE = 64


def nru(in_: List[str]) -> int:
    """
    @param  int in_ lista de paginas referenciadas

    @return int numero de pagefaults
    """
    tbl = dict()
    classes = dict()
    faults = 0
    referencedPagesCnt = 0
    for i in range(0, 4):
        classes[f"cls{i}"] = []

    def include(page: str):
        tbl[page] = {"r": True, "m": random.choice([False, True])}

    def clearLowestClassses():
        for p in tbl.keys():
            r = tbl[p].get("r")
            m = tbl[p].get("m")
            if not r and not m:
                classes["cls0"].append(p)
            elif not r and m:
                classes["cls1"].append(p)
            elif r and not m:
                classes["cls2"].append(p)
            else:
                classes["cls3"].append(p)

        i: str
        if len(classes["cls0"]) > 0:
            i = random.choice(classes["cls0"])
        elif len(classes["cls1"]) != 0:
            i = random.choice(classes["cls1"])
        elif len(classes["cls2"] != 0):
            i = random.choice(classes["cls2"])
        elif len(classes["cls3"] != 0):
            i = random.choice(classes["cls3"])

        tbl.pop(i)

    def reset():
        for i in classes.keys():
            classes[i] = []

    def notInTable(page: str):
        nonlocal faults
        if len(tbl) == 0 or len(tbl) < MAX_SIZE:
            include(page)
            faults += 1
        elif len(tbl) == MAX_SIZE:
            clearLowestClassses()
            include(p)
            reset()
            faults += 1

    for page in in_:
        if page not in tbl:
            notInTable(page)
        else:
            tbl[page]["r"] = True
        referencedPagesCnt += 1
        if referencedPagesCnt == 3:
            for p in tbl:
                tbl[p].update(r=0)
            referencedPagesCnt = 0

    return faults
