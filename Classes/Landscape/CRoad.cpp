//
//  CRoad.cpp
//  HelloCpp
//
//  Created by Daniel on 11.11.13.
//
//

#include "CRoad.h"

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CRoad::CRoad()
{
    _freeTileGid = 0;
    _occupiedTileGid = 1;
    _castleCoord = Point(0, 0);
    _road = NULL;
    _path = NULL;
}

#pragma mark - Деструктор

CRoad::~CRoad()
{
    _freeTileGid = 0;
    _occupiedTileGid = 1;
    _castleCoord = Point(0, 0);
    delete _road;
    delete _path;
}

#pragma mark - GET методы

/*
 *  Возвращает номер свободной ячейки
 */
int CRoad::getFreeTileGid()
{
    return _freeTileGid;
}

/*
 *  Возвращает номер занятой ячейки
 */
int CRoad::getOccupiedTileGid()
{
    return _occupiedTileGid;
}

/*
 *  Возвращает координаты замка
 */
Point CRoad::getCastleCoord()
{
    return _castleCoord;
}

/*
 *  Возвращает слой дороги
 */
TMXLayer* CRoad::getRoad()
{
    return _road;
}

/*
 *  Возвращает путь до замка
 */
vector<Point>* CRoad::getPath()
{
    return _path;
}

#pragma mark - SET методы

/*
 *  Установить координаты замка
 */
CRoad& CRoad::setCastleCoord(Point new_castle_coord) {
    Rect layerSize = Rect(0, 0, _road->getContentSize().width / 32, _road->getContentSize().height / 32);
    if (layerSize.containsPoint(new_castle_coord) && _road->getTileGIDAt(new_castle_coord) == _freeTileGid) _castleCoord = new_castle_coord;
    return *this;
}

/*
 *  Установить слой дороги
 */
CRoad& CRoad::setRoad(TMXLayer *new_road)
{
    if (new_road != NULL) _road = new_road;
    return *this;
}

#pragma mark - Внутренние методы объекта

// Направления движений юнита
const Point dir[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int BLANK  = -2;          // незанятная ячейка

vector<Point>* CRoad::lee(Point startPoint)
{
    int d, x, y;
    bool stop;
    
    // Необходимо для поиска TODO: убрать после debug
    int usedMap[(int)_road->getLayerSize().width][(int)_road->getLayerSize().height];
    // Создаем метакарту доступности
    for (int i = 0; i < (int)_road->getLayerSize().width; i++)
        for (int j = 0; j < (int)_road->getLayerSize().height; j++)
            usedMap[i][j] = BLANK;
    
    // распространение волны
    d = 0;
    usedMap[(int)startPoint.x][(int)startPoint.y] = 0;
    do {
        stop = true;
        for ( x = 0; x < _road->getLayerSize().width; ++x )
            for ( y = 0; y < _road->getLayerSize().height; ++y )
                if ( usedMap[x][y] == d )
                {
                    for (int k = 0; k < 4; ++k ) {
                        Point new_point = Point(x + (int)dir[k].x, y + (int)dir[k].y);
                        if ( Rect(0, 0, _road->getLayerSize().width - 1, _road->getLayerSize().height - 1).containsPoint(new_point) &&
                            usedMap[(int)new_point.x][(int)new_point.y] == BLANK &&
                            _road->getTileGIDAt(new_point) == _freeTileGid)
                        {
                            stop = false;
                            usedMap[(int)new_point.x][(int)new_point.y] = d + 1;
                        }
                    }
                }
        d++;
    } while ( !stop && usedMap[(int)_castleCoord.x][(int)_castleCoord.y] == BLANK );
    
    if (usedMap[(int)_castleCoord.x][(int)_castleCoord.y] == BLANK) return false;  // путь не найден
    
    // восстановление пути
    int len = usedMap[(int)_castleCoord.x][(int)_castleCoord.y];
    x = (int)_castleCoord.x;
    y = (int)_castleCoord.y;
    d = len;
    
    vector<Point>* new_path = new vector<Point>;
    
    Point p = Point(x, y);
    while ( d > 0 )
    {
        new_path->push_back(p);
        d--;
        for (int k = 0; k < 4; ++k)
            if (usedMap[int(p.x + dir[k].x)][int(p.y + dir[k].y)] == d)
            {
                p.x += dir[k].x;
                p.y += dir[k].y;
                
                break;
            }
    }
    
    return new_path;
}

#pragma mark - Дополнительные методы

/*
 *  Нахождение кротчайшего пути до замка
 */
bool CRoad::findPath(Point startPoint)
{
    // TODO: написать поиск кратчайшего маршрута
    
    printf("Find new path! \n");
    
    //dfs(startPoint, new_path);
    vector<Point>* new_path = lee(startPoint);
    //for (int i = 0; i < new_path->size(); i++)
        //new_deque_path->push_back((*new_path)[i]);
    
    if (!new_path->empty()) {
        delete _path;
        _path = new_path;
        return true;
    } else return false;
}

/*
 *  Проверка пути на валидность
 */
bool CRoad::checkPath()
{
    if (_path->empty())
        return false;
    for (int i = 0; i < _path->size(); i++)
        if (_road->getTileGIDAt((*_path)[i]) == _occupiedTileGid)
            return false;
    return true;
}

#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CRoad::init()
{
    // Устнаваливаем значения для занятого и свободного тайла в метаслоях
    TMXMapInfo* mapInfo = TMXMapInfo::create("TileMap.tmx");
    Object* object;
    CCARRAY_FOREACH(mapInfo->getTilesets(), object);
    _occupiedTileGid = ((TMXTilesetInfo*)object)->_firstGid;
    _freeTileGid = _occupiedTileGid + 1;
    
    return true;
}

/*
 *  Метод для создания объекта с картой и координатами замка
 */
CRoad* CRoad::createWithLayerAndCastleCoord(TMXLayer *layer, Point castleCoord)
{
    CRoad* new_road = new CRoad;
    if (new_road && new_road->init()) {
        new_road->setRoad(layer);
        new_road->setCastleCoord(castleCoord);
        return new_road;
    } else return NULL;
    
}