#include "Fleet.h"

int Fleet::getID() const
{
    if (m_motherFleet != nullptr)
        return m_fleetID;
    return m_motherFleet->getID();
}

int Fleet::getShipsAmount() const
{
    return m_shipsAmount;
}

void Fleet::addShips(int shipsNum)
{
    m_shipsAmount += shipsNum;
}

int Fleet::getPiratesAmount() const
{
    return m_piratesAmount;
}

void Fleet::addMultiplePirates(int piratesNum)
{
    m_piratesAmount += piratesNum;
}

void Fleet::addPirate(shared_ptr<Pirate> pirate)
{
    m_pirateHash->insertItem(pirate->getID(),pirate);
    m_piratesAmount++;
} 

shared_ptr<Fleet> Fleet::getMotherFleet() const
{
    return m_motherFleet;
}

void Fleet::setMotherFleet(shared_ptr<Fleet> fleet)
{
    m_motherFleet = fleet;
}

int Fleet::getCounter() const
{
    return m_fleetCounter;
}

void Fleet::setCounter(int newCounter)
{
    m_fleetCounter = newCounter;
}

int Fleet::getRankDifference() const
{
    if(m_motherFleet)
        return m_rankDifference + m_motherFleet -> getRankDifference();
    return m_rankDifference;
}

void Fleet::increaseRankDifference(int difference)
{
    m_rankDifference += difference;
}

bool Fleet::isUsed() const
{
    if (m_motherFleet)
        return true;
    return false;
}
