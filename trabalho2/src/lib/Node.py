from dataclasses import dataclass, field


@dataclass
class Node:
    page: str
    prev: "Node" = field(default=None)
    next: "Node" = field(default=None)
