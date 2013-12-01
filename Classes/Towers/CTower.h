//
//  CTower.h
//  HelloCpp
//
//  Created by Daniel on 07.11.13.
//
//

#ifndef __HelloCpp__CTower__
#define __HelloCpp__CTower__

// Кастомные
#include "CAbstractEnemy.h"

class CLandscape;

class CTower : public CAbstractAttacedUnit
{
private:
    int _level;
    int _experience;
    
    // Графичечкие поля
    vector<vector<Sprite*>> _towerAnimation;
    vector<Sprite*> _fireAnimation;
    
    // Контейнер всех передвигающихся юнитов по карте
    vector<CAbstractEnemy*>* _enemiesArray;
    
    /** Дополнительные методы */
    void levelUp();
    void addExperience(int exp);
    virtual void update(float dt);
    
public:
    /** Конструкторы */
    CTower();
    
    /** GET методы */
    int getLevel();
    int getExperience();
    vector<CAbstractEnemy*>* getEnemiesArray();
    
    /** SET методы */
    CTower& setLevel(int new_level);
    CTower& setExperience(int new_experience);
    CTower& setEnemiesArray(vector<CAbstractEnemy*>* new_enemies_array);
    
    /** Перегрузка методов */
    virtual void draw();
    virtual void attackAnimation();
    virtual void isKillEnemy();
    
    /** Инициализация */
    virtual bool init();
    static CTower* createTower(CLandscape* landscape);
    
    /** Пользовательский ввод */
    bool onTouchBegan(Touch *touch, Event *event);
    
    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CTower);
};


#endif /* defined(__HelloCpp__CTower__) */
