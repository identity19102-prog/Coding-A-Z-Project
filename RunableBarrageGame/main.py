import datetime

import pygame
import sys
import random
from settings import *
from utils import draw_text
from screens import start_screen, game_over_screen, game_clear_screen
from player import Player
from bullet import Bullet

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

spawn_event = pygame.USEREVENT + 1
spawn_delay = 500
pygame.time.set_timer(spawn_event, spawn_delay)

player = Player()
bullets = []

items = []
item_size = 20
item_speed = 4

score = 0
game_time = 100
bullet_speed = 5

start_screen(screen)

running = True
while running:
    dt = clock.tick(60) / 1000
    screen.fill(BLACK)

    # === 난이도 조절 (10점마다 상승) ===
    difficulty_level = score // 10  # 0,1,2,3,...

    # === 아이템 스폰 (300점마다) ===
    if score > 0 and score % 300 == 0:

        # 같은 점수에서 중복 생성 방지: spawn_score를 기준으로 체크
        if not any(item[3] == score for item in items):
            item_x = random.randint(0, WIDTH - item_size)
            items.append([item_x, -item_size, [255, 255, 255], score])

    # 밀도(스폰 간격) 감소: 최대 속도는 25ms까지
    new_delay = max(25, 500 - difficulty_level * 50)

    # 총알 속도 증가: 최대 20까지
    new_speed = min(20, 5 + difficulty_level * 2)

    if new_delay != spawn_delay:
        spawn_delay = new_delay
        pygame.time.set_timer(spawn_event, spawn_delay)

    bullet_speed = new_speed



    # === 이벤트 ===
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == spawn_event:
            bullets.append(Bullet())

    # === 입력 ===
    keys = pygame.key.get_pressed()
    player.move(keys)

    # === 총알 ===
    new_bullets = []
    for bullet in bullets:
        bullet.move(bullet_speed)
        bullet.draw(screen)

        if bullet.rect().colliderect(player.rect()):
            if player.invincible <= 0:
                player.lives -= 1
                score -= 1
                player.invincible = 60
        elif bullet.y > HEIGHT:
            score += 1
        else:
            new_bullets.append(bullet)

    bullets = new_bullets

    # === 아이템 업데이트 & 충돌 체크 ===
    new_items = []
    for item in items:
        x, y, color, spawn_score = item

        # 아이템 내려오기
        y += item_speed

        # 색 랜덤 반짝임
        color = [random.randint(150, 255),
                 random.randint(150, 255),
                 random.randint(150, 255)]

        item_rect = pygame.Rect(x, y, item_size, item_size)

        # 충돌
        if player.rect().colliderect(item_rect):
            player.lives += 1
            continue

        # 화면 안에 있는 아이템만 유지
        if y < HEIGHT:
            new_items.append([x, y, color, spawn_score])

    items = new_items

    # === 아이템 그리기 (@) ===
    for x, y, color, spawn_score in items:
        item_text = FONT_SCORE.render("@", True, color)
        screen.blit(item_text, (x, y))

    # === 사망 ===
    if player.lives <= -1:
        now = datetime.datetime.now()
        time_str = now.strftime("%Y-%m-%d %H:%M:%S")

        # 결과 저장
        with open("result.txt", "a") as f:
            f.write("===== RUNABLE BARRAGE GAME RESULT =====\n")
            f.write(f"Time: {time_str}\n")
            f.write(f"Score: {score}\n")
            f.write(f"Remaining Lives: {player.lives}\n")
            f.write(f"Time Survived: {int(100 - game_time)} seconds\n")
            f.write(f"----------------------------------------\n")

        game_over_screen(screen, score)
        running = False

    # === 승리조건 ===
    game_time -= dt
    if game_time <= 0:
        now = datetime.datetime.now()
        time_str = now.strftime("%Y-%m-%d %H:%M:%S")

        # 저장
        with open("result.txt", "a") as f:
            f.write("===== RUNABLE BARRAGE GAME RESULT =====\n")
            f.write(f"Time: {time_str}\n")
            f.write(f"Score: {score}\n")
            f.write(f"Remaining Lives: {player.lives}\n")
            f.write(f"Time Survived: {int(100 - game_time)} seconds\n")
            f.write(f"----------------------------------------\n")

        game_clear_screen(screen, score)
        running = False

    if player.invincible > 0:
        player.invincible -= 1

    # === UI ===
    player.draw(screen)

    score_text = FONT_SCORE.render(str(score), True, WHITE)
    screen.blit(score_text, (50, 10))

    timer_text = FONT_SCORE.render(str(int(game_time)), True, (255,0,0))
    screen.blit(timer_text, (275, 10))

    life_text = FONT_SCORE.render("*" * player.lives, True, (192,0,127))
    screen.blit(life_text, (480, 10))

    pygame.display.flip()

pygame.quit()
