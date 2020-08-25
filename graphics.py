from ctypes import c_double, c_int, CDLL
import sys


from cs1lib import *

lib_path = './mainmodule.so'
mainmodule = CDLL(lib_path)

windowWidth = 400
windowHeight = 800

drawFirstPage = True  # keeps track of what page is being drawn
difficulty = "easy"  # keeps track of what the difficulty set is

## draws simple background for game
def draw_background():
    set_fill_color(.2, 0, 0, .5)
    draw_rectangle(0, 0, 400, 800)


## handles mouse clicks
def mouse_click(mx, my):

    ## handling clicks on the first page
    if drawFirstPage:

        ## easy button click
        if windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 2 <= my <= windowHeight//6 + (windowHeight//5) * 2:
            difficulty = "easy"
        
        ## medium button click
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 3 <= my <= (windowHeight//5) * 3 + windowHeight//6:
            difficulty = "medium"
        
        ## hard button click
        elif  windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 4 <= my <= windowHeight//5 * 4 + windowHeight//6:
            difficulty = "hard"
        
        elif 
    
    ## clicks on the game page
    else:


def mouse_release(mx, my):
    pass

def key_click(key):
    pass
    
def key_release(key):
    pass

def draw_first_page():
    draw_text("Select Difficulty", windowWidth//5, windowHeight//7)
    draw_rectangle(windowWidth//4, (windowHeight//5)*2, windowWidth//2, windowHeight//6)  ## easy
    draw_rectangle(windowWidth//4, (windowHeight//5)*3, windowWidth//2, windowHeight//6)  ## medium
    draw_rectangle(windowWidth//4, (windowHeight//5)*4, windowWidth//2, windowHeight//6)  ## hard

    

def draw_game_page():
    pass


def main():
    clear()
    draw_background()

    if drawFirstPage:
        draw_first_page()
    else:
        draw_game_page()



start_graphics(main, width=windowWidth, height=windowHeight, mouse_press=mouse_click, mouse_release=mouse_release, key_press=key_click, key_release=key_release)


