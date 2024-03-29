#include "glTiledLoader.h"
#include "glTiled.h"
#include "glSettings.h"
#include "glHero.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <iostream>     // std::cout
#include <sstream>
#include <string>
#include <vector>

using namespace std;

glTiledLoader::glTiledLoader()
{

}

glTiled &glTiledLoader::searchTiled(int c, int search_type){
	int d=c+6;
	c-=6;
	if (c<0) c=0;
	if (d>=100) d=99;
	for (int a=c; a<=d;a++){
		for (int b=0; b<vecTiled.at(0).size();b++){
			if (vecTiled.at(a).at(b).type == search_type) 
				return (vecTiled.at(a).at(b));
		}
	}
}

void glTiledLoader::setInvisibleRoom(int c){
	int d=c-3;
	for (int a=c; a<=d;a++){
		for (int b=0; b<vecTiled.at(0).size()/2;b++){
			vecTiled.at(a).at(b).opacity=0;
			vecTiled.at(a).at(b).together=true;
			vecTiled.at(a).at(b).color=sf::Color(128, 128, 128,255);
		}
		for (int b=vecTiled.at(0).size()/2; b<vecTiled.at(0).size();b++){
			vecTiled.at(a).at(b).opacity=0;
			vecTiled.at(a).at(b).together=true;
			vecTiled.at(a).at(b).color=sf::Color(128, 128, 128,0);
		}
	}
}

float glTiledLoader::getOpacity(int x, int y){
	return vecTiled.at(x).at(y).opacity;
}

sf::Color glTiledLoader::getColor(int x, int y){
	return vecTiled.at(x).at(y).color;
}

vector<glTiled*> glTiledLoader::searchTilesAssociatedForAction(int scope, int search_type) 
{
	
	int upperBound = scope + 10;
	int lowerBound = scope - 10;
	lowerBound = (lowerBound < 0) ? 0 : lowerBound;
	upperBound = (upperBound > 99) ? 99 : upperBound;
	vector<glTiled*> result;

	for (int row = lowerBound; row <= upperBound; row++){
		for (int column = 0; column < vecTiled.at(0).size(); column++) {
			//cout << vecTiled.at(row).at(column).type << ", ";
			if (vecTiled.at(row).at(column).type == search_type) 
				result.push_back(&vecTiled.at(row).at(column));
		}
		//cout << endl;
	}

	return result;
}

vector<glTiled*> glTiledLoader::searchTilesAssociatedForActionOrigin(int scope, int search_type) 
{
	
	int upperBound = scope + 10;
	int lowerBound = scope - 10;
	lowerBound = (lowerBound < 0) ? 0 : lowerBound;
	upperBound = (upperBound > 99) ? 99 : upperBound;
	vector<glTiled*> result;

	for (int row = lowerBound; row <= upperBound; row++){
		for (int column = 0; column < vecTiled.at(0).size(); column++) {
			//cout << vecTiled.at(row).at(column).type << ", ";
			if (vecTiled.at(row).at(column).originalType == search_type) 
				result.push_back(&vecTiled.at(row).at(column));
		}
		//cout << endl;
	}

	return result;
}

void glTiledLoader::loadMap(int number) {
	ostringstream ss2;
	ss2 << number;
	string str = ss2.str();
	string line;
	int i = 0;
	size_t pos = 0;
	std::string token;
	std::string a ("assets/maps/");
	std::string b (".txt");
	std::string path;
	path = a+str+b;

	ifstream myfile (path);
	std::stringstream ss;

	vecTiled.clear();
	vec.clear();

	// parsing file
	getline(myfile, line);
	pos =  line.find(",");
	std::string rows = line.substr(0, pos);
	std::string cols = line.substr(pos+1);
	  
	this->amountOfRows = atoi(rows.c_str());
	this->amountOfColumns = atoi(cols.c_str());

	cout << "Map size: (" << amountOfRows << ", " << amountOfColumns << ")" << endl;

	if (myfile.is_open())
	{
		while ( getline (myfile, line) )
		{
			std::string s = line;
			std::string delimiter = ",";

			vec.push_back ( vector<int>() );
			vecTiled.push_back(vector<glTiled>() );

			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);	
				vec.at(i).push_back( atoi(token.c_str()) );
				vecTiled.at(i).push_back(glTiled(atoi(token.c_str()), 0, 0));
				s.erase(0, pos + delimiter.length());		
			}
			++i;
		}
		myfile.close();

		for (int a=0; a<vecTiled.size();a++){
			for (int b=0; b<vecTiled.at(0).size();b++) 
			{
				int type = vecTiled.at(a).at(b).type;
				if (type >= OBJECTS_MIN && type <= OBJECTS_MAX) 
				{
					// search for associated object
					vecTiled.at(a).at(b).associated = &searchTiled(a, type+1);
				} else if(type == LEVER_LEFT) {
					vecTiled.at(a).at(b).actionAssociated = searchTilesAssociatedForAction(a, INVISIBLE_LADDER);
				}else if(type == ELEBOX) {
					vecTiled.at(a).at(b).actionAssociated = searchTilesAssociatedForAction(a, LASER);
				}
				if (vecTiled.at(a).at(b).type==INVISIBLE_POSX) 
					this->setInvisibleRoom(a);
			}
		}
	}else {
		cout << "Unable to open file"; 
	}
}

bool glTiledLoader::isActive(int x,int y){
	return vecTiled.at(x).at(y).isActive();
}

void glTiledLoader::Update(){
	for (int a=0; a<vecTiled.size();a++){
		for (int b=0; a<vecTiled.at(0).size();b++){
			vecTiled.at(a).at(b).Update();
		}
	}
}

glTiled& glTiledLoader::getTile(int row , int column)
{
	assert (row >= 0 || column >= 0 || row < 100 || column < 20);
	return vecTiled.at(row).at(column);
}


void glTiledLoader::setActive(int x,int y){
	vecTiled.at(x).at(y).setDefinitelyActive();
}

void glTiledLoader::runActionOnAssociated(int x,int y){
	if(vecTiled.at(x).at(y).type == LEVER_LEFT)
		// change lever sprite
		vecTiled.at(x).at(y).type = LEVER_RIGHT;
	else
	{
		vecTiled.at(x).at(y).runActionOnAssociated();
	}
}

void glTiledLoader::runActionOnAssociatedLasers(int x,int y){
	if(vecTiled.at(x).at(y).type == LASER)
		vecTiled.at(x).at(y).type=0;
	vecTiled.at(x).at(y).runActionOnAssociatedLaser();
}

void glTiledLoader::runActionOnAssociatedLasersShowAgain(int x,int y) {	
	if(vecTiled.at(x).at(y).originalType == LASER)
		vecTiled.at(x).at(y).type=LASER;
	vecTiled.at(x).at(y).runActionOnAssociatedLaserShow();
}

float glTiledLoader::getLowerOpacity(int x,int y){
	float opacity = vecTiled.at(x).at(y).getLowerOpacity();
	if (opacity < 0.3){ 
		vecTiled.at(x).at(y).type=0;
	}
	return opacity;
}

bool glTiledLoader::isLadder(int x,int y){

	if (vecTiled.at(x).at(y).type >= LADDER_MIN && vecTiled.at(x).at(y).type <= LADDER_MAX){
		return true;
	}
	return false;
}

bool glTiledLoader::isKilledByLaser(int x, int y)
{
	if (vecTiled.at(x).at(y).type==LASER){
		return true;
	}
	return false;
}

bool glTiledLoader::isBlockableObject(int x, int y)
{
	if (((vecTiled.at(x).at(y).type >= OBJECTS_MIN  && vecTiled.at(x).at(y).type <= OBJECTS_MAX )||(vecTiled.at(x).at(y).type==LASER))&& vecTiled.at(x).at(y).type % 2 == 1){
		return true;
	}
	return false;
}

bool glTiledLoader::isWall(int x,int y){

	if (vecTiled.at(x).at(y).type >= GROUND_MIN && vecTiled.at(x).at(y).type <= GROUND_MAX){
		return true;
	}
	return false;
}

bool glTiledLoader::isFree(int x,int y){

	if (vecTiled.at(x).at(y).type == FREE){
		return true;
	}
	return false;
}

int glTiledLoader::getValue(int x,int y){

	return vecTiled.at(x).at(y).type;
}

int glTiledLoader::getMapWidth()
{
	return glSettings::TILE_WIDTH*amountOfColumns;
}

int glTiledLoader::getMapHeight()
{
	return glSettings::TILE_HEIGHT*amountOfRows;
}

///////////////
// (0,0)
//
//
//
// (TILE_HEIGHT*ilo��, 0) -> HEROES
void glTiledLoader::getTileCoords(float posX, float posY, glHero::PLAYER playerId, int& tileRow, int& tileColumn)
{
	tileRow = (int)posY/glSettings::TILE_HEIGHT;
	tileColumn = (int)posX/glSettings::TILE_WIDTH;

	if(playerId == glHero::PLAYER::SND)
	{
		tileColumn += 10;
	}
}

sf::FloatRect glTiledLoader::getTileBoundingBox(int row, int col, glHero::PLAYER playerId)
{
	if(playerId == glHero::PLAYER::FST)
		return sf::FloatRect(col*glSettings::TILE_WIDTH, row*glSettings::TILE_HEIGHT, glSettings::TILE_HEIGHT,  glSettings::TILE_WIDTH);
	else 
		return sf::FloatRect(col*glSettings::TILE_WIDTH-640, row*glSettings::TILE_HEIGHT, glSettings::TILE_HEIGHT,  glSettings::TILE_WIDTH);
}

bool glTiledLoader::intersectsWithWall(glHero& hero)
{
	int firstTileRow, firstTileColumn;
	int row, column;
	bool debug = false;
	sf::Sprite sprite = hero.getSpirte();

	getTileCoords(sprite.getGlobalBounds().left+sprite.getTextureRect().width/2, sprite.getGlobalBounds().top + sprite.getTextureRect().height/2, hero.playerId, row, column);

	if(debug)
	{
		cout << "Sprite position: (" << sprite.getGlobalBounds().left << ", " << sprite.getGlobalBounds().top << ")" << endl; 
		cout << "Checking tile area for collision: " << row << ", " << column << " Intersects: " << sprite.getGlobalBounds().intersects(getTileBoundingBox(row, column, hero.playerId)) 
			<< " Is wall: " << isWall(row, column) <<  endl;
		cout << "Tile position: (" << getTileBoundingBox(row, column, hero.playerId).left << ", " << getTileBoundingBox(row, column, hero.playerId).top << ")" << endl;
	}

	for(int i = -1; i <= 1; ++i)
	{
		for(int j = -1; j <= 1; ++j)
		{
			if(row+i < 0 || column+j < 0 || row+i >= amountOfRows || column+j >= amountOfColumns)
				continue;
			if(sprite.getGlobalBounds().intersects(getTileBoundingBox(row+i, column+j, hero.playerId)) && isWall(row+i, column+j))
			{
				return true;
			}
		}
	}
	
	return false;
}

bool glTiledLoader::blockedByObstacleOnLeftSide(glHero& hero)
{
	int firstTileRow, firstTileColumn;
	int row, column;
	bool debug = false;
	sf::Sprite sprite = hero.getSpirte();
	sf::FloatRect spriteBB = sprite.getGlobalBounds();
	spriteBB.height -= 5.f;

	getTileCoords(sprite.getPosition().x+sprite.getTextureRect().width/2, sprite.getPosition().y + sprite.getTextureRect().height/2, hero.playerId, row, column);

	if(debug)
	{
		cout << "Sprite position: (" << sprite.getGlobalBounds().left << ", " << sprite.getGlobalBounds().top << ")" << endl; 
		cout << "Checking tile area for collision: " << row << ", " << column << " Intersects: " << sprite.getGlobalBounds().intersects(getTileBoundingBox(row, column, hero.playerId)) 
			<< " Is wall: " << isWall(row, column) <<  endl;
		cout << "Tile position: (" << getTileBoundingBox(row, column, hero.playerId).left << ", " << getTileBoundingBox(row, column, hero.playerId).top << ")" << endl;
	}

	for(int i = -1; i <= 1; ++i)
	{
		for(int j = -1; j <= 0; ++j)
		{
			if(row+i < 0 || column+j < 0 || row+i >= amountOfRows || column+j >= amountOfColumns)
				continue;
			if(spriteBB.intersects(getTileBoundingBox(row+i, column+j, hero.playerId)) && (isWall(row+i, column+j) || isBlockableObject(row+i, column+j)))
			{
				return true;
			}
		}
	}
	
	return false;
}


bool glTiledLoader::blockedByObstacleOnRightSide(glHero& hero)
{
	int firstTileRow, firstTileColumn;
	int row, column;
	bool debug = false;
	sf::Sprite sprite = hero.getSpirte();
	sf::FloatRect spriteBB = sprite.getGlobalBounds();
	spriteBB.height -= 5.f;

	getTileCoords(sprite.getPosition().x+sprite.getTextureRect().width/2, sprite.getPosition().y + sprite.getTextureRect().height/2, hero.playerId, row, column);

	if(debug)
	{
		cout << "Sprite position: (" << sprite.getGlobalBounds().left << ", " << sprite.getGlobalBounds().top << ")" << endl; 
		cout << "Checking tile area for collision: " << row << ", " << column << " Intersects: " << sprite.getGlobalBounds().intersects(getTileBoundingBox(row, column, hero.playerId)) 
			<< " Is wall: " << isWall(row, column) <<  endl;
		cout << "Tile position: (" << getTileBoundingBox(row, column, hero.playerId).left << ", " << getTileBoundingBox(row, column, hero.playerId).top << ")" << endl;
	}

	for(int i = -1; i <= 1; ++i)
	{
		for(int j = 0; j <= 1; ++j)
		{
			if(row+i < 0 || column+j < 0 || row+i >= amountOfRows || column+j >= amountOfColumns)
				continue;
			if(spriteBB.intersects(getTileBoundingBox(row+i, column+j, hero.playerId)) && (isWall(row+i, column+j) || isBlockableObject(row+i, column+j)))
			{
				return true;
			}
		}
	}
	
	return false;
}

bool glTiledLoader::intersectsWithLadder(glHero& hero)
{
	int firstTileRow, firstTileColumn;
	int row, column;
	bool debug = false;
	sf::Sprite sprite = hero.getSpirte();

	getTileCoords(sprite.getPosition().x+sprite.getTextureRect().width/2, sprite.getPosition().y + sprite.getTextureRect().height/2, hero.playerId, row, column);

	if(debug)
	{
		cout << "Sprite position: (" << sprite.getPosition().x<< ", " <<  sprite.getPosition().y << ")" << endl; 
		cout << "Checking tile area for collision: " << row << ", " << column << " Intersects: " << sprite.getGlobalBounds().intersects(getTileBoundingBox(row, column, hero.playerId)) 
			<< " Is ladder: " << isLadder(row, column) <<  endl;
		cout << "Tile position: (" << getTileBoundingBox(row, column, hero.playerId).left << ", " << getTileBoundingBox(row, column, hero.playerId).top << ")" << endl;
	}

	if(row < 0 || column < 0 || row >= amountOfRows || column >= amountOfColumns)
		return false;
	if(sprite.getGlobalBounds().intersects(getTileBoundingBox(row, column, hero.playerId)) && isLadder(row, column))
		return true;

	return false;
}