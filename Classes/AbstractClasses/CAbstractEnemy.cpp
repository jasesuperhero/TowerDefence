//
//  CAbstractEnemy.cpp
//  HelloCpp
//
//  Created by Daniel on 07.11.13.
//
//

#include "CAbstractEnemy.h"

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CAbstractEnemy::CAbstractEnemy()
{
    _moveSpeed = 10;
    _road = NULL;
}

#pragma mark - GET методы

/*
 *  Возвращает скорость передвижения
 */
int CAbstractEnemy::getMoveSpeed()
{
    return _moveSpeed;
}

/*
 *  Возвращает состояние передвижения объекта
 */
bool CAbstractEnemy::getInMoving()
{
    return _inMoving;
}

/*
 *  Возвращает текущую дорогу для объекта
 */
CRoad* CAbstractEnemy::getRoad()
{
    return _road;
}

/*
 *  Возвращает action прозода вверх по карте
 */
RepeatForever* CAbstractEnemy::getMoveUpAction()
{
    return _moveUp;
}

/*
 *  Возвращает action прозода вниз по карте
 */
RepeatForever* CAbstractEnemy::getMoveDownAction()
{
    return _moveDown;
}

/*
 *  Возвращает action прозода влево по карте
 */
RepeatForever* CAbstractEnemy::getMoveLeftAction()
{
    return _moveLeft;
}

/*
 *  Возвращает action прозода вправо по карте
 */
RepeatForever* CAbstractEnemy::getMoveRightAction()
{
    return _moveRight;
}


#pragma mark - SET методы

/*
 *  Устанавливает скорость передвижения
 */
CAbstractEnemy& CAbstractEnemy::setMoveSpeed(int new_move_speed)
{
    if (new_move_speed > 0) _moveSpeed = new_move_speed;
    return *this;
}

/*
 *  Устанавливает состояние передвижения объекта
 */
CAbstractEnemy& CAbstractEnemy::setInMoving(bool new_in_moving)
{
    if (new_in_moving != _inMoving) {
        _inMoving = new_in_moving;
    }
    return *this;
}

/*
 *  Устанавливает текущую дорогу для объекта
 */
CAbstractEnemy& CAbstractEnemy::setRoad(CRoad *new_road)
{
    _road = new_road;
    return *this;
}

/*
 *  Устанавливает action для движение вверх
 */
CAbstractEnemy& CAbstractEnemy::setMoveUpAction(RepeatForever *new_move_up)
{
    if (!new_move_up) throw "Error! NULL ptr to action! \n";
    _moveUp = new_move_up;
    return *this;
}

/*
 *  Устанавливает action для движение вниз
 */
CAbstractEnemy& CAbstractEnemy::setMoveDownAction(RepeatForever *new_move_down)
{
    if (!new_move_down) throw "Error! NULL ptr to action! \n";
    _moveUp = new_move_down;
    return *this;
}

/*
 *  Устанавливает action для движение влево
 */
CAbstractEnemy& CAbstractEnemy::setMoveLeftAction(RepeatForever *new_move_left)
{
    if (!new_move_left) throw "Error! NULL ptr to action! \n";
    _moveUp = new_move_left;
    return *this;
}

/*
 *  Устанавливает action для движение вправо
 */
CAbstractEnemy& CAbstractEnemy::setMoveRightAction(RepeatForever *new_move_right)
{
    if (!new_move_right) throw "Error! NULL ptr to action! \n";
    _moveUp = new_move_right;
    return *this;
}

/*
 *  Создание action анимации по файлу, начальной области и количеству фреймов
 */
RepeatForever* CAbstractEnemy::createMoveAnimateAction(const char *filename, cocos2d::Rect startRect, int count)
{
    Animation* animation = Animation::create();
    for(int i = 0; i < count; i++) {
        SpriteFrame* frame = SpriteFrame::create(filename, startRect);
        startRect.origin.x += startRect.size.height;
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(0.1);
    RepeatForever* moveAnimate = RepeatForever::create(Animate::create(animation));
    moveAnimate->retain();
    return moveAnimate;
}

