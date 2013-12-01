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
    _attacedUnit = NULL;
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
    if (new_max_damage < 0) throw "New damage is less than 0";
    _maxDamage = new_max_damage;
    return *this;
}

/*
 *  Устанавлливает новое значения для скорости атаки юнита
 */
CAbstractAttacedUnit& CAbstractAttacedUnit::setRate(int new_rate)
{
    if (new_rate < 0) throw "New rate is less than 0";
    _rate = new_rate;
    return *this;
}

/*
 *  Устанавлливает новое значения для радиуса атаки юнита
 */
CAbstractAttacedUnit& CAbstractAttacedUnit::setDamageRadius(int new_damage_radius)
{
    if (new_damage_radius < 0) throw "New damage radius is less than 0";
    _damageRadius = new_damage_radius;
    return *this;
}

/*
 *  Устанавлливает нового атакуемого юнита
 */
CAbstractAttacedUnit& CAbstractAttacedUnit::setAttacedUnit(CAbstractProtectiveUnit *new_attaced_unit)
{
    _attacedUnit = new_attaced_unit;
    this->stopActionByTag(ATTACK_TAG);
    return *this;
}

#pragma mark - Дополнительные методы

/*
 *  Наносит урон противнику. Возвращает true, если противник погиб от удара и false, если все еще жив
 */
bool CAbstractAttacedUnit::makeDamageTo()
{
    if (_attacedUnit && _attacedUnit->getAlive() && canAttack()) {
        if(_attacedUnit->getDemaged(_maxDamage)) {
            printf("Unit %s was killed by %s\n", _attacedUnit->getName(), this->getName());
            return true;
        }
    } else setAttacedUnit(NULL);
    return false;
}

/*
 *  Проверяет возможность нанесения урона противнику
 */
bool CAbstractAttacedUnit::canAttack()
{
    if (!_attacedUnit) return false;
    return getPosition().getDistance(_attacedUnit->getPosition()) < _damageRadius;
}

/*
 *  Метод для выстрела пушки и обновления ее спрайта
 */
void CAbstractAttacedUnit::attack()
{
    if (_attacedUnit && _attacedUnit->getAlive() && canAttack()) {
        attackAnimation();
        FiniteTimeAction* sequence = Sequence::create(DelayTime::create(getRate()),
                                                      CallFunc::create(this, callfunc_selector(CAbstractAttacedUnit::attack)),
                                                      NULL);
        sequence->setTag(ATTACK_TAG);
        sequence->retain();
        this->runAction(sequence);
    } else setAttacedUnit(NULL);
}

/*
 *  Метод определяющий убийство атакуемого юнита
 */
void CAbstractAttacedUnit::isKillEnemy()
{
    this->stopActionByTag(ATTACK_TAG);
}