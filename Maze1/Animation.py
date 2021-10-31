import pygame
import os
import time
def animate(path):
    current_path = os.path.dirname(os.path.abspath(__file__))

    window = pygame.display.set_mode((900,500))

    run = True
    pygame.display.set_caption("MAZE 2")
    maze_image = pygame.image.load(os.path.join(current_path,'maze2.png'))
    maze = pygame.transform.scale(maze_image,(600,400))

    x = 200
    y = 160
    i = 1
    stop = False
    window.fill((255,255,255))
    window.blit(maze, (150,60))
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
       
        pygame.draw.circle(window,(0,255,0),(x,y),20)#200 160 (y->65)(x->85)
        if i>=len(path):
            run = False
            time.sleep(5)
            continue
        if path[i-1]+1 == path[i] and (not stop):
            x+=85
        elif path[i]+1 == path[i-1] and (not stop):
            x-=85
        elif path[i]-path[i-1]>1 and (not stop):
            y+=65
        elif (not stop):
            y-=65
        if i<len(path):
            i+=1
        else:
            stop = True
            
        pygame.display.update()
        time.sleep(0.3)
    pygame.quit()

def walk(Q):
    curr = 7
    path = []
    #print(str(curr) + "->",)
    path.append(curr)
    while curr != 41:
        mx = -float('inf')
        idx = 0
        for i in range(len(Q[curr])):
            if Q[curr][i] > mx:
                mx = Q[curr][i]
                idx = i
        next = idx
        #print(str(next) + "->",)
        path.append(next)
        curr = next
    #print('done')
    path.append(-1)
    animate(path)
Q = []
for i in range(42):
    Q.append(list(map(float,input().split())))

walk(Q)


