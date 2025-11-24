import pygame
from settings import *

class Player:
    def __init__(self):
        self.x = WIDTH // 2
        self.y = HEIGHT - 100
        self.size = PLAYER_SIZE
        self.speed = PLAYER_SPEED
        self.lives = PLAYER_LIVES
        self.invincible = 0

    def move(self, keys):
        if keys[pygame.K_LEFT] and self.x > 0:
            self.x -= self.speed
        if keys[pygame.K_RIGHT] and self.x < WIDTH - self.size:
            self.x += self.speed
        if keys[pygame.K_UP] and self.y > 0:
            self.y -= self.speed
        if keys[pygame.K_DOWN] and self.y < HEIGHT - self.size:
            self.y += self.speed

    def draw(self, screen):
        text = FONT_PLAYER.render("*", True, (0,255,0))
        screen.blit(text, (self.x, self.y))

    def rect(self):
        return pygame.Rect(self.x, self.y, self.size, self.size)
