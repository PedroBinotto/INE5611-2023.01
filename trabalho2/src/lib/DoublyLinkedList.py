from src.lib.Node import Node
from src.lib.constants import MAX_FRAMES
from src.lib.PageFaultException import PageFaultException


class DoublyLinkedList:
    def __init__(self):
        self.__head: Node = None
        self.__tail: Node = None
        self.__curr: Node = None

    def __repr__(self):
        return str(self.__head)

    def __goToHead(self):
        self.__curr = self.__head
        return self.__curr

    def __goToTail(self):
        if self.__head is None:
            return None

        self.__curr = self.__tail
        return self.__curr

    def getCurrent(self):
        return self.__curr

    def push(self, key: str, checkPageFault=True):
        if self.currentSize < self.maxCapacity:
            if self.find(key, True):
                self.getItem(key)
                self.popCurrent()
                self.push(key, False)
                return
            else:
                new_item = Node(key)
                first = self.__goToHead()

                if first is not None:
                    first.prev = new_item
                    new_item.next = first
                    first = new_item
                else:
                    first = new_item
                    self.__tail = first

                self.__head = new_item
                self.__curr = new_item
                if checkPageFault:
                    raise PageFaultException
        else:
            if self.find(key, True):
                self.getItem(key)
                self.popCurrent()
                self.push(key, False)
                return
            else:
                self.popLast()
                self.push(key, False)
                if checkPageFault:
                    raise PageFaultException

    def getItem(self, key: str) -> Node:
        self.__goToHead()
        while self.__curr is not None:
            if self.__curr.page == key:
                return self.__curr
            else:
                self.__curr = self.__curr.next

    def popCurrent(self):
        if self.__head.next is None:
            self.popFirst()
        elif self.__curr.next is None:
            self.popLast()
        elif self.__curr == self.__head:
            self.popFirst()
        else:
            self.__curr.prev.next = self.__curr.next
            self.__curr.next.prev = self.__curr.prev
            self.__curr = self.__curr.prev

    def popFirst(self):
        if self.__head is None:
            raise Exception("Empty list")
        else:
            self.__head = self.__head.next
            self.__head.__prev = None
            self.__curr = self.__head

    def popLast(self):
        self.__goToTail()
        if self.__goToTail() is not None:
            self.__curr = self.__curr.prev
            self.__curr.next = None
            self.__tail = self.__curr
        else:
            raise Exception("Empty list")

    def find(self, key: str, resetPosition=False):
        old_atual = self.__curr

        if self.__curr is None:
            return False

        self.__goToHead()
        while self.__curr.page != key and self.__curr.next != None:
            self.__curr = self.__curr.next

        if self.__curr.page == key:
            if resetPosition == True:
                self.__curr = old_atual
            return True
        else:
            if resetPosition == True:
                self.__curr = old_atual
            return False

    def print(self):
        pointer = self.__head

        while pointer != None:
            print(pointer.page)
            pointer = pointer.next

    @property
    def currentSize(self):
        size = 0
        pointer = self.__head
        while pointer != None:
            pointer = pointer.next
            size += 1
        return size

    @property
    def maxCapacity(self):
        return MAX_FRAMES
