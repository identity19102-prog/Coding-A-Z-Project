import pygame
import sys
from settings import *
from utils import draw_text

def start_screen(screen):
    screen.fill(BLACK)
    draw_text(screen, "RUNABLE BARRAGE GAME", FONT_TITLE, WHITE, WIDTH//2, HEIGHT//2 - 50)
    draw_text(screen, "Press Any Key to Start", FONT_TITLE, WHITE, WIDTH//2, HEIGHT//2 + 50)
    pygame.display.flip()

    waiting = True
    while waiting:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit(); sys.exit()
            if event.type == pygame.KEYDOWN:
                waiting = False


def game_over_screen(screen, score):
    screen.fill(BLACK)
    draw_text(screen, "GAME OVER", FONT_TITLE, WHITE, WIDTH//2, HEIGHT//2 - 50)
    draw_text(screen, f"Score: {score}", FONT_TITLE, WHITE, WIDTH//2, HEIGHT//2)
    draw_text(screen, "Press Any Key to Exit", FONT_TITLE, WHITE, WIDTH//2, HEIGHT//2 + 50)
    pygame.display.flip()

    waiting = True
    while waiting:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit(); sys.exit()
            if event.type == pygame.KEYDOWN:
                pygame.quit(); sys.exit()


def game_clear_screen(screen, score):
    screen.fill(BLACK)
    draw_text(screen, "!!! GAME CLEAR !!!", FONT_TITLE, WHITE, WIDTH//2, HEIGHT//2 - 50)
    draw_text(screen, f"Final Score: {score}", FONT_TITLE, WHITE, WIDTH//2, HEIGHT//2)
    draw_text(screen, "Press Any Key to Exit", FONT_TITLE, WHITE, WIDTH//2, HEIGHT//2 + 50)
    pygame.display.flip()

    waiting = True
    while waiting:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit(); sys.exit()
            if event.type == pygame.KEYDOWN:
                pygame.quit(); sys.exit()
