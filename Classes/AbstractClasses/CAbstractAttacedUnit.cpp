//
//  CAbstractAttacedUnit.cpp
//  HelloCpp
//
//  Created by Daniel on 07.11.13.
//
//

#include "CAbstractAttacedUnit.h"

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CAbstractAttacedUnit::CAbstractAttacedUnit()
{
    _maxDamage = 100;
    _rate = 10;
    _damageRadius = 10;
}

#pragma mark - GET методы

/*
 *  Возвращает максимальный урон юнита
 */
int CAbstractAttacedUnit::getMaxDamage()
{
    return _maxDamage;
}

/*
 *  Возвращает количество ударов в секунду юнита
 */
int CAbstractAttacedUnit::getRate()
{
    return _rate;
}

/*
 *  Возвращает радиус атаки
 */
int CAbstractAttacedUnit::getDamageRadius()
{
    return _damageRadius;
}

/*
 *  Возвращает юнита акауемого данным
 */
CAbstractProtectiveUnit* CAbstractAttacedUnit::getAttacedUnit()
{
    return _attacedUnit;
}

#pragma mark - SET методы

/*
 *  Устанавлливает новое значения для максимального урона юнита
 */
CAbstractAttacedUnit& CAbstractAttacedUnit::setMaxDamage(int new_max_damage)
{
    if (new_max_damage > 0)
        _maxDamage = new_max_damage;
    return *this;
}

/*
 *  Устанавлливает новое значения для скорости атаки юнита
 */
CAbstractAttacedUnit& CAbstractAttacedUnit::setRate(int new_rate)
{
    if (new_rate > 0)
        _rate = new_rate;
    return *this;
}

/*
 *  Устанавлливает новое значения для радиуса атаки юнита
 */
CAbstractAttacedUnit& CAbstractAttacedUnit::setDamageRadius(int new_damage_radius)
{
    if (new_damage_radius > 0)
        _damageRadius = new_damage_radius;
    return *this;
}

/*
 *  Устанавлливает нового атакуемого юнита
 */
CAbstractAttacedUnit& CAbstractAttacedUnit::setAttacedUnit(CAbstractProtectiveUnit *new_attaced_unit)
{
    if (new_attaced_unit != NULL)
        _attacedUnit = new_attaced_unit;
    return *this;
}

#pragma mark - Дополнительные методы

/*
 *  Наносит урон противнику. Возвращает true, если противник погиб от удара и false, если все еще жив
 */
bool CAbstractAttacedUnit::makeDamageTo(CAbstractProtectiveUnit *attaced_unit)
{
    if(attaced_unit->getDemaged(_maxDamage)) {
        printf("Unit %s was killed by %s", attaced_unit->getName(), this->getName());
        return true;
    } else return false;
}