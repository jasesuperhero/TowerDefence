//
//  CAbstractEnemy.h
//  HelloCpp
//
//  Created by Daniel on 07.11.13.
//
//

#ifndef __HelloCpp__CAbstractEnemy__
#define __HelloCpp__CAbstractEnemy__

// Библиотеки
#include <cocos2d.h>
// Кастомные
#include "CAbstractAttacedUnit.h"
#include "CRoad.h"

class CAbstractEnemy : public CAbstractAttacedUnit
{
protected:
    int _moveSpeed;
    bool _inMoving;
    CRoad* _road;
    
    /** Графические поля */
    RepeatForever* _moveUp;
    RepeatForever* _moveDown;
    RepeatForever* _moveLeft;
    RepeatForever* _moveRight;
    
public:
    /** Конструкторы */
    CAbstractEnemy();
    
    /** GET методы */
    int getMoveSpeed();
    bool getInMoving();
    CRoad* getRoad();
    
    RepeatForever* getMoveUpAction();
    RepeatForever* getMoveDownAction();
    RepeatForever* getMoveLeftAction();
    RepeatForever* getMoveRightAction();
    
    /** SET методы */
    CAbstractEnemy& setMoveSpeed(int new_move_speed);
    CAbstractEnemy& setInMoving(bool new_in_moving);
    CAbstractEnemy& setRoad(CRoad* new_road);
    CAbstractEnemy& setMoveUpAction(RepeatForever* new_move_up);
    CAbstractEnemy& setMoveDownAction(RepeatForever* new_move_down);
    CAbstractEnemy& setMoveLeftAction(RepeatForever* new_move_left);
    CAbstractEnemy& setMoveRightAction(RepeatForever* new_move_right);
    
    /** Дополнительные методы */
    static RepeatForever* createMoveAnimateAction(const char* filename, Rect startRect, int count);
    virtual void makeMove() = 0;
};

#endif /* defined(__HelloCpp__CAbstractEnemy__) */
