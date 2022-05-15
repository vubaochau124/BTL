#include "Board.h"

Board::Board(){

}

Board::~Board(){

}

void Board::Reset(){
    for (int i = 0; i < BOARD_WIDTH; i ++)
        for (int j = 0; j < BOARD_HEIGHT; j ++)
            board[i][j] = FREE;
}

void Board::Init(){
    board[2][2] = board[2][3] = board[2][4] = SNAKE;
}

void Board::Update(int checkType){
    pair<int, int> head = snake.GetHeadPos();
    pair<int, int> tail = snake.GetTailPos();

    board[head.second][head.first] = SNAKE;
    if(checkType != 2)
        board[tail.second][tail.first] = FREE;
}

void Board::Move(int moveType){
    int checkType = MoveCheck(moveType);
    if(checkType)
        snake.Move(moveType),
        Update(checkType);
}

void Board::ForceMove(){
    snake.ForceMove();
}

int Board::MoveCheck(int moveType){
    pair<int, int> head = snake.GetHeadPos();
    int dir = snake.GetDirection();

    if(abs(moveType - dir) == 2)
        return 0; // opposite direction
    if(dir == UP)
        head.second --;
    if(dir == DOWN)
        head.second ++;
    if(dir == LEFT)
        head.first --;
    if(dir == RIGHT)
        head.first ++;
    
    if(board[head.second][head.first] == SNAKE)
        return 1; // body hit
    if(board[head.second][head.first] == WALL)
        return 2; // wall hit
    if(board[head.second][head.first] == FOOD)
        return 3; // growth
    
    return 4; // hit nothing
}

void Board::SpawnFood(){
    bool rng = true;
    int x, y;
    while(rng){
        x = rand() % BOARD_WIDTH;
        y = rand() % BOARD_HEIGHT;

        if(board[x][y] == FREE){
            board[x][y] = FOOD;
            food = {x, y};
            rng = false;
        }
    }
}

void Board::DrawBoard(SDL_Renderer *renderer){
    boardTex.Render(renderer, 0, 0, &boardTexClip);
    playField.Render(renderer, 64, 64, &playFieldClip);
    snake.Draw(renderer);
}

void Board::TextureInit(SDL_Renderer* renderer){
    boardTex.LoadTextureFromFile("images/play_board.png", renderer);
    playField.LoadTextureFromFile("images/play_field.png", renderer);
    snake.Init(renderer);
}