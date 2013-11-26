//
//  CAbstractProtectiveUnit.cpp
//  HelloCpp
//
//  Created by Daniel on 05.11.13.
//
//

#include "CAbstractProtectiveUnit.h"
#include "CLandscape.h"

// Графичиские константы
const int HealthFramesNumber = 21;

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CAbstractProtectiveUnit::CAbstractProtectiveUnit()
{
    _alive = true;
    _health = 10;
    _maxHealth = 100;
    _deadAnimation = Animation::create();
    _deadAnimation->retain();
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
    return _alive;
}

/*
 *  Возвращает анимацию смерти/разрушения
 */
Animation* CAbstractProtectiveUnit::getDeadAnimation()
{
    return _deadAnimation;
}

#pragma mark - SET методы

/*
 *  Устанавливаем текущий уровень здоровья
 */
CAbstractProtectiveUnit& CAbstractProtectiveUnit::setHealth(int new_health)
{
    if (new_health <= 0) throw "Health is less than 0";
    _health = new_health;
    return *this;
}

/*
 *  Устанавливаем максимальный уровень здоровья
 */
CAbstractProtectiveUnit& CAbstractProtectiveUnit::setMaxHealth(int new_max_health)
{
    if (new_max_health <= 0) throw "Max health is less than 0";
    _maxHealth = new_max_health;
    return *this;
}

/*
 *  Устанавливаем значение для alive
 */
CAbstractProtectiveUnit& CAbstractProtectiveUnit::setAlive(bool new_alive)
{
    setVisible(new_alive);
    _alive = new_alive;
    return *this;
}


/*
 *  Устанавливает новую анимацию смерти/разрушения
 */
CAbstractProtectiveUnit& CAbstractProtectiveUnit::setDeadAnimation(Animation *new_dead_animation)
{
    if (!new_dead_animation) throw "Dead animation is NULL";
    _deadAnimation = new_dead_animation;
    return *this;
}

#pragma mark - Дополнительные методы
#pragma mark - PRIVATE

/*
 *  Убийство юнита
 */
void CAbstractProtectiveUnit::killEnemy()
{
    setAlive(false);
    getLandscape()->removeEnemy(this);
}

#pragma mark - PUBLIC

/*
 *  Юнит получает урон. Возвращает true, если юнит умер, и false, если еще жив
 */
bool CAbstractProtectiveUnit::getDemaged(int damage)
{
    _health -= damage;
    if (_health > 0) {
        this->removeChild(_unitHealthSprite);
        _unitHealthSprite = getUnitHealthAnimation()[int(_health * HealthFramesNumber / _maxHealth)];
        this->addChild(_unitHealthSprite);
        this->_sprite->runAction(TintBy::create(0.1, 0, 255, 255));
        return false;
    } else {
        this->stopAllActions();
        this->_sprite->stopAllActions();
        FiniteTimeAction* sequence = Sequence::create(Animate::create(_deadAnimation),
                                                      CallFunc::create(this, callfunc_selector(CAbstractProtectiveUnit::killEnemy)),
                                                      NULL);
        sequence->retain();
        this->_sprite->runAction(sequence);
        return true;
    }
}

