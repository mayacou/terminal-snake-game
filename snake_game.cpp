#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

// global variables
const int width = 20;
const int height = 20;
int x, y, foodx, foody, score;
int tailx[100], taily[100]; //store snake body position
int nTail; //store length of body
bool gameOver;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// setup game
void setup() {
    gameOver = false;
    dir = STOP;
    
    //start in middle
    x = width/2;
    y = height/2;

    //rand food
    foodx = rand() % width;
    foody = rand() % height;
    
    score = 0;
    nTail = 0;
}

// make board
void draw() {
    system("cls"); //clear console

    //top wall
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;

    //display the board
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (j == 0) cout << "#"; //left wall

            if (i == y && j == x) cout << "O"; //snake head
            else if (i == foody && j == foodx) cout << "*"; //food
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailx[k] == j && taily[k] == i) {
                        cout << "o"; //snake tail
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
            if (j == width - 1) cout << "#"; //right wall
        }
        cout << endl;
    }

    //bottom wall
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;

    //display score
    cout << "Score: " << score << endl;
}

// define input
void input() {
    if(_kbhit()) { //if keyboard is hit
        switch (_getch()) { //get character
            case 'w':
                dir = UP;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

// define logic
void logic() {
    //move tail
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;

    //tail
    for (int i = 1; i < nTail; i++) {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    //move around
    switch(dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    //check for walls
    if (x >= width || x < 0 || y >= height || y < 0) {
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailx[i] == x && taily[i] == y) { //ran into tail
            gameOver = true;
        }
    }

    //check for food
    if (x == foodx && y == foody) {
        score += 10;
        foodx = rand() % width;
        foody = rand() % height;
        nTail++;
    }
}

// main to execute
int main() {
    srand(time(0)); //rand number generator
    
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        _sleep(100); //pause for game speed, 100 milliseconds
    }
    return 0;
}