"""Simon Says / memory game, HACK-PAD themed (4 colored buttons, like the
pad's 4 keys). Can be run standalone: python memory_game.py"""
import pygame
import random
import sys
import time

W, H = 420, 500
COLORS = [
    ("Pink",   (255, 0, 80),   (120, 0, 40)),
    ("Orange", (255, 120, 0),  (120, 55, 0)),
    ("Yellow", (255, 220, 0),  (120, 100, 0)),
    ("Cyan",   (0, 160, 255),  (0, 70, 120)),
]
PAD_RECT = [
    pygame.Rect(20, 20, 180, 180),
    pygame.Rect(220, 20, 180, 180),
    pygame.Rect(20, 220, 180, 180),
    pygame.Rect(220, 220, 180, 180),
]


def flash_pad(screen, idx, font):
    name, bright, dim = COLORS[idx]
    pygame.draw.rect(screen, bright, PAD_RECT[idx], border_radius=16)
    pygame.display.flip()
    pygame.time.delay(280)
    draw_board(screen, font, message="")
    pygame.time.delay(120)


def draw_board(screen, font, message):
    screen.fill((12, 12, 20))
    for i, (name, bright, dim) in enumerate(COLORS):
        pygame.draw.rect(screen, dim, PAD_RECT[i], border_radius=16)
    label = font.render(message, True, (230, 230, 240))
    screen.blit(label, (20, 420))
    pygame.display.flip()


def run():
    pygame.init()
    screen = pygame.display.set_mode((W, H))
    pygame.display.set_caption("HACK-PAD Memory (PC)")
    font = pygame.font.SysFont("consolas", 20)

    sequence = []
    player_pos = 0
    state = "show"  # show | wait | grow | over
    last_step_time = 0

    def new_round():
        nonlocal player_pos, state, last_step_time
        sequence.append(random.randrange(4))
        player_pos = 0
        state = "show"
        last_step_time = time.time()

    new_round()
    draw_board(screen, font, f"Level {len(sequence)}")
    show_index = 0

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                running = False
            if event.type == pygame.MOUSEBUTTONDOWN and state == "wait":
                for i, r in enumerate(PAD_RECT):
                    if r.collidepoint(event.pos):
                        flash_pad(screen, i, font)
                        if sequence[player_pos] == i:
                            player_pos += 1
                            if player_pos == len(sequence):
                                state = "grow"
                                last_step_time = time.time()
                        else:
                            state = "over"

        if state == "show":
            if time.time() - last_step_time > 0.55:
                if show_index < len(sequence):
                    flash_pad(screen, sequence[show_index], font)
                    show_index += 1
                    last_step_time = time.time()
                else:
                    show_index = 0
                    state = "wait"
                    draw_board(screen, font, f"Level {len(sequence)} - your turn")

        elif state == "grow":
            if time.time() - last_step_time > 0.6:
                new_round()
                draw_board(screen, font, f"Level {len(sequence)}")

        elif state == "over":
            draw_board(screen, font, f"You lost at level {len(sequence)} - ESC to quit, click to restart")
            for event2 in pygame.event.get():
                if event2.type == pygame.MOUSEBUTTONDOWN:
                    sequence.clear()
                    new_round()
                    draw_board(screen, font, f"Level {len(sequence)}")
                    show_index = 0

        pygame.time.delay(16)

    pygame.quit()


if __name__ == "__main__":
    run()
