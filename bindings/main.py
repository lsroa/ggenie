from gg import Game, Sprite


def setup() -> None:
    g = Game()
    tank = g.create_entity()
    s = Sprite(id="tank", rect=(10, 10, 10, 10))
    tank.add(s)

    print(s.id)
    print(s.rect)

    print("*********")
    print(f"entity id: {tank.id}")

    g.run()
