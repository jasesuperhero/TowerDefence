//
//  CGameplayLayer.h
//  HelloCpp
//
//  Created by Daniel on 02.11.13.
//
//

#ifndef __HelloCpp__CGameplayLayer__
#define __HelloCpp__CGameplayLayer__

// Библиотеки
#include <cocos2d.h>
#include <vector>
// Кастомные
#include "CLandscape.h"
#include "CWall.h"
#include "CTower.h"

using namespace cocos2d;

class CGameplayLayer : public Layer {
private:
    CLandscape* _landscape;
    
public:
    /** Методы создания и инициализации */
    virtual bool init();

    /** Пользовательский ввод */
    bool onTouchBegan(Touch *touch, Event *event);
    
    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CGameplayLayer);
};

#endif /* defined(__HelloCpp__CGameplayLayer__) */
