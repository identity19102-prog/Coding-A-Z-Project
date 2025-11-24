import random
import pygame
from settings import *

class Bullet:
    def __init__(self):
        self.x = random.randint(0, WIDTH - BULLET_SIZE)
        self.y = -BULLET_SIZE
        self.color = (
            random.randint(25,255),
            random.randint(25,255),
            random.randint(25,255)
        )

    def move(self, speed):
        self.y += speed

    def draw(self, screen):
        text = FONT_BULLET.render("☻", True, self.color)
        screen.blit(text, (self.x, self.y))

    def rect(self):
        return pygame.Rect(self.x, self.y, BULLET_SIZE, BULLET_SIZE)
