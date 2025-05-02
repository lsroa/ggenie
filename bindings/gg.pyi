from typing import Any

class Entity:
    id: str
    def add(self, component: Any) -> None: ...

class Game:
    def create_entity(self) -> Entity: ...

class Sprite:
    def __init__(self, id: str, rect: tuple[int, int, int, int]) -> None: ...
    id: str
    rect: tuple[int, int, int, int]

class Transform:
    def __init__(self, x: float, y: float) -> None: ...

__all__ = ["Entity", "Game", "Sprite", "Transform"]
