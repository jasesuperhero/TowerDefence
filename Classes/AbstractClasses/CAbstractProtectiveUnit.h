//
//  CAbstractProtectiveUnit.h
//  HelloCpp
//
//  Created by Daniel on 05.11.13.
//
//

#ifndef __HelloCpp__CAbstractProtectiveUnit__
#define __HelloCpp__CAbstractProtectiveUnit__

// Кастомные
#include "CAbstractUnit.h"

class CLandscape;

class CAbstractProtectiveUnit : public CAbstractUnit
{
protected:
    int _health;
    int _maxHealth;
    int _cost;
    bool _alive;
    
    // Графика
    Animate* _deadAnimation;
    
    /** Дополнительные методы */
    virtual void killUnit();
    
public:
    /** Конструкторы */
    CAbstractProtectiveUnit();
    
    /** GET методы */
    int getHealth();
    int getMaxHealth();
    int getCost();
    bool getAlive();
    Animate* getDeadAnimation();
    
    /** SET методы */
    CAbstractProtectiveUnit& setHealth(int new_health);
    CAbstractProtectiveUnit& setMaxHealth(int new_max_health);
    CAbstractProtectiveUnit& setCost(int new_cost);
    CAbstractProtectiveUnit& setAlive(bool new_alive);
    CAbstractProtectiveUnit& setDeadAnimation(Animate* new_dead_animation);
    
    /** Дополнительные методы */
    bool getDemaged(int damage);
};

#endif /* defined(__HelloCpp__CAbstractProtectiveUnit__) */
