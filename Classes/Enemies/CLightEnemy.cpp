//
//  CLightEnemy.cpp
//  HelloCpp
//
//  Created by Daniel on 08.11.13.
//
//

#include "CLightEnemy.h"
#include "CLandscape.h"

#define STANDART_DAMAGE 100
#define STANDART_RATE 3
#define STANDART_HEALTH 10000
#define STANDART_DAMAGE_RADIUS 100
#define STANDART_MOVE_SPEED 1
#define STANDART_EXP 300
#define STANDART_NAME (char*)"Light Unit"

#pragma mark - Дополнительные методы

/*
 *  Обновление объекта со временем
 */
void CLightEnemy::update(float dt)
{
    if (getAlive()) {
        if (!getRoad()->getPath() || !getRoad()->checkPath())
            getRoad()->findPath(getTiledCoord());
        
        if (getRoad()->getPath() && !getRoad()->getPath()->empty() && !getInMoving())
            makeMove();
    }
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
    setExp(STANDART_EXP);
    
    // настройка спрайта
    setSpriteWithRect("light_unit.png", Rect(0, 0, 32, 32));
    
    // Отлавливание касания экрана
    /*auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CLightEnemy::onTouchBegan, this);
    EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
    this->setTouchEnabled(true);*/
    
    // Запуск основного цикла
    this->getScheduler()->scheduleUpdateForTarget(this, this->getZOrder(), false);
    
    // Устанавливаем размер слоя
    this->setContentSize(Size(32, 32));
    
    // Загрузка фреймов для анимации движения
    _moveUp = RepeatForever::create(CAbstractUnit::createAnimate("light_unit.png", Rect(0, 4 * 32, 32, 32), 6, 0.1));
    _moveUp->retain();
    _moveDown = RepeatForever::create(CAbstractUnit::createAnimate("light_unit.png", Rect(0, 0, 32, 32), 6, 0.1));
    _moveDown->retain();
    _moveLeft = RepeatForever::create(CAbstractUnit::createAnimate("light_unit.png", Rect(0, 2 * 32, 32, 32), 6, 0.1));
    _moveLeft->retain();
    _moveRight = RepeatForever::create(CAbstractUnit::createAnimate("light_unit.png", Rect(0, 6 * 32, 32, 32), 6, 0.1));
    _moveRight->retain();
    
    // Загрузка анимации смерти
    for (int i = 2; i < 8; i++) {
        SpriteFrame* frame = SpriteFrame::create("fx_enemydie_tiny_32.png", Rect(i * 32, 0, 32, 32));
        getDeadAnimation()->addSpriteFrame(frame);
    }
    getDeadAnimation()->setDelayPerUnit(0.1);
    
    return true;
}

/*
 *  Метод создания юнита с привязкой к дороге и замку
 */
CLightEnemy* CLightEnemy::createEnemy(CLandscape *landscape)
{
    CLightEnemy* enemy = CLightEnemy::create();
    enemy->setLandscape(landscape);
    enemy->setRoad(CRoad::createWithLayerAndCastleCoord(landscape->getLayer("Road"), landscape->getCastleCoord()));
    return enemy;
}

#pragma mark - Пользовательский ввод

/*
 *  Делегированный метод для обработки начала касания экрана
 */
bool CLightEnemy::onTouchBegan(Touch *touch, Event *event)
{
    if (isClicked(touch) && getAlive()) {
        printf("%s was touch\n", this->getName());
        setAlive(!getAlive());
        return true;
    }
    return false;
}
