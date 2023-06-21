from src.lib.constants import MAX_FRAMES


class SecondChanceSpecializedQueue:
    def __init__(self):
        self.__items = []
        self.__referenced_list = []

    def enqueue(self, item):
        self.__items.insert(0, item)
        self.__referenced_list.insert(0, True)

    def dequeue(self):
        self.__referenced_list.pop()
        self.__items.pop()

    def getItems(self):
        return self.__items

    def giveSecondChance(self, referenced_page):
        while True:
            if self.__isFirstItemReferenced():
                self.__sendToEnd()
            else:
                self.dequeue()
                self.enqueue(referenced_page)
                return False

    def setIsReferenced(self, item):
        index = self.__items.index(item)
        self.__referenced_list[index] = True

    def __getFirstItem(self):
        return self.__items[self.currentSize - 1]

    def __isFirstItemReferenced(self):
        return self.__referenced_list[self.currentSize - 1]

    def __sendToEnd(self):
        item = self.__getFirstItem()

        self.dequeue()
        self.__items.insert(0, item)
        self.__referenced_list.insert(0, False)

    @property
    def currentSize(self) -> int:
        return len(self.__items)

    @property
    def isEmpty(self) -> bool:
        return self.currentSize == 0

    @property
    def maxCapacity(self) -> int:
        return MAX_FRAMES

    @property
    def isFull(self) -> bool:
        return self.currentSize == self.maxCapacity
