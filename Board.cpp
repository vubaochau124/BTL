#include "Board.h"

void Board::Reset(){
    for (int i = 0; i < BOARD_WIDTH; i ++)
        for (int j = 0; j < BOARD_HEIGHT; j ++)
            board[i][j] = FREE;
}

void Board::Init(){
    board[2][2] = board[2][3] = board[2][4] = SNAKE;
    SpawnFood();
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
    if(checkType){
        snake.Move(moveType);
        Update(checkType);
    }
    else if(checkType == 2){
        snake.Move(moveType);
        Update(checkType);
        snake.Growth();
        SpawnFood();
    }
}

void Board::ForceMove(){
    int checkType = MoveCheck(snake.GetDirection());
    if(checkType == 2){
        snake.ForceMove();
        Update(checkType);
        snake.Growth();
        SpawnFood();
    }
    else if(checkType){
        snake.ForceMove();
        Update(checkType);
    }
}

int Board::MoveCheck(int moveType){
    pair<int, int> head = snake.GetHeadPos();
    int dir = snake.GetDirection();

    if(abs(moveType - dir) == 2)
        return 0; // opposite direction
    if(moveType == UP)
        head.second --;
    if(moveType == DOWN)
        head.second ++;
    if(moveType == LEFT)
        head.first --;
    if(moveType == RIGHT)
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
    foodTex.Render(renderer, BOARD_X + food.second * 32, 
                             BOARD_Y + food.first  * 32, &foodTexClip);
    snake.Draw(renderer);

    // for(int i = 0; i < BOARD_WIDTH; i ++){
    //     for(int j = 0; j < BOARD_HEIGHT; j ++)
    //         cerr << board[i][j];
    //     cerr << '\n';
    // }
    // cerr << '\n';
}

void Board::TextureInit(SDL_Renderer* renderer){
    boardTex.LoadTextureFromFile("images/play_board.png", renderer);
    playField.LoadTextureFromFile("images/play_field.png", renderer);
    foodTex.LoadTextureFromFile("images/food.png", renderer);
    snake.Init(renderer);
}

Board::Board(){

}

Board::~Board(){
    boardTex.FreeTexture();
    playField.FreeTexture();
    foodTex.FreeTexture();
}