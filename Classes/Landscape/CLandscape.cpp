//
//  CLandscape.cpp
//  HelloCpp
//
//  Created by Daniel on 08.11.13.
//
//

#include "CLandscape.h"
#include "CLightEnemy.h"

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

/*
 *  Возвращает замок
 */
CCastle* CLandscape::getCastle()
{
    return _castle;
}

/*
 *  Возвращает массив атакующий построек
 */
vector<CAbstractAttacedUnit*>* CLandscape::getAttacedBuildings()
{
    return &_attacedBuildings;
}

/*
 *  Возвращает массив стен
 */
vector<CWall*>* CLandscape::getWalls()
{
    return &_walls;
}

/*
 *  Возвращает массив врагов
 */
vector<CAbstractEnemy*>* CLandscape::getEnemies()
{
    return &_enemies;
}

#pragma mark - Дополнительные методы
#pragma mark - PUBLIC

/*
 *  Возвращает координаты замка
 */
Point CLandscape::getCastleCoord()
{
    TMXObjectGroup* castlePlace = getObjectGroup("Castle");
    Point castleCoord = Point(castlePlace->getObject("CastleCoord")->valueForKey("x")->intValue() + 16,
                              castlePlace->getObject("CastleCoord")->valueForKey("y")->intValue() + 16);
    castleCoord.x = trunc(castleCoord.x / this->getTileSize().width); castleCoord.y = trunc(castleCoord.y / this->getTileSize().width) - 1;
    return castleCoord;
}

#pragma mark - PRIVAT

/*
 *  Устанавливает значения свободных и занятых мета-клеток
 */
void CLandscape::getMetaTiles()
{
    TMXMapInfo* mapInfo = TMXMapInfo::create("TileMap.tmx");
    Object* object;
    CCARRAY_FOREACH(mapInfo->getTilesets(), object);
    _occupiedTileGid = ((TMXTilesetInfo*)object)->_firstGid;
    _freeTileGid = _occupiedTileGid + 1;
}

/*
 *  Установка замка на карту
 */
void CLandscape::placeCastle()
{
    _castle = CCastle::createCastle(this);
    TMXObjectGroup* castlePlace = getObjectGroup("Castle");
    Point castleCoord = Point(castlePlace->getObject("CastleCoord")->valueForKey("x")->intValue() + 16,
                              castlePlace->getObject("CastleCoord")->valueForKey("y")->intValue() + 16);
    _castle->setPosition(castleCoord);
    _castle->placeTowers();
    this->addChild(_castle);
}

/*
 *  Установка на карту логов врагов
 */
void CLandscape::placeLairs()
{
    TMXLayer* lairs_places = getLayer("Lairs");
    
    for (int i = 0; i < lairs_places->getLayerSize().width; i++)
        for (int j = 0; j < lairs_places->getLayerSize().height; j++)
            if (lairs_places->getTileGIDAt(Point(i, j))) {
                CLair* lair = CLair::createLairWithLandscape(this);
                lair->setPosition(getPositionWithTiledCoord(Point(i, j)));
                this->addChild(lair, 100);
            }
}

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
        CTower* tower = CTower::createTower(this);
        if (_castle->buyBuilding(tower->getCost())) {
    
            // Ставим занятость клетки
            _towersPlaces->setTileGID(_occupiedTileGid, tileCoord);
        
            tower->setPosition(getPositionWithTiledCoord(tileCoord));
            this->addChild(tower, this->getChildrenCount());
            return tower;
        };
    }
    return NULL;
}

/*
 *  Добавление новой стены на карту
 */
CWall* CLandscape::addWallToMapWithPosition(Point tileCoord)
{
    if (_wallsPlaces->getTileGIDAt(tileCoord) == _freeTileGid) {
        Size mapSize = this->getMapSize();
    
        // Ставим занятость клетки
        _wallsPlaces->setTileGID(_occupiedTileGid, tileCoord);
        _road->setTileGID(_occupiedTileGid, tileCoord);
        
        CWall* wall = CWall::createWall(this);
        wall->setPosition(getPositionWithTiledCoord(tileCoord));
        _walls.push_back(wall);
        this->addChild(wall, this->getChildrenCount());
        return wall;
    } else return NULL;
}

#pragma mark - Удаление объектов

/*
 *  Удаление объектов
 */
void CLandscape::removeUnit(CAbstractUnit *unit)
{
    // Провекра на тип удаляемого юнита
    // Враг
    if (dynamic_cast<CAbstractEnemy*>(unit)) {
        vector<CAbstractEnemy*>::const_iterator location = find(_enemies.begin(), _enemies.end(), unit);
        if (location != _enemies.end())
            _enemies.erase(location);
    }
    // Башня
    if (dynamic_cast<CTower*>(unit)) {
        vector<CAbstractAttacedUnit*>::const_iterator location = find(_attacedBuildings.begin(), _attacedBuildings.end(), unit);
        if (location != _attacedBuildings.end())
            _attacedBuildings.erase(location);
    }
    // Стена
    if (dynamic_cast<CWall*>(unit)) {
        _road->setTileGID(_freeTileGid, unit->getTiledCoord());
        vector<CWall*>::const_iterator location = find(_walls.begin(), _walls.end(), unit);
        if (location != _walls.end())
            _walls.erase(location);
    }
}

/*
 *  Добавление нового юнита на карту
 */
void CLandscape::addEnemyToMapWithPosition(Point tileCoord, CAbstractEnemy* enemy)
{
    if (_road->getTileGIDAt(tileCoord) == _freeTileGid) {
        enemy->setPosition(getPositionWithTiledCoord(tileCoord));
        enemy->setAlive(true);
        this->addChild(enemy, this->getChildrenCount());
        
        _enemies.push_back(enemy);
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
 *  Преобразует координаты карты в экранные координаты
 */
Point CLandscape::getPositionWithTiledCoord(Point tileCoord)
{
    int tile_size = this->getTileSize().width;
    return Point(tileCoord.x * tile_size + tile_size / 2,
                 (this->getContentSize().height / 32 - tileCoord.y - 1) * tile_size + tile_size / 2);
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
    this->initWithTMXFile("TileMap.tmx");
    //_background = this->getLayer("Background");
    _wallsPlaces = this->getLayer("WallsPlaces");
    //_wallsPlaces->setVisible(false);
    _towersPlaces = this->getLayer("TowersPlaces");
    //_towersPlaces->setVisible(false);
    _road = this->getLayer("Road");
    
    // Устнаваливаем значения для занятого и свободного тайла в метаслоях
    getMetaTiles();
    // Масштабирование и выравнивание карты по центру
    scaleMapToWin();
    this->setPosition(((Director::getInstance()->getWinSizeInPixels()).width -
                       (this->getBoundingBox()).size.width) / 2, 0);
    
    // Запускаем основной цикл для карты
    this->getScheduler()->scheduleUpdateForTarget(this, 1, false);
    
    // Установка замка
    placeCastle();
    // Установка логов
    placeLairs();
    
    return true;
}
