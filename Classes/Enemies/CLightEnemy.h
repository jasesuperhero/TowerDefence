//
//  CLightEnemy.h
//  HelloCpp
//
//  Created by Daniel on 08.11.13.
//
//

#ifndef __HelloCpp__CLightEnemy__
#define __HelloCpp__CLightEnemy__

#include <cocos2d.h>
#include "CAbstractEnemy.h"

class CLightEnemy : public CAbstractEnemy
{
private:
    /** Дополнительные методы */
    virtual void update(float dt);
    
public:
    /** Дополнительные методы */
    void makeMove();
    
    /** Инициализация */
    virtual bool init();
    static CLightEnemy* createEnemyWithRoadAndCastleCoord(TMXLayer* road, Point castleCoord);
    
    /** Пользовательский ввод */
    bool onTouchBegan(Touch *touch, Event *event);
    
    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CLightEnemy);
};

#endif /* defined(__HelloCpp__CLightEnemy__) */
