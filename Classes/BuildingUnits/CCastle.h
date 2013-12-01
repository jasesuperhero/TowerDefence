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
#include "CTower.h"
#include "CWall.h"

class CLandscape;

class CCastle : public CAbstractProtectiveUnit
{
private:
    int _money;
    
    /** Дополнительные методы */
    virtual void update(float dt);
    
public:
    /** Конструкторы */
    CCastle();
    
    /** GET методы */
    int getMoney();
    
    /** SET методы */
    CCastle& setMoney(int new_money);
    
    /** Дополнительные методы */
    bool buyBuilding(int cost);
    void addMoney(int adding_money);
    void placeTowers();
    
    /** Инициализация */
    virtual bool init();
    static CCastle* createCastle(CLandscape* landscape);
    
    /** Пользовательский ввод */
    bool onTouchBegan(Touch *touch, Event *event);
    
    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CCastle);
};

#endif /* defined(__HelloCpp__CCastle__) */
