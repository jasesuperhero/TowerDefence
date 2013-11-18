//
//  CLightEnemy.cpp
//  HelloCpp
//
//  Created by Daniel on 08.11.13.
//
//

#include "CLightEnemy.h"

#define STANDART_DAMAGE 100
#define STANDART_RATE 3
#define STANDART_HEALTH 10000
#define STANDART_DAMAGE_RADIUS 100
#define STANDART_MOVE_SPEED 1
#define STANDART_NAME (char*)"Light Unit"

#pragma mark - Дополнительные методы

/*
 *  Обновление объекта со временем
 */
void CLightEnemy::update(float dt)
{
    if (!_road->getPath() || !_road->checkPath())
        getRoad()->findPath(getTiledCoord());
    
    if (getRoad()->getPath() && !getRoad()->getPath()->empty() && !getInMoving())
        makeMove();
}

/*
 *  Передвижение TODO: Доделать метод передвижения
 */
void CLightEnemy::makeMove()
{
    CRoad* road = getRoad();
    if (road->checkPath()) {
        Point dir_point = getPositionWithTiledCoord((*road->getPath())[road->getPath()->size() - 1]);
        printf("Next position for unit is X = %f Y = %f \n", dir_point.x, dir_point.y);
        road->getPath()->pop_back();
        
        FiniteTimeAction* sequence = Sequence::create(MoveTo::create(1 / getMoveSpeed(), dir_point),
                                                      CallFunc::create(this, callfunc_selector(CLightEnemy::makeMove)),
                                                      NULL);
        sequence->retain();
        this->runAction(sequence);
        
        this->_sprite->stopAllActions();
        
        if (dir_point.x - getPosition().x > 0) {
            //_moveRight->retain();
            this->_sprite->runAction(_moveRight);
        }
        
        if (dir_point.x - getPosition().x < 0) {
            //_moveLeft->retain();
            this->_sprite->runAction(_moveLeft);
        }
        
        if (dir_point.y - getPosition().y > 0) {
            //_moveUp->retain();
            this->_sprite->runAction(_moveUp);
        }
        
        if (dir_point.y - getPosition().y < 0) {
            //_moveDown->retain();
            this->_sprite->runAction(_moveDown);
        }
        
        setInMoving(true);
    } else setInMoving(false);
}

#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CLightEnemy::init()
{
    if ( !CAbstractUnit::init() )
    {
        return false;
    }
    
    // Настройка объекта
    setName(STANDART_NAME);
    setHealth(STANDART_HEALTH);
    setMaxHealth(STANDART_HEALTH);
    setMaxDamage(STANDART_DAMAGE);
    setDamageRadius(STANDART_DAMAGE_RADIUS);
    setRate(STANDART_RATE);
    setMoveSpeed(STANDART_MOVE_SPEED);
    
    // настройка спрайта
    setSpriteWithRect("light_unit.png", Rect(0, 0, 32, 32));
    this->addChild(_sprite);
    
    // настройка отображения имени объекта
    _unit_name->initWithString(_name, "Calibri", 12);
    
    // Отлавливание касания экрана
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CLightEnemy::onTouchBegan, this);
    EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
    this->setTouchEnabled(true);
    
    // Запуск основного цикла
    this->getScheduler()->scheduleUpdateForTarget(this, 1, false);
    
    // Устанавливаем размер слоя
    this->setContentSize(Size(32, 32));
    
    // Загрузка фреймов для анимации
    _moveUp = CAbstractEnemy::createMoveAnimateAction("light_unit.png", Rect(0, 4 * 32, 32, 32), 6);
    _moveDown = CAbstractEnemy::createMoveAnimateAction("light_unit.png", Rect(0, 0, 32, 32), 6);
    _moveLeft = CAbstractEnemy::createMoveAnimateAction("light_unit.png", Rect(0, 2 * 32, 32, 32), 6);
    _moveRight = CAbstractEnemy::createMoveAnimateAction("light_unit.png", Rect(0, 6 * 32, 32, 32), 6);
    
    return true;
}

/*
 *  Метод создания юнита с привязкой к дороге и замку
 */
CLightEnemy* CLightEnemy::createEnemyWithRoadAndCastleCoord(TMXLayer *road, Point castleCoord)
{
    CLightEnemy* enemy = CLightEnemy::create();
    CRoad* new_road = CRoad::createWithLayerAndCastleCoord(road, castleCoord);
    enemy->setRoad(new_road);
    return enemy;
}

#pragma mark - Пользовательский ввод

/*
 *  Делегированный метод для обработки начала касания экрана
 */
bool CLightEnemy::onTouchBegan(Touch *touch, Event *event)
{
    if (isClicked(touch)) {
        printf("%s was touch\n", this->getName());
        getDemaged(1000);
        return true;
    }
    return false;
}
