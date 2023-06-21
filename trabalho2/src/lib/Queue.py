from src.lib.constants import MAX_FRAMES


class Queue:
    def __init__(self):
        self.items = []

    def enqueue(self, item):
        return self.items.insert(0, item)

    def dequeue(self):
        return self.items.pop()

    def getItems(self):
        return self.items

    @property
    def size(self) -> int:
        return len(self.items)

    @property
    def isEmpty(self) -> bool:
        return self.size == 0

    @property
    def isFull(self) -> bool:
        return self.size == MAX_FRAMES
