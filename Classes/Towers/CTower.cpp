//
//  CTower.cpp
//  HelloCpp
//
//  Created by Daniel on 07.11.13.
//
//

#include "CTower.h"

// Характеристики башни
#define STANDART_DAMAGE 100
#define STANDART_RATE 3
#define STANDART_HEALTH 10000
#define STANDART_DAMAGE_RADIUS 100
#define STANDART_NAME (char*)"Tower"

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CTower::CTower()
{
    _level = 1;
    _experience = 0;
}

#pragma mark - GET методы

/*
 *  Возвращает текущий уровень
 */
int CTower::getLevel()
{
    return _level;
}

/*
 *  Возвращает текущий опыт
 */
int CTower::getExperience()
{
    return _experience;
}

#pragma mark - SET методы

/*
 *  Устанавливает текущий уровень
 */
CTower& CTower::setLevel(int new_level)
{
    _level = new_level;
    return *this;
}

/*
 *  Устанавливает текущий опыт
 */
CTower& CTower::setExperience(int new_experience)
{
    _experience = new_experience;
    return *this;
}

#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CTower::init()
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
    setSpriteWithRect("turret.png", Rect(0, 0, 32, 32));
    this->addChild(_sprite);
    
    // настройка отображения имени объекта
    _unit_name->initWithString(_name, "Calibri", 12);
    
    // Запуск основного цикла
    this->getScheduler()->scheduleUpdateForTarget(this, this->getZOrder(), false);
    
    return true;
}

#pragma mark - Пользовательский ввод

/*
 *  Делегированный метод для обработки начала касания экрана
 */
bool CTower::onTouchBegan(Touch *touch, Event *event)
{
    if (isClicked(touch)) {
        printf("Tower was touch\n");
        return true;
    }
    return false;
}

#pragma mark - Дополнительные методы
#pragma mark - PRIVAT

/*
 *  Повышение уровня
 */
void CTower::levelUp()
{
    _level++;
}

/*
 *  Обновление объекта со временем
 */
void CTower::update(float dt)
{
    
}