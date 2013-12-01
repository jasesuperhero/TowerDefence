//
//  CRoad.h
//  HelloCpp
//
//  Created by Daniel on 11.11.13.
//
//

#ifndef __HelloCpp__CRoad__
#define __HelloCpp__CRoad__

// Библиотеки
#include <cocos2d.h>

using namespace cocos2d;
using namespace std;

class CRoad : public Object
{
private:
    int _freeTileGid;
    int _occupiedTileGid;
    Point _castleCoord;
    TMXLayer* _road;
    
    vector<Point>* _path;
    
    /** Внутренние методы объекта */
    vector<Point>* findPathWithoutBlock(Point startPoint);
    vector<Point>* findPathWithBlock(Point startPoint);
    
public:
    /** Конструкторы */
    CRoad();
    
    /** Деструктор */
    ~CRoad();
    
    /** GET методы */
    int getFreeTileGid();
    int getOccupiedTileGid();
    Point getCastleCoord();
    TMXLayer* getRoad();
    vector<Point>* getPath();
    
    /** SET методы */
    CRoad& setCastleCoord(Point new_castle_coord);
    CRoad& setRoad(TMXLayer* new_road);
    
    /** Дополнительные методы */
    bool findPath(Point startPoint);
    bool checkPath();
    
    /** Инициализация */
    virtual bool init();
    static CRoad* createWithLayerAndCastleCoord(TMXLayer* layer, Point castleCoord);
};

#endif /* defined(__HelloCpp__CRoad__) */
