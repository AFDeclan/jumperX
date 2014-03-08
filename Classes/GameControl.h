//
//  GameControl.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__GameControl__
#define __jumper_x__GameControl__

#include <iostream>

typedef enum GameStatus {
    On = 0,
    Pause = 1,
    Over = 2
} GameStatus;

class GameControl {
public:
    static void startGame();
    static void overGame();
    static void pauseGame();
    static void resumeGame();
    
    static GameStatus getGameStatus();
private:
    static GameStatus _gameStatus;
};

#endif /* defined(__jumper_x__GameControl__) */
