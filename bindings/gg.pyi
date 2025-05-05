from typing import Any

class Entity:
    id: str
    def add(self, component: Any) -> Entity: ...

class Game:
    def create_entity(self) -> Entity: ...

class Sprite:
    def __init__(
        self, id: str, rect: tuple[int, int, int, int], scale: tuple[int, int]
    ) -> None: ...
    id: str
    rect: tuple[int, int, int, int]
    scale: tuple[int, int]

class Transform:
    def __init__(self, x: float, y: float) -> None: ...

class Animation:
    total_frames: int
    speed: int
    start_time: float
    current_frame: int
    def __init__(self, total_frames: int, speed: int) -> None: ...

__all__ = ["Entity", "Animation", "Game", "Sprite", "Transform"]
