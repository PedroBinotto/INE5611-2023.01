from typing import List
from src.lib.DoublyLinkedList import DoublyLinkedList
from src.lib.PageFaultException import PageFaultException


def lru(in_: List[str]) -> int:
    """
    @param  int in_ lista de paginas referenciadas

    @return int numero de pagefaults
    """

    faults = 0
    l = DoublyLinkedList()

    for page in in_:
        try:
            l.push(page)
        except PageFaultException:
            faults += 1

    return faults
