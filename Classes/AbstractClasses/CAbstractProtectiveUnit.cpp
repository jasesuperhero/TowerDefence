//
//  CAbstractProtectiveUnit.cpp
//  HelloCpp
//
//  Created by Daniel on 05.11.13.
//
//

#include "CAbstractProtectiveUnit.h"

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CAbstractProtectiveUnit::CAbstractProtectiveUnit()
{
    _health = 10;
    _maxHealth = 100;
}

#pragma mark - GET методы

/*
 *  Возвращает количество здоровья юнита
 */
int CAbstractProtectiveUnit::getHealth()
{
    return _health;
}

/*
 *  Возвращает максимальный запас здоровья
 */
int CAbstractProtectiveUnit::getMaxHealth()
{
    return _maxHealth;
}

/*
 *  Возвращает состояние юнита
 */
bool CAbstractProtectiveUnit::getAlive()
{
    return alive;
}

#pragma mark - SET методы

#pragma mark - PRIVATE

/*
 *  Устанавливаем значение для alive
 */
CAbstractProtectiveUnit& CAbstractProtectiveUnit::setAlive(bool new_alive)
{
    alive = new_alive;
    return *this;
}

#pragma mark - PUBLIC

/*
 *  Устанавливаем текущий уровень здоровья
 */
CAbstractProtectiveUnit& CAbstractProtectiveUnit::setHealth(int new_health)
{
    _health = new_health;
    return *this;
}

/*
 *  Устанавливаем максимальный уровень здоровья
 */
CAbstractProtectiveUnit& CAbstractProtectiveUnit::setMaxHealth(int new_max_health)
{
    _maxHealth = new_max_health;
    return *this;
}

#pragma mark - Дополнительные методы

/*
 *  Юнит получает урон. Возвращает true, если юнит умер, и false, если еще жив
 */
bool CAbstractProtectiveUnit::getDemaged(int damage)
{
    _health -= damage;
    if (_health > 0) {
        this->removeChild(_unitHealthSprite);
        _unitHealthSprite = _unitHealthAnimation[int(_health * 21 / _maxHealth)];
        this->addChild(_unitHealthSprite);
        return true;
    } else return (_health > 0);
}

