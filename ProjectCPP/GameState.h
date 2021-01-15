#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Interface.h"
#include "PathFinding.h"
#include "Dwarf.h"
#include "Map.h"
#include "Tree.h"
#include "Cursor.h"
#include "ObjectRenderMenager.h"
#include "Animal.h"
#include "Beaver.h"
#include "Bushes.h"
class GameState :
	public State
{
public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();
	void endState();

	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);


private:

	//Init functions
	void initMap();
	void initObjects();
	void keyboardUpdate();


	void setTileToRemove();
	//Map variables
	Map *map;
	sf::View *m_view;
	const int grid_map_size = 12;

	PathFinding* pathSystem;
	std::vector<PathFinding*> pathSystemVec;
	//Objects
	std::vector<Dwarf*> dwarves;
	std::vector<Tree*> trees;
	std::vector<Animal*> animals;
	std::vector<Bushes*> bushes;

	//Interface
	Interface* m_interface;

	Cursor *m_cursor;
	sf::Clock gameClock;

	ObjectRenderMenager objRenderMen;
	float gameTime;

	sf::Clock pathFindingClock;
	float pathTime;


	sf::Clock keyPressClock;
	float keyPressTime;

	void lumberjackUpdate();
	//Dwarves variables
	
};

#endif // !GAMESTATE_H