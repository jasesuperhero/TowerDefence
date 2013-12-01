//
//  CWall.h
//  HelloCpp
//
//  Created by Daniel on 05.11.13.
//
//

#ifndef __HelloCpp__CWall__
#define __HelloCpp__CWall__

// Системные
#include <cocos2d.h>
// Кастомные
#include "CAbstractProtectiveUnit.h"

class CLandscape;

class CWall : public CAbstractProtectiveUnit
{
private:
    bool _canRepair;
    int _autoRepairValue;
    
    /** Дополнительные методы */
    void autoRepairWall();
    virtual void update(float dt);
    
public:
    /** Конструкторы */
    CWall();
    
    /** GET методы */
    bool getCanRepair();
    int getAutoRepairValue();
    
    /** SET методы */
    CWall& setCanRepair(bool new_value);
    CWall& setAutoRepairValue(int new_repair_value);
    
    /** Инициализация */
    virtual bool init();
    static CWall* createWall(CLandscape* landscape);
    
    /** Пользовательский ввод */
    bool onTouchBegan(Touch *touch, Event *event);

    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CWall);
};

#endif /* defined(__HelloCpp__CWall__) */
