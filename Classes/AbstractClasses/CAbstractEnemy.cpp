//
//  CAbstractEnemy.cpp
//  HelloCpp
//
//  Created by Daniel on 07.11.13.
//
//

#include "CAbstractEnemy.h"
#include "CWall.h"
#include "CLandscape.h"

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
 *  Возвращает указатель на массив стен
 */
vector<CWall*>* CAbstractEnemy::getWalls()
{
    return _walls;
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
 *  Установка нового указатели на массив дороги
 */
CAbstractEnemy& CAbstractEnemy::setWalls(vector<CWall*> *new_walls)
{
    if (new_walls == NULL) throw "New walls ptr is NULL";
    _walls = new_walls;
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

#pragma mark - Перегруженные методы

/*
 *  Убит ли атакуемый юнит
 */
void CAbstractEnemy::isKillEnemy()
{
    makeDamageTo();
}

#pragma mark - Дополнительные методы
#pragma mark - PRIVATE

/*
 *  Обновление объекта со временем
 */
void CAbstractEnemy::update(float dt)
{
    setZOrder(getLandscape()->getContentSize().height - getPositionY());
    
    if (getAlive()) {
        // Если дошли до площади замка, то просто исчезаем и наносим мнимый урон замку
        if (getTiledCoord().x == getRoad()->getCastleCoord().x &&
            getTiledCoord().y == getRoad()->getCastleCoord().y) {
            
            // TODO: урон замку
            
            return;
        }
        
        // Поиск маршрута
        if (!getRoad()->getPath() || !getRoad()->checkPath())
            if (!this->getActionByTag(MOVING_TAG) || (this->getActionByTag(MOVING_TAG) && this->getActionByTag(MOVING_TAG)->isDone())) {
                getRoad()->findPath(getTiledCoord());
                this->stopActionByTag(MOVING_TAG);
                this->getSprite()->stopActionByTag(MOVING_ANIMATION_TAG);
                makeMove();
            }
        
        // Атака помехи или замка
        if (!getAttacedUnit() || !getAttacedUnit()->getAlive()) {
            vector<CWall*>* wallsArray = getWalls();
            for (int i = 0; i < getWalls()->size(); i++)
                if (getPosition().getDistance((*wallsArray)[i]->getPosition()) < getDamageRadius()) {
                    setAttacedUnit((*wallsArray)[i]);
                    attack();
                    return;
                }
        }
    }
}

#pragma mark - PUBLIC

/*
 *  Передвижение
 */
void CAbstractEnemy::makeMove()
{
    CRoad* road = getRoad();
    if (road->checkPath() && getAlive()) {
        Point dir_point = getPositionWithTiledCoord((*road->getPath())[road->getPath()->size() - 1]);
        //printf("Next position for unit is X = %f Y = %f \n", dir_point.x, dir_point.y);
        road->getPath()->pop_back();
        
        FiniteTimeAction* move = Sequence::create(MoveTo::create(1 * (getPosition().getDistance(dir_point) / 32) / getMoveSpeed(), dir_point),
                                                  CallFunc::create(this, callfunc_selector(CAbstractEnemy::makeMove)),
                                                  NULL);
        move->setTag(MOVING_TAG);
        move->retain();
        this->runAction(move);
        
        this->_sprite->stopActionByTag(MOVING_ANIMATION_TAG);
        
        if (dir_point.x - getPosition().x > 0)
            this->_sprite->runAction(_moveRight);
        if (dir_point.x - getPosition().x < 0)
            this->_sprite->runAction(_moveLeft);
        if (dir_point.y - getPosition().y > 0)
            this->_sprite->runAction(_moveUp);
        if (dir_point.y - getPosition().y < 0)
            this->_sprite->runAction(_moveDown);
    };
}

#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CAbstractEnemy::init()
{
    if ( !CAbstractUnit::init() )
    {
        return false;
    }
    
    // Запуск основного цикла
    this->getScheduler()->scheduleUpdateForTarget(this, this->getZOrder(), false);
    
    return true;
}
