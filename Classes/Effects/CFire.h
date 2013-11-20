//
//  CFire.h
//  HelloCpp
//
//  Created by Daniel on 20.11.13.
//
//

#ifndef __HelloCpp__CFire__
#define __HelloCpp__CFire__

#include <iostream>
#include <cocos2d.h>

using namespace cocos2d;

class CFire : public Sprite
{
private:
    Animation* _fireAnimation;
    
public:
    /** Конструкторы */
    CFire();
    
    /** Инициализация */
    virtual bool init();
    
    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CFire);
};

#endif /* defined(__HelloCpp__CFire__) */
