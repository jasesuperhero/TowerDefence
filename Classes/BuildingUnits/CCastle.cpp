//
//  CCastle.cpp
//  HelloCpp
//
//  Created by Daniel on 09.11.13.
//
//

#include "CCastle.h"

#define STANDART_DAMAGE 100
#define STANDART_RATE 3
#define STANDART_HEALTH 10000
#define STANDART_DAMAGE_RADIUS 100
#define STANDART_NAME (char*)"Castle"

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CCastle::CCastle()
{
    _money = 0;
}

#pragma mark - GET методы

/*
 *  Возвращает текущее количество золота в замке
 */
int CCastle::getMoney()
{
    return _money;
}

#pragma mark - SET методы

/*
 *  Устанавливает текущее количество золота в замке
 */
CCastle& CCastle::setMoney(int new_money)
{
    if (new_money > 0) _money = new_money;
    return *this;
}

#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CCastle::init()
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
    
    // настройка спрайта
    setSpriteWithRect("tmw_desert_spacing.png", Rect(1, 4 * 32 + 5, 32, 32));
    this->addChild(_sprite);
    
    // настройка отображения имени объекта
    _unit_name->initWithString(_name, "Calibri", 12);
    
    // Создаем игровой цикл для объекта
    //this->getScheduler()->scheduleSelector(schedule_selector(CWall::update), this, 10, false);
    this->getScheduler()->scheduleUpdateForTarget(this, 1, false);
    
    return true;
}

#pragma mark - Пользовательский ввод

/*
 *  Делегированный метод для обработки начала касания экрана
 */
bool CCastle::onTouchBegan(Touch *touch, Event *event)
{
    if (isClicked(touch)) {
        printf("Castle was touch\n");
        return true;
    }
    return false;
}
