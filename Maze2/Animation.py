import pygame
import os
import time
def animate(path):
    current_path = os.path.dirname(os.path.abspath(__file__))

    window = pygame.display.set_mode((1000,900))

    run = True
    pygame.display.set_caption("MAZE 3")
    maze_image = pygame.image.load(os.path.join(current_path,'maze3.jpeg'))
    maze = pygame.transform.scale(maze_image,(700,700))

    x = 500
    y = 93
    i = 1
    stop = False
    window.fill((255,255,255))
    window.blit(maze, (150,60))
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
       
        pygame.draw.circle(window,(0,255,0),(x,y),10)#200 160 (y->65)(x->85)
        if i>=len(path):
            run = False
            time.sleep(5)
            continue
        if path[i-1]+1 == path[i] and (not stop):
            x+=40
        elif path[i]+1 == path[i-1] and (not stop):
            x-=40
        elif path[i]-path[i-1]>1 and (not stop):
            y+=40
        elif (not stop):
            y-=40
        if i<len(path):
            i+=1
        else:
            stop = True
            
        pygame.display.update()
        time.sleep(0.15)
    pygame.quit()

def walk(Q):
    curr = 8
    path = []
    #print(str(curr) + "->",)
    path.append(curr)
    while curr != 280:
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
for i in range(289):
    Q.append(list(map(float,input().split())))

walk(Q)


