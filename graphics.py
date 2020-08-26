from ctypes import *
import sys


from cs1lib import *

lib_path = './python/sudokumodule.so'
mainmodule = CDLL(lib_path)

windowWidth = 400
windowHeight = 800
edgeSize = windowWidth // 4
boardWidth = windowWidth - edgeSize
boardHeight = windowHeight - edgeSize

squareSize = boardWidth // 9
buttonSize = (windowWidth - edgeSize) // 10

drawFirstPage = True  # keeps track of what page is being drawn
showSolved = False
difficulty = None # keeps track of what the difficulty set is
hover = None
clickedSquare = False # keeps track if a square has been clicked or not
xClick = 0
yClick = 0
inputNumber = None
currentPuzzle = None

puzzle = None

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
    global difficulty, clickedSquare, xClick, yClick, inputNumber
    global drawFirstPage
    global puzzle, currentPuzzle

    ## handling clicks on the first page
    if drawFirstPage:

        ## solve own button click
        if windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 1 <= my <= (windowHeight//5) * 1 + windowHeight//6:
            difficulty = "solve"
            infile = open("./uipuzzles/blank.txt", "r")
            puzzle = read_in_puzzle(infile)
            currentPuzzle = puzzle
            infile.close()
            drawFirstPage = False

        ## easy button click
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 2 <= my <= (windowHeight//5) * 2 + windowHeight//6:
            difficulty = "easy"
            mainmodule.create(35, None)
            infile = open("./uipuzzles/newpuzzle.txt", "r")
            puzzle = read_in_puzzle(infile)
            currentPuzzle = puzzle
            infile.close()
            drawFirstPage = False
        
        ## medium button click
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 3 <= my <= (windowHeight//5) * 3 + windowHeight//6:
            difficulty = "medium"
            mainmodule.create(40, None)
            infile = open("./uipuzzles/newpuzzle.txt", "r")
            puzzle = read_in_puzzle(infile)
            currentPuzzle = puzzle
            infile.close()
            drawFirstPage = False
        
        ## hard button click
        elif  windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 4 <= my <= windowHeight//5 * 4 + windowHeight//6:
            difficulty = "hard" 
            mainmodule.create(50, None)
            infile = open("./uipuzzles/newpuzzle.txt", "r")
            puzzle = read_in_puzzle(infile)
            currentPuzzle = puzzle
            infile.close()  
            drawFirstPage = False
    
    ## clicks on the game page
    else:
        if windowWidth//4 <= mx <= (windowWidth//4)*3 and (windowWidth//3)*2 <= my <= ((windowHeight//3)*2)+(squareSize*2):
            if difficulty == "solve":
                mainmodule.solveUI()
                showSolved = True
            else:
                showSolved = True

        elif windowWidth//4 <= mx <= (windowWidth//4)*3 and ((windowHeight//3)*2)+(squareSize*3) <= my <= ((windowHeight//3)*2)+(squareSize*3) + squareSize * 2:
            drawFirstPage = True

        
        ## check for number button clicks
        if ((edgeSize // 2) + (squareSize*10) + (edgeSize // 4)) <= my <= ((edgeSize // 2) + (squareSize*10) + (edgeSize // 4)) + buttonSize:  # check y
            
            for button in range(10):
                if ((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9)) <= mx <= ((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9)) + buttonSize:
                    
                    if button != 9:

                        print(button)
                        inputNumber = button + 1
                        set_fill_color(1, 0, 0)
                        draw_rectangle((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9), ((edgeSize // 2 + (squareSize*10)) + edgeSize // 4), buttonSize, buttonSize)
                        draw_text(str(button + 1), (edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9) + (buttonSize // 5),  (((edgeSize // 2 + (squareSize*10)) + edgeSize // 4) + buttonSize) - (buttonSize // 5))
                        break
                    else:

                        inputNumber = "X"
                        set_fill_color(1, 0, 0)
                        draw_rectangle((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9), ((edgeSize // 2 + (squareSize*10)) + edgeSize // 4), buttonSize, buttonSize)
                        draw_text("X", (edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9) + (buttonSize // 5),  (((edgeSize // 2 + (squareSize*10)) + edgeSize // 4) + buttonSize) - (buttonSize // 5))
                        break

        else:
        ## square clicks
            for row in range(9):
                for column in range(9):
                    if edgeSize // 2 + (squareSize*row) <= mx <= edgeSize // 2 + (squareSize*row) + squareSize and edgeSize // 2 + (squareSize*column) <= my <= edgeSize // 2 + (squareSize*column) + squareSize:
                        clickedSquare = True  # square got clicked 
                        xClick = mx
                        yClick = my

## checks to draw a number in a square
def check_clicks():
    global currentPuzzle
    if clickedSquare and inputNumber != None:
        for row in range(9):
            for column in range(9):
                if edgeSize // 2 + (squareSize*row) <= xClick <= edgeSize // 2 + (squareSize*row) + squareSize and edgeSize // 2 + (squareSize*column) <= yClick <= edgeSize // 2 + (squareSize*column) + squareSize:
                    if inputNumber != "X" and puzzle[row][column] != currentPuzzle[row][column]:
                        currentPuzzle[row][column] = inputNumber

                    elif puzzle[row][column] != currentPuzzle[row][column]:
                        currentPuzzle[row][column] = 0
                    
        
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
    check_clicks()
    draw_boxes()



def draw_boxes():
    set_fill_color(1, 1, 1)

    ## draw all 9x9 squares
    for row in range(9):
        for column in range(9):
            draw_rectangle(edgeSize // 2 + (squareSize*row), edgeSize // 2 + (squareSize*column), squareSize, squareSize)

    disable_fill()
    set_stroke_width(3)

    for row in range(3):
        for column in range(3):
            draw_rectangle(edgeSize // 2 + (squareSize*3*row), edgeSize // 2 + (squareSize*3*column), squareSize*3, squareSize*3)

    set_stroke_width(1)
    enable_fill()
    set_fill_color(0, 0, 1, .5)
    set_font_size(windowWidth // 15)

    for rowIndex in range(9):
        for colIndex in range(9):
            if (currentPuzzle[rowIndex][colIndex] != "0"):
                if (currentPuzzle[rowIndex][colIndex] == puzzle[rowIndex][colIndex]):
                    set_stroke_color(0, 0, 0)
                else:
                    set_stroke_color(.3, .3, .3)
                draw_text(currentPuzzle[rowIndex][colIndex], ((edgeSize // 10) * 6) + (squareSize*rowIndex), ((edgeSize // 10) * 4) + (squareSize*(colIndex + 1)))

    for button in range(10):
        draw_rectangle((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9), ((edgeSize // 2 + (squareSize*10)) + edgeSize // 4), buttonSize, buttonSize)
        if (button != 9):
            draw_text(str(button + 1), (edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9) + (buttonSize // 5),  (((edgeSize // 2 + (squareSize*10)) + edgeSize // 4) + buttonSize) - (buttonSize // 5))
        else:
            draw_text("X", (edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9) + (buttonSize // 5),  (((edgeSize // 2 + (squareSize*10)) + edgeSize // 4) + buttonSize) - (buttonSize // 5))
    
    draw_rectangle(windowWidth//4, (windowHeight//3)*2, windowWidth//2, squareSize * 2)
    draw_text("Solve", windowWidth//4 + (2 * squareSize), (windowHeight//3)*2 + squareSize)
    draw_rectangle(windowWidth//4, ((windowHeight//3)*2)+(squareSize*3), windowWidth//2, squareSize * 2)
    draw_text("New Game", windowWidth//4 + squareSize, ((windowHeight//3)*2)+(squareSize*4))

def read_in_puzzle(infile):
    puzzle = []
    for line in infile:
        split_line = line.strip().split(" ")
        puzzle.append(split_line)
    return puzzle

def write_out_puzzle(puzzle, outfile):
    for row in puzzle:
        for column in row:
            outfile.write("%d " % int(column))
        outfile.write("\n")

def main():
    clear()
    draw_background()

    if drawFirstPage:
        draw_first_page()
    else:
        draw_game_page()



start_graphics(main, title="Sudoku", width=windowWidth, height=windowHeight, mouse_press=mouse_click, mouse_release=mouse_release, key_press=key_click, key_release=key_release, mouse_move=mouse_move)


