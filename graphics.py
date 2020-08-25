from ctypes import c_double, c_int, CDLL
import sys


from cs1lib import *

lib_path = './python/sudokumodule.so'
mainmodule = CDLL(lib_path)

windowWidth = 400
windowHeight = 800

drawFirstPage = True  # keeps track of what page is being drawn
difficulty = None # keeps track of what the difficulty set is
hover = None

## draws simple background for game
def draw_background():
    set_fill_color(.2, 0, 0, .5)
    draw_rectangle(0, 0, windowWidth, windowHeight)


def mouse_move(mx, my):
    global hover

    ## handling hovers on the first page
    if drawFirstPage:

        ## solve own button hover
        if windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 1 <= my <= (windowHeight//5) * 1 + windowHeight//6:
            hover = "page1Solve"

        ## easy button hover
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 2 <= my <= (windowHeight//5) * 2 + windowHeight//6:
            hover = "page1Easy"
        
        ## medium button hover
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 3 <= my <= (windowHeight//5) * 3 + windowHeight//6:
            hover = "page1Medium"
        
        ## hard button hover
        elif  windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 4 <= my <= windowHeight//5 * 4 + windowHeight//6:
            hover = "page1Hard" 

        else:
            hover = None
    
    ## hovers on the game page
    else:
        pass


## handles mouse clicks
def mouse_click(mx, my):
    global difficulty

    ## handling clicks on the first page
    if drawFirstPage:

        ## solve own button click
        if windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 1 <= my <= (windowHeight//5) * 1 + windowHeight//6:
            difficulty = "solve"
            draw_first_page = False

        ## easy button click
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 2 <= my <= (windowHeight//5) * 2 + windowHeight//6:
            difficulty = "easy"
            draw_first_page = False
        
        ## medium button click
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 3 <= my <= (windowHeight//5) * 3 + windowHeight//6:
            difficulty = "medium"
            draw_first_page = False
        
        ## hard button click
        elif  windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 4 <= my <= windowHeight//5 * 4 + windowHeight//6:
            difficulty = "hard"   
            draw_first_page = False
    
    ## clicks on the game page
    else:
        pass


def mouse_release(mx, my):
    pass

def key_click(key):
    pass
    
def key_release(key):
    pass

def draw_first_page():
    
    if hover == "page1Solve":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    draw_rectangle(windowWidth//4, (windowHeight//5)*1, windowWidth//2, windowHeight//6)  ## solve

    if hover == "page1Easy":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    draw_rectangle(windowWidth//4, (windowHeight//5)*2, windowWidth//2, windowHeight//6)  ## easy

    if hover == "page1Medium":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    draw_rectangle(windowWidth//4, (windowHeight//5)*3, windowWidth//2, windowHeight//6)  ## medium

    if hover == "page1Hard":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    draw_rectangle(windowWidth//4, (windowHeight//5)*4, windowWidth//2, windowHeight//6)  ## hard

    set_font_size(windowWidth // 12)
    draw_text("Select Difficulty", windowWidth//5, windowHeight//7)

    set_font_size(windowWidth // 11)
    draw_text("Solve", windowWidth//8 * 3, windowHeight//48 * 14)
    draw_text("Own", windowWidth//5 * 2, windowHeight//12 * 4)

    set_font_size(windowWidth // 11)
    draw_text("Easy", windowWidth//100 * 39, windowHeight//2 * 1)

    set_font_size(windowWidth // 11)
    draw_text("Medium", windowWidth//20 * 7, windowHeight//10 * 7)

    set_font_size(windowWidth // 11)
    draw_text("Hard", windowWidth//100 * 39, windowHeight//10 * 9)

        

    

def draw_game_page():
    pass


def main():
    clear()
    draw_background()

    if drawFirstPage:
        draw_first_page()
    else:
        draw_game_page()



start_graphics(main, width=windowWidth, height=windowHeight, mouse_press=mouse_click, mouse_release=mouse_release, key_press=key_click, key_release=key_release, mouse_move=mouse_move)


