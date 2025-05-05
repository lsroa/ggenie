from gg import Game, Sprite, Transform, Animation


def setup(g: Game) -> None:
    print("Hello from python")
    s = Sprite(id="tank", rect=(0, 16, 16, 16), scale=(3, 3))
    t = Transform(x=0.0, y=0.0)
    a = Animation(2, 4)

    tank = g.create_entity()
    tank.add(s).add(t).add(a)


def update(delta: float) -> None:
    pass
