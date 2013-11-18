//
//  CLandscape.cpp
//  HelloCpp
//
//  Created by Daniel on 08.11.13.
//
//

#include "CLandscape.h"

// Направления движений юнита
const Point dir[8] = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CLandscape::CLandscape()
{
    _towersPlaces = NULL;
    _wallsPlaces = NULL;
}

#pragma mark - Деструктор

/*
 *  Деструктор
 */
CLandscape::~CLandscape()
{
    CC_SAFE_RELEASE(this);
}

#pragma mark - GET методы

/*
 *  Возвращает слой мест для башен
 */
TMXLayer& CLandscape::getTowerPlaces()
{
    return *_towersPlaces;
}

/*
 *  Возвращает слой мест для стен
 */
TMXLayer& CLandscape::getWallsPlaces()
{
    return *_wallsPlaces;
}

#pragma mark - Дополнительные методы
#pragma mark - PRIVAT
/*
 *  Масштабирование карты по окну
 */
void CLandscape::scaleMapToWin()
{
    Size winSize = Director::getInstance()->getWinSizeInPixels();
    Size mapSize = this->getContentSize();
    
    this->setScale(MIN(winSize.width / mapSize.width, winSize.height / mapSize.height));
}

/*
 *  Обновление объекта со временем
 */
void CLandscape::update(float dt)
{
    //printf("Update Landscape\n");
    //for (int i = 0; i < _attacedBuildings.size(); i++)
      //  for (int j = 0; j < _enemies.size(); j++)
            
}

#pragma mark - Методы для добалвения новых объектов

/*
 *  Добавление нового объекта на карту с масштабированием
 */
void CLandscape::addToMapWithPosition(Layer *layer, Point tileCoord)
{
    Size mapSize = this->getMapSize();
    int tileSize = (this->getTileSize()).width;
    layer->setPosition((tileCoord.x + 1) * tileSize - tileSize / 2, (mapSize.height - tileCoord.y) * tileSize - tileSize / 2);
    this->addChild(layer, this->getChildrenCount());
}

/*
 *  Добавление новой башни на карту
 */
CTower* CLandscape::addTowerToMapWithPosition(Point tileCoord)
{
    if (_towersPlaces->getTileGIDAt(tileCoord) == _freeTileGid) {
        Size mapSize = this->getMapSize();
        int tileSize = (this->getTileSize()).width;
        CTower* tower = CTower::create();
    
        // Ставим занятость клетки
        _towersPlaces->setTileGID(_occupiedTileGid, tileCoord);
        
        tower->setPosition((tileCoord.x + 1) * tileSize - tileSize / 2,
                           (mapSize.height - tileCoord.y) * tileSize - tileSize / 2);
        this->addChild(tower, this->getChildrenCount());
        return tower;
    } else return NULL;
}

/*
 *  Добавление новой стены на карту
 */
CWall* CLandscape::addWallToMapWithPosition(Point tileCoord)
{
    if (_wallsPlaces->getTileGIDAt(tileCoord) == _freeTileGid) {
        Size mapSize = this->getMapSize();
        int tileSize = (this->getTileSize()).width;
    
        // Ставим занятость клетки
        _wallsPlaces->setTileGID(_occupiedTileGid, tileCoord);
        _road->setTileGID(_occupiedTileGid, tileCoord);
        
        CWall* wall = CWall::create();
        wall->setPosition((tileCoord.x + 1) * tileSize - tileSize / 2,
                          (mapSize.height - tileCoord.y) * tileSize - tileSize / 2);
        this->addChild(wall, this->getChildrenCount());
        return wall;
    } else return NULL;
}

/*
 *  Добавление нового юнита на карту
 */
void CLandscape::addEnemyToMapWithPosition(Point tileCoord, CAbstractEnemy* enemy)
{
    if (_road->getTileGIDAt(tileCoord) == _freeTileGid) {
        Size mapSize = this->getMapSize();
        int tileSize = (this->getTileSize()).width;
        
        enemy->setPosition((tileCoord.x + 1) * tileSize - tileSize / 2,
                          (mapSize.height - tileCoord.y) * tileSize - tileSize / 2);
        this->addChild(enemy, this->getChildrenCount());
    };
}

#pragma mark - Методы для определения клетки

/*
 *  Определение тайла карты по координате
 */
Point CLandscape::tileCoordForPosition(Point position)
{
    int x = (position.x - (this->getBoundingBox()).origin.x) / (this->getTileSize().width * this->getScaleX());
    int y = (this->getMapSize().height * this->getTileSize().height * this->getScaleY() - (position.y - (this->getBoundingBox()).origin.y)) / (this->getTileSize().height * this->getScaleY()) ;
    return Point(x, y);
}

/*
 *  Метод проверяет ячейку тайла на возможность постройки башни
 */
bool CLandscape::isClickedTowerPlace(Point position)
{
    int tileGid = _towersPlaces->getTileGIDAt(position);
    if (tileGid) {
        Dictionary *properties = this->getPropertiesForGID(tileGid);
        if (properties) {
            String *collision = new String();
            *collision = *properties->valueForKey("Placeable");
            return (collision && (collision->compare("True")));
        }
    }
    return false;
}

/*
 *  Метод проверяет ячейку тайла на возможность постройки стены
 */
bool CLandscape::isClickedWallPlace(Point position)
{
    int tileGid = _wallsPlaces->getTileGIDAt(position);
    if (tileGid) {
        Dictionary *properties = this->getPropertiesForGID(tileGid);
        if (properties) {
            String *collision = new String();
            *collision = *properties->valueForKey("Placeable");
            return (collision && (collision->compare("True")));
        }
    }
    return false;
}

#pragma mark - Инициализация

bool CLandscape::init()
{
    // Super инициализация слоя
    if ( !TMXTiledMap::init() )
    {
        return false;
    }
    
    // Загрузка карты
    //*this = TMXTiledMap::create("TileMap.tmx");
    this->initWithTMXFile("TileMap.tmx");
    //_background = this->getLayer("Background");
    _wallsPlaces = this->getLayer("WallsPlaces");
    //_wallsPlaces->setVisible(false);
    _towersPlaces = this->getLayer("TowersPlaces");
    //_towersPlaces->setVisible(false);
    _road = this->getLayer("Road");
    
    // Установка замка
    CCastle* castle = CCastle::create();
    TMXObjectGroup* castlePlace = getObjectGroup("Castle");
    Point castleCoord = Point(castlePlace->getObject("CastleCoord")->valueForKey("x")->intValue() + 16,
                              castlePlace->getObject("CastleCoord")->valueForKey("y")->intValue() + 16);
    castle->setPosition(castleCoord);
    this->addChild(castle);
    _attacedBuildings.push_back(castle);
    
    // Устнаваливаем значения для занятого и свободного тайла в метаслоях
    TMXMapInfo* mapInfo = TMXMapInfo::create("TileMap.tmx");
    Object* object;
    CCARRAY_FOREACH(mapInfo->getTilesets(), object);
    _occupiedTileGid = ((TMXTilesetInfo*)object)->_firstGid;
    _freeTileGid = _occupiedTileGid + 1;
    
    // Масштабирование и выравнивание карты по центру
    scaleMapToWin();
    this->setPosition(((Director::getInstance()->getWinSizeInPixels()).width -
                       (this->getBoundingBox()).size.width) / 2,
                      ((Director::getInstance()->getWinSizeInPixels()).height -
                       (this->getBoundingBox()).size.height) / 2);
    
    // Запускаем основной цикл для карты
    this->getScheduler()->scheduleUpdateForTarget(this, 1, false);
    
    //TODO: DEBUG область
    castleCoord.x = trunc(castleCoord.x / this->getTileSize().width); castleCoord.y = trunc(castleCoord.y / this->getTileSize().width) - 1;
    CLightEnemy* enemy = CLightEnemy::createEnemyWithRoadAndCastleCoord(getLayer("Road"), castleCoord);
    addEnemyToMapWithPosition(Point(0, 11), enemy);
    _enemies.push_back(enemy);
    
    return true;
}
