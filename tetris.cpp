#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define W 10
#define H 20
#define BLOCK 20

// ------------------ Global Variables -------------------
int board[W][H]; 
int posX, posY;
int currentPiece, nextPiece;
int rotation;
int color;
int score = 0;
int level = 1;
int lines = 0;
int speed = 40;
int baseSpeed = 40;

// Tetromino shapes
int shapes[7][4][4][4] = {
    /* I-Piece (line) */
    {
        /* Rotation 0° */
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 90° */
        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}},
        /* Rotation 180° (same as 0°) */
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 270° (same as 90°) */
        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}}},

    /* O-Piece (square) */
    {
        /* Rotation 0°, 90°, 180°, 270° (all same) */
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        {{1, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}},

    /* T-Piece */
    {
        /* Rotation 0° */
        {{0, 1, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 90° */
        {{0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 180° */
        {{0, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 270° */
        {{0, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}}},

    /* L-Piece */
    {
        /* Rotation 0° */
        {{1, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 90° */
        {{0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 180° */
        {{0, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 0}},
        /* Rotation 270° */
        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0}}},

    /* J-Piece */
    {
        /* Rotation 0° */
        {{0, 0, 1, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 90° */
        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}},
        /* Rotation 180° */
        {{0, 0, 0, 0},
         {1, 1, 1, 0},
         {1, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 270° */
        {{1, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}}},

    /* S-Piece */
    {
        /* Rotation 0° */
        {{0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 90° */
        {{0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 0}},
        /* Rotation 180° */
        {{0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 270° */
        {{0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 0}}},

    /* Z-Piece */
    {
        /* Rotation 0° */
        {{1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 90° */
        {{0, 0, 1, 0},
         {0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 180° */
        {{1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},
        /* Rotation 270° */
        {{0, 0, 1, 0},
         {0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}}}};

// ------------------ Function Prototypes -------------------
void clearBoard();
void drawBlock(int x, int y, int c);
void drawBoard();
int collision(int dx, int dy, int r);
void placePiece();
void clearLines();
void newPiece();
void drawPiece();
void drawGhostPiece();
void drawNextPiece();
void hardDrop();
void pauseGame();
void drawScore();
void gameLoop();
void difficultyMenu();
void menu();

// ------------------ Function Definitions -------------------

void clearBoard()
{
    for (int x = 0; x < W; x++)
        for (int y = 0; y < H; y++)
            board[x][y] = 0;
}

void drawBlock(int x, int y, int c)
{
    setfillstyle(SOLID_FILL, c);
    bar(x * BLOCK + 50, y * BLOCK + 50, (x + 1) * BLOCK + 50, (y + 1) * BLOCK + 50);
    setcolor(WHITE);
    rectangle(x * BLOCK + 50, y * BLOCK + 50, (x + 1) * BLOCK + 50, (y + 1) * BLOCK + 50);
}

void drawBoard()
{
    cleardevice();
    for (int x = 0; x < W; x++)
        for (int y = 0; y < H; y++)
            if (board[x][y])
                drawBlock(x, y, board[x][y]);
}

int collision(int dx, int dy, int r)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (shapes[currentPiece][r][i][j])
            {
                int nx = posX + j + dx;
                int ny = posY + i + dy;
                if (nx < 0 || nx >= W || ny >= H)
                    return 1;
                if (ny >= 0 && board[nx][ny])
                    return 1;
            }
    return 0;
}

void placePiece()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (shapes[currentPiece][rotation][i][j])
                board[posX + j][posY + i] = color;
}

void clearLines()
{
    for (int y = H - 1; y >= 0; y--)
    {
        int full = 1;
        for (int x = 0; x < W; x++)
            if (board[x][y] == 0)
                full = 0;
        if (full)
        {
            lines++;
            score += 100 * level;
            for (int yy = y; yy > 0; yy--)
                for (int x = 0; x < W; x++)
                    board[x][yy] = board[x][yy - 1];
            y++;
        }
    }
    level = lines / 10 + 1;
    speed = baseSpeed - level * 2;
    if (speed < 5)
        speed = 5;
}

void newPiece()
{
    currentPiece = nextPiece;
    nextPiece = rand() % 7;
    posX = 3;
    posY = 0;
    rotation = 0;
    color = 1 + rand() % 14;
}

void drawPiece()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (shapes[currentPiece][rotation][i][j])
                drawBlock(posX + j, posY + i, color);
}

void drawGhostPiece()
{
    int ghostY = posY;
    while (!collision(0, ghostY - posY + 1, rotation))
        ghostY++;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (shapes[currentPiece][rotation][i][j])
            {
                setcolor(LIGHTGRAY);
                rectangle((posX + j) * BLOCK + 50, (ghostY + i) * BLOCK + 50,
                          (posX + j + 1) * BLOCK + 50, (ghostY + i + 1) * BLOCK + 50);
            }
}

void drawNextPiece()
{
    int startX = W * BLOCK + 100;
    int startY = 50;
    setcolor(WHITE);
    outtextxy(startX, startY - 30, "Next:");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (shapes[nextPiece][0][i][j])
            {
                setfillstyle(SOLID_FILL, 1 + nextPiece * 2);
                bar(startX + j * BLOCK, startY + i * BLOCK,
                    startX + (j + 1) * BLOCK, startY + (i + 1) * BLOCK);
                setcolor(WHITE);
                rectangle(startX + j * BLOCK, startY + i * BLOCK,
                          startX + (j + 1) * BLOCK, startY + (i + 1) * BLOCK);
            }
}

void hardDrop()
{
    while (!collision(0, 1, rotation))
        posY++;
    placePiece();
    clearLines();
    newPiece();
}

void pauseGame()
{
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setcolor(YELLOW);
    outtextxy(120, 200, "PAUSED");
    outtextxy(80, 250, "Press P to Resume");
    while (1)
    {
        char k = getch();
        if (k == 'p' || k == 'P')
            break;
    }
}

void drawScore()
{
    char s[50];
    int offsetX = W * BLOCK + 100;
    int offsetY = 200;
    sprintf(s, "Score:%d", score);
    outtextxy(offsetX, offsetY, s);
    sprintf(s, "Level:%d", level);
    outtextxy(offsetX, offsetY + 20, s);
    sprintf(s, "Lines:%d", lines);
    outtextxy(offsetX, offsetY + 40, s);
}

void gameLoop()
{
    int counter = 0;
    while (1)
    {
        if (kbhit())
        {
            char k = getch();
            if (k == 0 || k == 224)
            {
                char arrow = getch();
                if (arrow == 75 && !collision(-1, 0, rotation))
                    posX--;
                if (arrow == 77 && !collision(1, 0, rotation))
                    posX++;
                if (arrow == 72 && !collision(0, 0, (rotation + 1) % 4))
                    rotation = (rotation + 1) % 4;
                if (arrow == 80 && !collision(0, 1, rotation))
                    posY++;
            }
            else
            {
                if (k == ' ')
                    hardDrop();
                if (k == 'p' || k == 'P')
                    pauseGame();
            }
        }
        if (++counter > speed)
        {
            counter = 0;
            if (collision(0, 1, rotation))
            {
                placePiece();
                clearLines();
                newPiece();
            }
            else
                posY++;
        }
        drawBoard();
        drawGhostPiece();
        drawPiece();
        drawNextPiece();
        drawScore();
        delay(30);
    }
}

//---------Difficulty Menu Options---------------------
void difficultyMenu()
{
    cleardevice();
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(180, 120, "SELECT LEVEL");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(220, 220, "1 EASY");
    outtextxy(220, 260, "2 MEDIUM");
    outtextxy(220, 300, "3 HARD");
    char k;
    while (1)
    {
        k = getch();
        if (k == '1')
        {
            baseSpeed = 50;
            break;
        }
        if (k == '2')
        {
            baseSpeed = 35;
            break;
        }
        if (k == '3')
        {
            baseSpeed = 22;
            break;
        }
    }
    speed = baseSpeed;
}

//---------Main Menu Options-------------
void menu()
{
    cleardevice();
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(200, 120, "TETRIS");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(220, 220, "1 START GAME");
    outtextxy(220, 260, "2 EXIT");
}

int main()
{
    int gd = DETECT, gm;
    srand(time(0));
    initgraph(&gd, &gm, "");
    nextPiece = rand() % 7;
    while (1)
    {
        menu();
        char k = getch();
        if (k == '1')
        {
            difficultyMenu();
            clearBoard();
            newPiece();
            gameLoop();
        }
        if (k == '2')
            break;
    }
    closegraph();
    return 0;
}