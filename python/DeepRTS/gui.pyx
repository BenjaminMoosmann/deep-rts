import math

import cv2

import numpy as np


cimport numpy as np

import os
from pyDeepRTS.Constants import Unit, Direction, Tile


dir_path = os.path.dirname(os.path.realpath(__file__))

cdef class Ttile:
    cdef gui;
    cdef tile_id;

    def __init__(self, gui, tile_id):
        self.gui = gui
        self.tile_id = tile_id


cdef class Sprite:
    cdef gui;
    cdef sprite;
    cdef states;
    cdef iterator;
    cdef state;



    def __init__(self, gui, sprite, directions):
        self.gui = gui
        self.sprite = sprite
        self.states = {
            direction: [] for direction in directions
        }
        self.state = Direction.Down
        self.iterator = 0

        print(self.states)

    cdef load(self, filename):
        pass

    cdef next(self):
        self.iterator += 1

        frames = self.states[self.state]
        if len(frames) == 0:
            raise Exception("No frames !")

        return frames

    cdef set_state(self, state):
        self.iterator = 0
        self.state = state

cdef class SpriteManager:
    cdef gui;
    cdef color_mask;  # Color mask
    cdef sprites;

    def __init__(self, gui):
        self.gui = gui


        self.color_mask = {
            0: (255, 0, 0),  # Player 1
            1: (0, 0, 255),
            2: (0, 255, 0),
            3: (255, 255, 0),
            4: (0, 255, 255),
            5: (255, 0, 255)  # Player 6
        }

        tile_types = [int(getattr(Tile, x)) for x in Tile.__dict__ if x[0].isupper()]
        unit_classes = [x for x in Unit.__dict__ if x[0].isupper()]
        directions = [x for x in Direction.__dict__ if x[0].isupper()]

        tileset_path = os.path.join(os.getcwd(), "assets", "textures", "tiles.png")  # TODO cwd
        tileset = cv2.imread(tileset_path)

        self.tiles = {
            tile_type: self.sub_rect(tileset, tile_type - 1, self.gui.map.tile_width)
            for tile_type in tile_types
        }

        self.sprites = {
            sprite: Sprite(gui=gui, sprite=sprite, directions=directions) for sprite in unit_classes
        }



    cpdef sub_rect(self, tileset, tile_n, tile_size):
        size = tileset.shape
        n_cols = math.floor(size[0] / tile_size)
        n_rows = math.floor(tile_n / n_cols)
        mod_id = tile_n % n_cols

        x_start = (mod_id * tile_size) + mod_id
        y_start = (n_rows * tile_size) + n_rows

        print(x_start, y_start)



cdef class Layer:

    cdef static;
    cdef data;
    cdef gui;
    cdef public canvas;

    def __init__(self, gui, canvas, static=False):
        self.gui = gui
        self.static = static
        self.canvas = canvas

    cpdef render(self):
        if self.static:
            return self.data
        self.build()
        return self.data

    cdef build(self):
        raise NotImplementedError("build is not implemented")

cdef class GroundLayer(Layer):

    def __init__(self, gui, canvas):
        super().__init__(gui, canvas)

    cdef build(self):
        pass

cdef class UnitLayer(Layer):

    def __init__(self, gui, canvas):
        super().__init__(gui, canvas)

    cdef build(self):
        pass



cdef class ResourceLayer(Layer):

    def __init__(self, gui, canvas):
        super().__init__(gui, canvas)

    cdef build(self):
        pass



cdef class GUI:

    cdef game;
    cdef tilemap;
    cdef map;
    cdef tiles;
    cdef units;
    cdef layers;

    cdef tilemap_size;
    cdef tile_width, tile_height;
    cdef tilemap_render_size;
    cdef window_size;
    cdef sprite_manager;

    cdef layer_ground, layer_unit;

    def __init__(self, game):
        self.game = game
        self.tilemap = self.game.tilemap
        self.map = self.game.map

        self.tiles = self.tilemap.tiles
        self.units = self.game.units

        # SpriteManager
        self.sprite_manager = SpriteManager(gui=self)

        # Size of the map. typically 10x10, 15x15 etc
        self.tilemap_size = (self.map.map_width, self.map.map_height)

        # Size of a tile, typically 32x32
        self.tile_width, self.tile_height = self.map.tile_width, self.map.tile_height

        # Net size of the canvas (map * tile size)
        canvas_size = (self.map.map_width * self.map.tile_width, self.map.map_height * self.map.tile_height)

        # Create canvas
        canvas = np.zeros(shape=canvas_size + (3, ))

        self.layer_ground = GroundLayer(gui=self, canvas=canvas[0])
        self.layer_ground = ResourceLayer(gui=self, canvas=canvas[1])
        self.layer_unit = UnitLayer(gui=self, canvas=canvas[2])


        self.layers = [self.layer_ground, self.layer_unit]



    cpdef render(self):

        for layer in self.layers:
            layer.render()

    cpdef view(self):
        pass

    cpdef set_caption(self, caption):
        pass
