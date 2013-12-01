//
//  CAbstractEnemy.h
//  HelloCpp
//
//  Created by Daniel on 07.11.13.
//
//

#ifndef __HelloCpp__CAbstractEnemy__
#define __HelloCpp__CAbstractEnemy__

// Константы
#define MOVING_TAG 222
#define MOVING_ANIMATION_TAG 333

// Кастомные
#include "CAbstractAttacedUnit.h"
#include "CRoad.h"

class CWall;

class CLandscape;

class CAbstractEnemy : public CAbstractAttacedUnit
{
protected:
    int _moveSpeed;
    bool _inMoving;
    CRoad* _road;
    int _exp;
    
    vector<CWall*>* _walls;
    
    /** Графические поля */
    RepeatForever* _moveUp;
    RepeatForever* _moveDown;
    RepeatForever* _moveLeft;
    RepeatForever* _moveRight;
    
    /** Дополнительные методы */
    virtual void update(float dt);
    
public:
    /** Конструкторы */
    CAbstractEnemy();
    
    /** GET методы */
    int getMoveSpeed();
    bool getInMoving();
    CRoad* getRoad();
    int getExp();
    vector<CWall*> *getWalls();
    
    RepeatForever* getMoveUpAction();
    RepeatForever* getMoveDownAction();
    RepeatForever* getMoveLeftAction();
    RepeatForever* getMoveRightAction();
    
    /** SET методы */
    CAbstractEnemy& setMoveSpeed(int new_move_speed);
    CAbstractEnemy& setInMoving(bool new_in_moving);
    CAbstractEnemy& setRoad(CRoad* new_road);
    CAbstractEnemy& setExp(int new_exp);
    CAbstractEnemy& setWalls(vector<CWall*>* new_walls);
    
    CAbstractEnemy& setMoveUpAction(RepeatForever* new_move_up);
    CAbstractEnemy& setMoveDownAction(RepeatForever* new_move_down);
    CAbstractEnemy& setMoveLeftAction(RepeatForever* new_move_left);
    CAbstractEnemy& setMoveRightAction(RepeatForever* new_move_right);
    
    /** Переружаемые методы */
    virtual void isKillEnemy();
    
    /** Дополнительные методы */
    void makeMove();
    
    /** Инициализация */
    virtual bool init();
};

#endif /* defined(__HelloCpp__CAbstractEnemy__) */
