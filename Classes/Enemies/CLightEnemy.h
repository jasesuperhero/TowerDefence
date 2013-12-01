//
//  CLightEnemy.h
//  HelloCpp
//
//  Created by Daniel on 08.11.13.
//
//

#ifndef __HelloCpp__CLightEnemy__
#define __HelloCpp__CLightEnemy__

// Кастомные
#include "CAbstractEnemy.h"

class CLandscape;

class CLightEnemy : public CAbstractEnemy
{    
public:
    /** Инициализация */
    virtual bool init();
    static CLightEnemy* createEnemy(CLandscape* landscape);

    /** Перегруженные методы */
    virtual void attackAnimation();
    
    /** Пользовательский ввод */
    bool onTouchBegan(Touch *touch, Event *event);

    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CLightEnemy);
};

#endif /* defined(__HelloCpp__CLightEnemy__) */
