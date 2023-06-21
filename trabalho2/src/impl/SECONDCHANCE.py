from typing import List
from src.lib.SecondChanceSpecializedQueue import SecondChanceSpecializedQueue


def secondchance(in_: List[str]) -> int:
    """
    @param  int in_ lista de paginas referenciadas

    @return int numero de pagefaults
    """

    faults = 0
    q = SecondChanceSpecializedQueue()

    for page in in_:
        if page not in q.getItems():
            if q.isEmpty or (not q.isFull):
                q.enqueue(page)
                faults += 1
            else:
                q.giveSecondChance(page)
                faults += 1
        else:
            q.setIsReferenced(page)

    return faults
