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
    setAlive(false);
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
 *  Возвращает количество опыта за юнита
 */
int CAbstractEnemy::getExp()
{
    return _exp;
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
    if (new_road == NULL) throw "New road is NULL ptr";
    _road = new_road;
    return *this;
}

/*
 *  Установка нового значения опыта за юнита
 */
CAbstractEnemy& CAbstractEnemy::setExp(int new_exp)
{
    if (new_exp <= 0) throw "New exp is 0 or less than 0";
    _exp = new_exp;
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

#pragma mark - Дополнительные методы

/*
 *  Передвижение
 */
void CAbstractEnemy::makeMove()
{
    CRoad* road = getRoad();
    if (road->checkPath() && getAlive()) {
        Point dir_point = getPositionWithTiledCoord((*road->getPath())[road->getPath()->size() - 1]);
        printf("Next position for unit is X = %f Y = %f \n", dir_point.x, dir_point.y);
        road->getPath()->pop_back();
        
        FiniteTimeAction* sequence = Sequence::create(MoveTo::create(1 / getMoveSpeed(), dir_point),
                                                      CallFunc::create(this, callfunc_selector(CAbstractEnemy::makeMove)),
                                                      NULL);
        sequence->retain();
        this->runAction(sequence);
        
        this->_sprite->stopAllActions();
        
        if (dir_point.x - getPosition().x > 0)
            this->_sprite->runAction(_moveRight);
        if (dir_point.x - getPosition().x < 0)
            this->_sprite->runAction(_moveLeft);
        if (dir_point.y - getPosition().y > 0)
            this->_sprite->runAction(_moveUp);
        if (dir_point.y - getPosition().y < 0)
            this->_sprite->runAction(_moveDown);
        
        setInMoving(true);
    } else setInMoving(false);
}

