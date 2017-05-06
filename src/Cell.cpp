#include "Cell.h"

Cell::Cell(int const& maxHealth, int const& maxForce, int const& team)
{
	m_health = maxHealth ;
	m_force = maxForce ;
	m_maxHealth = maxHealth ;
	m_maxForce = maxForce ;
	m_team = team ;
}
void Cell::setHealth(int const& health)
{
	m_health = clamp(health,0,m_maxHealth) ;
}
void Cell::setMaxHealth(int const& maxHealth)
{
	m_maxHealth = maxHealth ;
}
void Cell::setForce(int const& force)
{
	m_force = clamp(force,0,m_maxForce) ;
}
void Cell::setMaxForce(int const& maxForce)
{
	m_maxForce = maxForce ;
}
void Cell::setTeam(int const& team)
{
	m_team = team ;
}
int Cell::getHealth() const
{
	return m_health ;
}
int Cell::getMaxHealth() const
{
	return m_maxHealth ;
}
int Cell::getForce() const
{
	return m_force ;
}
int Cell::getMaxForce() const
{
	return m_maxForce ;
}
int Cell::getTeam() const
{
	return m_team ;
}
