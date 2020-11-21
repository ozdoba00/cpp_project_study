#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	:State(window)
{
	
	initMap();
	initObjects();
}

GameState::~GameState()
{

}

void GameState::endState()
{
}

void GameState::updateKeybinds(const float& dt)
{
	this->checkForQuit();

}

void GameState::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->keyboardUpdate();

	this->gameTime = this->gameClock.getElapsedTime().asSeconds();

	
	if (gameTime > 0.5f) {

		
		this->lumberjackUpdate();
		this->pathSystem->setLevelData(this->map->getLevelData());
		for (auto& dwarf : dwarves) {
			dwarf->update(dt);
		}
		this->gameClock.restart();

		
	}
}

void GameState::render(sf::RenderTarget* target)
{	
	
	this->map->render(window);
	this->window->setView(this->m_view);
	for (auto& dwarf : dwarves) {
		dwarf->render(window);
	}
	for (auto& tree : trees) {
		tree->render(window);
	}

	
}

void GameState::initMap()
{

	this->map = new Map();
	this->m_view = sf::View(sf::FloatRect(0, 0, 400.f, 300.f));

	pathSystem = new PathFinding(this->window, sf::Vector2u(800.f, 600.f));
	this->pathSystem->setLevelData(this->map->getLevelData());
	
	

}
void GameState::initObjects()
{
	
	dwarves.push_back(new Dwarf(1, sf::Vector2f(this->grid_map_size*1, this->grid_map_size*2)));
	dwarves.push_back(new Dwarf(2, sf::Vector2f(this->grid_map_size * 8, this->grid_map_size * 2)));
	dwarves.push_back(new Dwarf(3, sf::Vector2f(this->grid_map_size * 4, this->grid_map_size * 7)));

	/*for (int i = 0; i < 3; i++) {
		dwarves.push_back(new Dwarf(i + 1, sf::Vector2f(this->grid_map_size * 5 + grid_map_size*(i + 2), this->grid_map_size * 4 + grid_map_size*(i + 1))));
	} */
	for (int i = 0; i < this->map->getLevelData().size() / 8; i++) {
		for (int j = 0; j < this->map->getLevelData().size() / 10; j++) {
			if (this->map->getLevelData()[i + j * this->map->getLevelData().size() / 8] == 4) {
				this->trees.push_back(new Tree(sf::Vector2f(this->grid_map_size * i, this->grid_map_size * j), i * this->map->getLevelData().size() / 10 + j));
				
				
			}
		}
	}
	

}

void GameState::keyboardUpdate()
{
	
	for (auto& dwarf : dwarves) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			dwarf->isSelected = false;
			if (dwarf->getNumberOfDwarf() == 1) {
				if (!dwarf->getIsSelected()) {
					std::cout << "wybrales dwarfa o numerze " << dwarf->getNumberOfDwarf() << std::endl;
					dwarf->isSelected = true;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			dwarf->isSelected = false;
			if (dwarf->getNumberOfDwarf() == 2) {
				
				if (!dwarf->getIsSelected()) {
					std::cout << "wybrales dwarfa o numerze "<<dwarf->getNumberOfDwarf() << std::endl;
					dwarf->isSelected = true;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			dwarf->isSelected = false;
			if (dwarf->getNumberOfDwarf() == 3) {

				if (!dwarf->getIsSelected()) {
					std::cout << "wybrales dwarfa o numerze " << dwarf->getNumberOfDwarf() << std::endl;
					dwarf->isSelected = true;
				}
			}
		}
		if (dwarf->getIsSelected()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			
				std::cout << "Dwarf number : " << dwarf->getNumberOfDwarf() << " is now a lumberjack!" << std::endl;
				dwarf->setDwarfJob(1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{	
			if (dwarf->getIsSelected())
			{
				std::cout << "Odznaczeni" << std::endl;
				dwarf->isSelected = false;
			}

		}
	}

	
	
}

void GameState::lumberjackUpdate()
{
	for (auto& dwarf : dwarves) { //Path to tree

		if (dwarf->getCurrentJob() == 1)
		{
			
			for (int i = 0; i < trees.size(); i++) {

				this->pathSystem->setStartEndNodes(trees[i]->getPosX(), trees[i]->getPosY(), dwarf->getPosX(), dwarf->getPosY());
				this->pathSystem->SolveAStar();
				this->pathSystem->update();
				dwarf->setInstructionsMove(this->pathSystem->getPathPosX(), this->pathSystem->getPathPosY(), this->trees.size(), 2); //2 to wartosc stanu dwarfa - w tym przypadku to CUTTING
				this->pathSystem->clearPathVector();
				

			}
			dwarf->clearPathVec();
		}
	}

	/* #####################*/

	//Cutting trees

	for (auto& dwarf : dwarves) {
		if (dwarf->getCurrentJob() == 1) {
			
			for (int i = 0; i < trees.size(); i++) {
				
				
					if ((this->trees[i]->getPosX() + 1 == dwarf->getPosX()) && (this->trees[i]->getPosY() == dwarf->getPosY()))
					{
						//std::cout <<"Indeksik: "<< this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[i]->cutTheTree(dwarf->getDwarfStrength());
					}
					if ((this->trees[i]->getPosX() - 1 == dwarf->getPosX()) && (this->trees[i]->getPosY() == dwarf->getPosY()))
					{
						//std::cout << "Indeksik: " << this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[i]->cutTheTree(dwarf->getDwarfStrength());
					}
					if ((this->trees[i]->getPosY() - 1 == dwarf->getPosY()) && (this->trees[i]->getPosX() == dwarf->getPosX()))
					{
						//std::cout << "Indeksik: " << this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[i]->cutTheTree(dwarf->getDwarfStrength());
					}
					if ((this->trees[i]->getPosY() + 1 == dwarf->getPosY()) && (this->trees[i]->getPosX() == dwarf->getPosX()))
					{
						//std::cout << "Indeksik: " << this->trees[i]->getIndexOfTree() << std::endl;
						this->trees[i]->cutTheTree(dwarf->getDwarfStrength());
					}

					if (trees[i]->getHpOfTree() == 0) {
						this->map->updateMapTitle(trees[i]->getPosX(), trees[i]->getPosY(), 2);
						this->trees.erase(trees.begin() + i);

					}
					
				
			}
		}
	}
}

