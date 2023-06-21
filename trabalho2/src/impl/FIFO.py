from typing import List
from src.lib.Queue import Queue


def fifo(in_: List[str]) -> int:
    """
    @param  int in_ lista de paginas referenciadas

    @return int numero de pagefaults
    """

    faults = 0
    q = Queue()

    for page in in_:
        if page not in q.getItems():
            if (not q.isFull) or q.isEmpty:
                q.enqueue(page)
            else:
                q.dequeue()
                q.enqueue(page)
            faults += 1

    return faults
