from gg import Game, Sprite, Transform


def setup(g: Game) -> None:
    print("Hello from python")
    s = Sprite(id="tank", rect=(10, 10, 10, 10), scale=(3, 3))
    t = Transform(x=10.0, y=10.0)

    tank = g.create_entity()
    tank.add(s)
    tank.add(t)


def update(delta: float) -> None:
    print(delta)
