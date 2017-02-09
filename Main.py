# https://www.spriters-resource.com/pc_computer/warcraft2/sheet/29501/
from game.WarC2 import Game
from game.util import log
from game.ParallellWorker import ParallellWorker
from web.Server import WebServer

if __name__ == "__main__":
    logger = log.setup_custom_logger('root')

    LOAD_SAVED_GAME = True

    if LOAD_SAVED_GAME:

        game = Game.load(fromfile=True)
        game.parallell_worker = ParallellWorker()

    else:

        select_map = "simple"
        select_players = 2
        game = Game.start(
            map_name=select_map,
            players=select_players,
            ParallellWorker=ParallellWorker
        )

    # Webserver'
    webserver = WebServer(game)
    webserver.daemon = True
    webserver.start()

    # Start loop
    game.loop()

    print("Player %s won the game!" % game.winner)
