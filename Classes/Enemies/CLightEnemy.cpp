//
//  CLightEnemy.cpp
//  HelloCpp
//
//  Created by Daniel on 08.11.13.
//
//

#include "CLightEnemy.h"
#include "CLandscape.h"
#include "CFire.h"

#define STANDART_DAMAGE 100
#define STANDART_RATE 3
#define STANDART_HEALTH 10000
#define STANDART_DAMAGE_RADIUS 100
#define STANDART_MOVE_SPEED 1
#define STANDART_EXP 300
#define STANDART_COST 100
#define STANDART_NAME (char*)"Light Unit"

#pragma mark - Перегруженные методы

/*
 *  Анимация и экшн атаки
 */
void CLightEnemy::attackAnimation()
{
    CFire* fire = CFire::create();
    fire->cocos2d::Node::setPosition(this->getPosition());
    FiniteTimeAction* sequence = Sequence::create(MoveTo::create(0.3, getAttacedUnit()->getPosition()),
                                                  CallFunc::create(this, callfunc_selector(CLightEnemy::isKillEnemy)),
                                                  CallFunc::create(fire, callfunc_selector(Node::removeFromParent)),
                                                  NULL);
    this->getParent()->addChild(fire, 1);
    fire->runAction(sequence);
}

#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CLightEnemy::init()
{
    if ( !CAbstractEnemy::init() )
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
    setCost(STANDART_COST);
    
    // настройка спрайта
    setSpriteWithRect("light_unit.png", Rect(0, 0, 32, 32));
    
    // Устанавливаем размер слоя
    this->setContentSize(Size(32, 32));
    
    // Загрузка фреймов для анимации движения
    _moveUp = RepeatForever::create(CAbstractUnit::createAnimate("light_unit.png", Rect(0, 4 * 32, 32, 32), 6, 0.1));
    _moveUp->setTag(MOVING_ANIMATION_TAG);
    _moveUp->retain();
    _moveDown = RepeatForever::create(CAbstractUnit::createAnimate("light_unit.png", Rect(0, 0, 32, 32), 6, 0.1));
    _moveDown->setTag(MOVING_ANIMATION_TAG);
    _moveDown->retain();
    _moveLeft = RepeatForever::create(CAbstractUnit::createAnimate("light_unit.png", Rect(0, 2 * 32, 32, 32), 6, 0.1));
    _moveLeft->setTag(MOVING_ANIMATION_TAG);
    _moveLeft->retain();
    _moveRight = RepeatForever::create(CAbstractUnit::createAnimate("light_unit.png", Rect(0, 6 * 32, 32, 32), 6, 0.1));
    _moveRight->setTag(MOVING_ANIMATION_TAG);
    _moveRight->retain();
    
    // Загрузка анимации смерти
    setDeadAnimation(CAbstractUnit::createAnimate("fx_enemydie_tiny_32.png", Rect(32, 0, 32, 32), 7, 0.1));
    
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
    enemy->setWalls(landscape->getWalls());
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
