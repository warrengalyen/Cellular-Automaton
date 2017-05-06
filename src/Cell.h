#pragma once

#include <string>
#include "Utility.h" 

using namespace std ;

class Cell
{
public:
	Cell(int const& health, int const& force, int const& team) ;
	void setHealth(int const& health) ;
	void setMaxHealth(int const& maxHealth) ;
	void setForce(int const& force) ;
	void setMaxForce(int const& maxForce) ;
	void setTeam(int const& team) ;
	int getHealth() const ;
	int getMaxHealth() const ;
	int getForce() const ;
	int getMaxForce() const ;
	int getTeam() const ;
	
private:
	int m_health ;
	int m_maxHealth ;
	int m_force ;
	int m_maxForce ;
	int m_team ;
};

