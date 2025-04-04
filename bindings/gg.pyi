from typing import Any, Tuple

class Entity:
    id: str
    def add(self, component: Any) -> None: ...

class Game:
    def create_entity(self) -> Entity: ...

class Sprite:
    def __init__(self, id: str, rect: Tuple[int, int, int, int]) -> None: ...
    id: str
    rect: Tuple[int, int, int, int]

__all__ = ["Entity", "Game", "Sprite"]
