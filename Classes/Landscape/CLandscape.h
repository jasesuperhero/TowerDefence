//
//  CLandscape.h
//  HelloCpp
//
//  Created by Daniel on 08.11.13.
//
//

#ifndef __HelloCpp__CLandscape__
#define __HelloCpp__CLandscape__

// Библиотеки
#include <cocos2d.h>

// Кастомные
#include "CCastle.h"
#include "CTower.h"
#include "CWall.h"
#include "CLair.h"

using namespace cocos2d;
using namespace std;

class CLandscape : public TMXTiledMap
{
private:
    // Параметры для работы с картой
    int             _freeTileGid;
    int             _occupiedTileGid;
    
    // Метаслои карты
    TMXLayer*       _towersPlaces;
    TMXLayer*       _wallsPlaces;
    TMXLayer*       _road;
    
    // Контейнеры для объектов
    vector<CAbstractAttacedUnit*> _attacedBuildings;
    vector<CWall*> _walls;
    vector<CAbstractEnemy*> _enemies;
    
    /** Дополнительные методы */
    // Обработка TMX файла карты
    void getMetaTiles();
    void placeCastle();
    void placeLairs();
    
    // Графика
    void scaleMapToWin();
    
    virtual void update(float dt);
    
public:
    /** Конструкторы */
    CLandscape();
    
    /** Деструктор */
    ~CLandscape();
    
    /** GET методы */
    TMXLayer& getTowerPlaces();
    TMXLayer& getWallsPlaces();
    Point getCastleCoord();
    
    /** Методы для добалвения новых объектов */
    void addToMapWithPosition(Layer* layer, Point tileCoord);
    CTower* addTowerToMapWithPosition(Point tileCoord);
    CWall* addWallToMapWithPosition(Point tileCoord);
    void addEnemyToMapWithPosition(Point tileCoord, CAbstractEnemy* enemy);
    
    /** Методы для удаления объектов */
    void removeEnemy(CAbstractUnit* enemy);
    
    /** Методы для определения клетки */
    Point tileCoordForPosition(Point position);
    Point getPositionWithTiledCoord(Point tileCoord);
    bool isClickedTowerPlace(Point position);
    bool isClickedWallPlace(Point position);
    
    /** Методы создания и инициализации */
    virtual bool init();
    
    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CLandscape);
};

#endif /* defined(__HelloCpp__CLandscape__) */
