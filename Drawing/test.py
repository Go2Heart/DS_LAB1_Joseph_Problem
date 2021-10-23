import math
import pygame
from pygame.locals import *


def DrawArc(screen):
    mycolcor = (255, 255, 255)
    position = (150, 150, 150, 150)
    start = math.radians(0)
    end = math.radians(360)
    width = 4
    pygame.draw.arc(screen, mycolcor, position, start, end, width)


def main():
    pygame.init()
    pygame.display.set_caption('Draw Arcs')
    screen = pygame.display.set_mode([600, 500])

    mRunning = True
    while mRunning:
        for event in pygame.event.get():
            if event.type == QUIT:
                mRunning = False
        screen.fill((0, 0, 0))
        DrawArc(screen)
        pygame.display.update()
    pygame.quit()


if __name__ == "__main__":
    main()