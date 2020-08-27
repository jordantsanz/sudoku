from ctypes import *
import sys
import time


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
showChecked = False

difficulty = None # keeps track of what the difficulty set is
hover = None
clickedSquare = False # keeps track if a square has been clicked or not
xClick = 0
yClick = 0
inputNumber = 0
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
        overButton = False
        if windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//3)*2+(squareSize*.5) <= my <= (windowHeight//3)*2+(squareSize*.5) + (squareSize * 2):
            hover = "page2Solve"
            overButton = True
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and ((windowHeight//3)*2)+(squareSize*3.5) <= my <= ((windowHeight//3)*2)+(squareSize*3.5) + (squareSize * 2):
            hover = "page2NewGame"
            overButton = True
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//3)*2-(squareSize*2.5) <= my <= (windowHeight//3)*2-(squareSize*2.5) + (squareSize * 2):
            hover = "page2Check"
            overButton = True
        for button in range(10):
            if ((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9)) <= mx <= ((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9)) + buttonSize:
                if ((edgeSize // 2) + (squareSize*10) + (edgeSize // 4)) <= my <= ((edgeSize // 2) + (squareSize*10) + (edgeSize // 4)) + buttonSize:
                    hover = "page2" + str(button + 1)
                    overButton = True
        if not overButton:
            hover = None


## handles mouse clicks
def mouse_click(mx, my):
    global difficulty, clickedSquare, xClick, yClick, inputNumber
    global drawFirstPage
    global puzzle, currentPuzzle, showSolved, showChecked, solvedPuzzle, colorPuzzle


    infile = open("./uipuzzles/blank.txt", "r")
    colorPuzzle = read_in_puzzle(infile)
    infile.close()

    ## handling clicks on the first page
    if drawFirstPage:

        ## solve own button click
        if windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 1 <= my <= (windowHeight//5) * 1 + windowHeight//6:
            difficulty = "solve"
            infile = open("./uipuzzles/blank.txt", "r")
            puzzle = read_in_puzzle(infile)
            infile.close()

            infile2 = open("./uipuzzles/blank.txt", "r")           
            currentPuzzle = read_in_puzzle(infile2)
            infile2.close()

            drawFirstPage = False

        ## easy button click
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 2 <= my <= (windowHeight//5) * 2 + windowHeight//6:
            difficulty = "easy"
            mainmodule.create(35, int(round(time.time() * 1000)), None)

            # read in original puzzle template
            infile = open("./uipuzzles/newpuzzle.txt", "r")
            puzzle = read_in_puzzle(infile)
            infile.close()

            # read in puzzle to be changed
            infile2 = open("./uipuzzles/newpuzzle.txt", "r")
            currentPuzzle = read_in_puzzle(infile2)
            infile2.close()

            # read in solved puzzle
            infile = open("./uipuzzles/solvedpuzzle.txt", "r")
            solvedPuzzle = read_in_puzzle(infile)
            infile.close()

            # off of first page
            drawFirstPage = False
        
        ## medium button click
        elif windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 3 <= my <= (windowHeight//5) * 3 + windowHeight//6:
            difficulty = "medium"
            mainmodule.create(40, int(round(time.time() * 1000)), None)

            # read in original puzzle
            infile = open("./uipuzzles/newpuzzle.txt", "r")
            puzzle = read_in_puzzle(infile)
            infile.close()

            # read in puzzle that will be changed
            infile2 = open("./uipuzzles/newpuzzle.txt", "r")
            currentPuzzle = read_in_puzzle(infile2)
            infile2.close()

            # read in solved puzzle
            infile = open("./uipuzzles/solvedpuzzle.txt", "r")
            solvedPuzzle = read_in_puzzle(infile)
            infile.close()

            # not on first page anymore
            drawFirstPage = False
        
        ## hard button click
        elif  windowWidth//4 <= mx <= windowWidth//4 + windowWidth//2 and (windowHeight//5) * 4 <= my <= windowHeight//5 * 4 + windowHeight//6:
            difficulty = "hard" 
            mainmodule.create(50, int(round(time.time() * 1000)), None)
            infile = open("./uipuzzles/newpuzzle.txt", "r")
            puzzle = read_in_puzzle(infile)
            infile.close()
            infile2 = open("./uipuzzles/newpuzzle.txt", "r")
            currentPuzzle = read_in_puzzle(infile2)
            infile2.close()  
            infile = open("./uipuzzles/solvedpuzzle.txt", "r")
            solvedPuzzle = read_in_puzzle(infile)
            infile.close()
            drawFirstPage = False
    
    ## clicks on the game page
    else:
        
        # solve button
        if windowWidth//4 <= mx <= (windowWidth//4)*3 and (windowHeight//3)*2+(squareSize*.5) <= my <= ((windowHeight//3)*2)+(squareSize*2.5):
            showChecked = False
            showSolved = True
            if difficulty == "solve":
                outfile = open("./uipuzzles/newpuzzle.txt", "w")
                write_out_puzzle(currentPuzzle, outfile)
                outfile.close()
                if (mainmodule.puzzleValidUI()):
                    mainmodule.solveUI()
                    infile = open("./uipuzzles/solvedpuzzle.txt", "r")
                    solvedPuzzle = read_in_puzzle(infile)
                    infile.close()
                else:
                    solvedPuzzle = None
            

        # new game button
        elif windowWidth//4 <= mx <= (windowWidth//4)*3 and ((windowHeight//3)*2)+(squareSize*3.5) <= my <= ((windowHeight//3)*2)+(squareSize*3.5)+(squareSize*2):
            drawFirstPage = True
            showChecked = False
            showSolved = False

        # check button
        elif windowWidth//4 <= mx <= (windowWidth//4)*3 and ((windowHeight//3)*2)-(squareSize*2.5) <= my <= ((windowHeight//3)*2)-(squareSize*3)+(squareSize*2.5):
            if showChecked == False:
                showChecked = True
            else:
                showChecked = False
        
        ## check for number button clicks on button y
        if ((edgeSize // 2) + (squareSize*10) + (edgeSize // 4)) <= my <= ((edgeSize // 2) + (squareSize*10) + (edgeSize // 4)) + buttonSize:  # check y
            
            # check button x
            for button in range(10):
                if ((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9)) <= mx <= ((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9)) + buttonSize:
                    
                    # if button is 1-9 button
                    if button != 9:

                        inputNumber = str(button + 1)
                        clickedSquare = None
                        break

                    # pressed delete button
                    else:

                        inputNumber = "10"
                        clickedSquare = None
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
    global currentPuzzle, clickedSquare

    # if number square has been clicked and a square has been clicked
    if clickedSquare and inputNumber != None and inputNumber != 0:

        # check each square to see if it was that square
        for row in range(9):
            for column in range(9):
                if edgeSize // 2 + (squareSize*column) <= xClick <= edgeSize // 2 + (squareSize*column) + squareSize and edgeSize // 2 + (squareSize*row) <= yClick <= edgeSize // 2 + (squareSize*row) + squareSize:

                    # if it was not a delete and it wasn't an original number
                    if inputNumber != "10" and (puzzle[row][column] != currentPuzzle[row][column] or currentPuzzle[row][column] == "0"):
                        currentPuzzle[row][column] = inputNumber

                    # else just if it wasn't an original number
                    else:
                        if puzzle[row][column] != currentPuzzle[row][column] and not showSolved:
                            currentPuzzle[row][column] = "0"
                    
        
def mouse_release(mx, my):
    pass

def key_click(key):
    pass
    
def key_release(key):
    pass

# draw first page
def draw_first_page():
    
    # draw solve button
    if hover == "page1Solve":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    draw_rectangle(windowWidth//4, (windowHeight//5)*1, windowWidth//2, windowHeight//6)  ## solve

    # draw easy button
    if hover == "page1Easy":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    draw_rectangle(windowWidth//4, (windowHeight//5)*2, windowWidth//2, windowHeight//6)  ## easy

    # draw medium button
    if hover == "page1Medium":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    draw_rectangle(windowWidth//4, (windowHeight//5)*3, windowWidth//2, windowHeight//6)  ## medium

    # draw hard button
    if hover == "page1Hard":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    draw_rectangle(windowWidth//4, (windowHeight//5)*4, windowWidth//2, windowHeight//6)  ## hard

    # set difficulty words
    set_font_size(windowWidth // 12)
    draw_text("Select Difficulty", windowWidth//5, windowHeight//7)

    # Solve own words
    set_font_size(windowWidth // 11)
    draw_text("Solve", windowWidth//8 * 3, windowHeight//48 * 14)
    draw_text("Own", windowWidth//5 * 2, windowHeight//12 * 4)

    # easy
    set_font_size(windowWidth // 11)
    draw_text("Easy", windowWidth//100 * 39, windowHeight//2 * 1)

    # medium
    set_font_size(windowWidth // 11)
    draw_text("Medium", windowWidth//20 * 7, windowHeight//10 * 7)

    # hard
    set_font_size(windowWidth // 11)
    draw_text("Hard", windowWidth//100 * 39, windowHeight//10 * 9)

#  drawing the game page
def draw_game_page():
    check_clicks()
    draw_boxes()

# draw all of the graphics
def draw_boxes():
    global showSolved, showChecked, solvedPuzzle, inputNumber, clickedSquare

    set_fill_color(1, 1, 1)

    ## draw all 9x9 squares
    for row in range(9):
        for column in range(9):
            set_fill_color(1, 1, 1)
            draw_rectangle(edgeSize // 2 + (squareSize*row), edgeSize // 2 + (squareSize*column), squareSize, squareSize)

    disable_fill()
    set_stroke_width(3)

    # draw the big 3x3 boxes on top
    for row in range(3):
        for column in range(3):
            draw_rectangle(edgeSize // 2 + (squareSize*3*row), edgeSize // 2 + (squareSize*3*column), squareSize*3, squareSize*3)

    set_stroke_width(1)
    enable_fill()
    set_fill_color(0, 0, 1, .5)
    set_font_size(windowWidth // 15)

     # if the solve button was clicked
    if showSolved:
        clickedSquare = False
        inputNumber = None
        
        set_stroke_color(0, 0, 0)
        if solvedPuzzle == None:
            draw_text("Not a valid Puzzle", windowWidth//4, (windowHeight//3)*2)
        else:
            # draw each answer to the puzzle in the right spot
            for rowIndex in range(9):
                for colIndex in range(9):
                    currentPuzzle[rowIndex][colIndex] = solvedPuzzle[rowIndex][colIndex]
    
    if showChecked:

        for rowIndex in range(9):
            for colIndex in range(9):
                if currentPuzzle[rowIndex][colIndex] != solvedPuzzle[rowIndex][colIndex]:
                    colorPuzzle[rowIndex][colIndex] = 1

    # draw the numbers in the puzzle
    for rowIndex in range(9):
        for colIndex in range(9):

            # if it isn't a 0
            if (currentPuzzle[rowIndex][colIndex] != "0"):

                # if it is wrong, draw in red
                if (colorPuzzle[rowIndex][colIndex] == 1):
                    set_stroke_color(1, 0, 0)

                elif (currentPuzzle[rowIndex][colIndex] == puzzle[rowIndex][colIndex]):
                    set_stroke_color(0, 0, 0)

                # else, draw in black
                else:
                    set_stroke_color(.4, .4, .4)

                # draw the number
                draw_text(currentPuzzle[rowIndex][colIndex], ((edgeSize // 10) * 6) + (squareSize*colIndex), ((edgeSize // 10) * 4) + (squareSize*(rowIndex+ 1)))


    # draw number button hovers
    for button in range(10):
        if hover == "page2" + str(button + 1) or inputNumber == str(button + 1):
            set_fill_color(.54, .36, .92)
        else:
            set_fill_color(.34, .15, .90)

        # draw button
        draw_rectangle((edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9), ((edgeSize // 2 + (squareSize*10)) + edgeSize // 4), buttonSize, buttonSize)
        set_stroke_color(0, 0, 0)  ## black

        # draw numbers on button
        if (button != 9):
            draw_text(str(button + 1), (edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9) + (buttonSize // 5),  (((edgeSize // 2 + (squareSize*10)) + edgeSize // 4) + buttonSize) - (buttonSize // 5))
        else:
            draw_text("X", (edgeSize // 4 + (buttonSize*button)) + (button * ((windowWidth - edgeSize // 2) - (10*buttonSize)) // 9) + (buttonSize // 5),  (((edgeSize // 2 + (squareSize*10)) + edgeSize // 4) + buttonSize) - (buttonSize // 5))
    
    # drawing solve button colors
    if hover == "page2Solve":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)

    # solve button drawing
    draw_rectangle(windowWidth//4, (windowHeight//3)*2+(squareSize*.5), windowWidth//2, squareSize * 2)
    draw_text("Solve", windowWidth//4 + (2 * squareSize), (windowHeight//3)*2 + (squareSize*1.5))

    # drawing new game button colors
    if hover == "page2NewGame":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    
    # draw new game button
    draw_rectangle(windowWidth//4, ((windowHeight//3)*2)+(squareSize*3.5), windowWidth//2, squareSize * 2)
    draw_text("New Game", windowWidth//4 + squareSize, ((windowHeight//3)*2)+(squareSize*4.5))

    # drawing a check button
    if hover == "page2Check":
        set_fill_color(.31, .49, 1)
    else:
        set_fill_color(.26, .41, .86)
    
    if difficulty != "solve":
        draw_rectangle(windowWidth//4, ((windowHeight//3)*2)-(squareSize*2.5), windowWidth//2, squareSize * 2)
        draw_text("Check", windowWidth//4 + (2 * squareSize), ((windowHeight//3)*2)-(squareSize*1.5)) 

   
# read in a puzzle from a text file
def read_in_puzzle(infile):
    puzzle = []
    for line in infile:
        split_line = line.strip().split(" ")
        puzzle.append(split_line)
    return puzzle

# write out the puzzle into a file
def write_out_puzzle(puzzle, outfile):
    for row in puzzle:
        for column in row:
            outfile.write("%d " % int(column))
        outfile.write("\n")


# main
def main():
    clear()
    draw_background()

    if drawFirstPage:
        draw_first_page()
    else:
        draw_game_page()

 
start_graphics(main, title="Sudoku", width=windowWidth, height=windowHeight, mouse_press=mouse_click, mouse_release=mouse_release, key_press=key_click, key_release=key_release, mouse_move=mouse_move)


