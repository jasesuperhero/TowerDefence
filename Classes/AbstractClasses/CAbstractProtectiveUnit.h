//
//  CAbstractProtectiveUnit.h
//  HelloCpp
//
//  Created by Daniel on 05.11.13.
//
//

#ifndef __HelloCpp__CAbstractProtectiveUnit__
#define __HelloCpp__CAbstractProtectiveUnit__

// Библиотеки
#include <cocos2d.h>
// Кастомные
#include "CAbstractUnit.h"

class CAbstractProtectiveUnit : public CAbstractUnit
{
protected:
    int _health;
    int _maxHealth;
    bool _alive;
    
    Animation* _deadAnimation;
    
private:
    /** SET методы */
    CAbstractProtectiveUnit& setAlive(bool new_alive);
    
public:
    /** Конструкторы */
    CAbstractProtectiveUnit();
    
    /** GET методы */
    int getHealth();
    int getMaxHealth();
    bool getAlive();
    Animation* getDeadAnimation();
    
    /** SET методы */
    CAbstractProtectiveUnit& setHealth(int new_health);
    CAbstractProtectiveUnit& setMaxHealth(int new_max_health);
    CAbstractProtectiveUnit& setDeadAnimation(Animation* new_dead_animation);
    
    /** Дополнительные методы */
    bool getDemaged(int damage);
};

#endif /* defined(__HelloCpp__CAbstractProtectiveUnit__) */
