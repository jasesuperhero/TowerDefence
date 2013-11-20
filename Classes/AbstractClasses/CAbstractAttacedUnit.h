//
//  CAbstractAttacedUnit.h
//  HelloCpp
//
//  Created by Daniel on 07.11.13.
//
//

#ifndef __HelloCpp__CAbstractAttacedUnit__
#define __HelloCpp__CAbstractAttacedUnit__

// Библиотеки
#include <cocos2d.h>
// Кастомные
#include "CAbstractProtectiveUnit.h"

class CAbstractAttacedUnit : public CAbstractProtectiveUnit
{
protected:
    int _maxDamage;
    int _rate;
    int _damageRadius;
    
    CAbstractProtectiveUnit* _attacedUnit;
    
public:
    /** Конструкторы */
    CAbstractAttacedUnit();
    
    /** GET методы */
    int getMaxDamage();
    int getRate();
    int getDamageRadius();
    CAbstractProtectiveUnit* getAttacedUnit();
    
    /** SET методы */
    CAbstractAttacedUnit& setMaxDamage(int new_max_damage);
    CAbstractAttacedUnit& setRate(int new_rate);
    CAbstractAttacedUnit& setDamageRadius(int new_damage_radius);
    CAbstractAttacedUnit& setAttacedUnit(CAbstractProtectiveUnit* new_attaced_unit);
    
    /** Дополнительные методы */
    void makeDamageTo();
};

#endif /* defined(__HelloCpp__CAbstractAttacedUnit__) */
