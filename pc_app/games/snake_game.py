"""Snake extra, corre en la PC (independiente del snake secreto del pad).
Se puede ejecutar suelto: python snake_game.py"""
import pygame
import random
import sys

CELL = 24
GRID = 18
SIZE = CELL * GRID
FPS = 12

BG = (10, 10, 18)
SNAKE_COLOR = (60, 220, 130)
FOOD_COLOR = (230, 60, 90)
TEXT_COLOR = (220, 220, 240)


def run():
    pygame.init()
    screen = pygame.display.set_mode((SIZE, SIZE + 40))
    pygame.display.set_caption("HACK-PAD Snake (PC)")
    clock = pygame.time.Clock()
    font = pygame.font.SysFont("consolas", 22)

    snake = [(9, 9), (8, 9), (7, 9)]
    direction = (1, 0)
    food = (random.randrange(GRID), random.randrange(GRID))
    score = 0
    alive = True

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return
            if event.type == pygame.KEYDOWN:
                if event.key in (pygame.K_UP, pygame.K_w) and direction != (0, 1):
                    direction = (0, -1)
                elif event.key in (pygame.K_DOWN, pygame.K_s) and direction != (0, -1):
                    direction = (0, 1)
                elif event.key in (pygame.K_LEFT, pygame.K_a) and direction != (1, 0):
                    direction = (-1, 0)
                elif event.key in (pygame.K_RIGHT, pygame.K_d) and direction != (-1, 0):
                    direction = (1, 0)
                elif event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    return
                elif event.key == pygame.K_r and not alive:
                    snake = [(9, 9), (8, 9), (7, 9)]
                    direction = (1, 0)
                    food = (random.randrange(GRID), random.randrange(GRID))
                    score = 0
                    alive = True

        if alive:
            head = (snake[0][0] + direction[0], snake[0][1] + direction[1])
            hit_wall = not (0 <= head[0] < GRID and 0 <= head[1] < GRID)
            hit_self = head in snake
            if hit_wall or hit_self:
                alive = False
            else:
                snake.insert(0, head)
                if head == food:
                    score += 10
                    while food in snake:
                        food = (random.randrange(GRID), random.randrange(GRID))
                else:
                    snake.pop()

        screen.fill(BG)
        for (x, y) in snake:
            pygame.draw.rect(screen, SNAKE_COLOR, (x * CELL, y * CELL, CELL - 2, CELL - 2), border_radius=4)
        pygame.draw.rect(screen, FOOD_COLOR, (food[0] * CELL, food[1] * CELL, CELL - 2, CELL - 2), border_radius=6)

        label = font.render(f"Score: {score}" + ("" if alive else "  -  GAME OVER (R para reiniciar)"), True, TEXT_COLOR)
        screen.blit(label, (8, SIZE + 8))

        pygame.display.flip()
        clock.tick(FPS)


if __name__ == "__main__":
    run()
