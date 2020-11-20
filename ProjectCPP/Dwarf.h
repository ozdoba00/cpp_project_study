#pragma once
#include "Entity.h"
class Dwarf :public Entity
{
private:
	enum States :signed int {
		IDLE = 0,
		WALK = 1,
		CUTTING = 2
	};

	enum Job :signed int {
		FREE,
		LUMBERJACK,
		MINER
	};
	int number;

	States dwarf_states;
	Job dwarf_job;
	void moveDwarf();
	//std::vector<int> m_pathPosX; std::vector<int> m_pathPosY;
	int m_pathPosX, m_pathPosY;
	sf::IntRect rectTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	void setDwarfColor();
	int velX, velY;


public:
	Dwarf(int number, sf::Vector2f pos);
	virtual ~Dwarf();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	virtual float getPosX() { return this->m_sprite.getPosition().x/12; }
	virtual float getPosY() { return this->m_sprite.getPosition().y/12; }

	int getNumberOfDwarf() { return this->number; }

	void setInstructionsMove(std::vector<int> pathPosX, std::vector<int> pathPosY, int index, int dwarfState);

	void setDwarfState(int state);
	void setDwarfJob(int job);

	Job getCurrentJob() const { return dwarf_job; }
	
	
	bool isSelected;

	bool getIsSelected() {  return this->isSelected; }


	std::vector<std::vector<int>> vecInsX;
	std::vector<std::vector<int>> vecInsY;

	void clearPathVec();
	std::vector<int> vecSizes;
	
protected:
	

	
};

