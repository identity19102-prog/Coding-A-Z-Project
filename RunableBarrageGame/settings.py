import pygame

# Window
WIDTH, HEIGHT = 600, 800

# Colors
WHITE = (255,255,255)
BLACK = (0,0,0)

# Player
PLAYER_SIZE = 20
PLAYER_SPEED = 9
PLAYER_LIVES = 3

# Bullet
BULLET_SIZE = 20
BULLET_SPEED = 5

# Fonts
pygame.font.init()
FONT_SCORE = pygame.font.SysFont("PxPlus Rainbow100 re 66", 24)
FONT_PLAYER = pygame.font.SysFont("PxPlus Rainbow100 re 66", 32)
FONT_BULLET = pygame.font.SysFont("PxPlus Rainbow100 re 66", 32)
FONT_TITLE = pygame.font.SysFont("PxPlus Rainbow100 re 66", 36)
