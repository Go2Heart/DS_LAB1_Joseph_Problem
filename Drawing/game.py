import pygame
from pygame import *
import pygame.freetype
from sys import exit
import math
from button import Button
import csv


Cost = []
Odder = []
Point = []
with open("demo.csv") as f:
    reader = csv.reader(f)
    header_row = next(reader)
    i = 0
    n = int(header_row[0])
    m = int(header_row[1])
    header_row = next(reader)[:-2]
    for i in range(int(len(header_row)-1 / 2)):
        try:
            Odder.append(int(header_row[2*i]))
            Cost.append(int(header_row[2*i+1]))
        except IndexError or ValueError:
            break
    header_row = next(reader)
    for i in range(len(header_row)-1):
        try:
            Point.append(int(header_row[i]))
            i = i + 1
        except IndexError:
            continue


def kill(screen,rad,color):
    DrawArc(screen, 300 + 200 * math.sin(rad), 300 + 200 * math.cos(rad),
            color, 31)
    pygame.display.update()
    pygame.time.delay(1)

def disappear(screen,rad):
    color = 0
    while(color != 256):
        kill(screen,rad,(color,color,color))
        color += 1


def DrawArc(screen, x, y, mycolor, size = 30):
    mycolcor = mycolor
    position = (x, y)
    pygame.draw.circle(screen, mycolcor, position, size, 0)


def waitforclick():
    pygame.event.clear()
    while True:
        event = pygame.event.wait()
        if event.type == MOUSEBUTTONDOWN:
            return

WIDTH, HEIGHT = 1000, 600
pygame.init()
pointer_rect = pointer.get_rect()
pointer_rect = pointer_rect.move((WIDTH - pointer_rect.width)/2,(HEIGHT - pointer_rect.height))
#pygame.mixer.quit()
GAME_FONT = pygame.font.Font('./Fonts/FiraCode-Light.ttf', 18)
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

x = 0
rad = 0
screen.fill((255, 255, 255))

for i in range(len(Odder)):
    DrawArc(screen, 300 + 200 * math.sin(rad), 300 + 200 * math.cos(rad),(100, 100, 200))
    text = GAME_FONT.render(str(i+1), True, (0, 0, 0))
    screen.blit(text, (300 + 260 * math.sin(rad), 300 + 260 * math.cos(rad)))
    rad += math.pi * (360 / len(Odder) / 180)

text_n = GAME_FONT.render("n = "+str(n), True, (0, 0, 0))
screen.blit(text_n,(700,200))
text_m = GAME_FONT.render("m = "+str(m), True, (0, 0, 0))
screen.blit(text_m,(700,250))
text_point = GAME_FONT.render("pointer at:", True, (0, 0, 0))
screen.blit(text_point,(700,400))
text_cost = GAME_FONT.render("last cost:        0", True, (0, 0, 0))
screen.blit(text_cost,(700,450))
#play_button = Button(screen, "PLAY")
#play_button.draw_button()

i = 0
rad = math.pi * (360 / len(Odder) / 180)
p_rad = math.pi * (360 / len(Point) / 180)
now = 0
i1 = 0
#newPointer = pointer
while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            exit()
        elif i == 0:
            waitforclick()
            break
    # 设置FPS
    if i > 0 :
        DrawArc(screen, 300 + 150 * math.sin(rad * (Point[i-1] - 1)), 300 + 150 * math.cos(rad * (Point[i-1]-1)),
               (255, 255, 255), 6)
    clock.tick(2)
    try:
        pygame.draw.rect(screen, (255, 255, 255), (900, 400, 200, 50))
        DrawArc(screen, 300 + 150 * math.sin(rad * (Point[i]-1)), 300 + 150 * math.cos(rad *(Point[i]-1)),
                (0, 0, 0), 5)
        text_point_value =  GAME_FONT.render(str(Point[i]), True, (0, 0, 0))
        screen.blit(text_point_value,(900,400))

        if Point[i] == Odder[i1] :
            disappear(screen,rad * (Odder[i1] - 1 ))
            pygame.draw.rect(screen, (255, 255, 255), (850, 450, 250, 50))
            text_cost_value = GAME_FONT.render(str(Cost[i1]), True, (0, 0, 0))
            screen.blit(text_cost_value,(900,450))
            i1 = i1 + 1
        i = i + 1
    except IndexError:
        DrawArc(screen, 300 + 200 * math.sin(rad * (Odder[i1] - 1)), 300 + 200 * math.cos(rad * (Odder[i1] - 1)),
                (255, 255, 255), 31)
        pygame.display.update()
        waitforclick()
        exit()
    pygame.display.update()
