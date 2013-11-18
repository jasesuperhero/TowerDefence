//
//  CCastle.h
//  HelloCpp
//
//  Created by Daniel on 09.11.13.
//
//

#ifndef __HelloCpp__CCastle__
#define __HelloCpp__CCastle__

// Библиотеки
#include <cocos2d.h>
// Кастомные
#include "CAbstractAttacedUnit.h"

class CCastle : public CAbstractAttacedUnit
{
private:
    int _money;

public:
    /** Конструкторы */
    CCastle();
    
    /** GET методы */
    int getMoney();
    
    /** SET методы */
    CCastle& setMoney(int new_money);
    
    /** Инициализация */
    virtual bool init();
    
    /** Пользовательский ввод */
    bool onTouchBegan(Touch *touch, Event *event);
    
    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CCastle);
};

#endif /* defined(__HelloCpp__CCastle__) */
