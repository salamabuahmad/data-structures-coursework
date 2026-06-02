#include "Pirate.h"
#include "Fleet.h"


int Pirate :: getID() const{
    return m_pirateID;
}

int Pirate::getRank() const{
    if(m_motherFleet.lock())
        return m_rank + m_motherFleet.lock() ->getRankDifference();
    return m_rank;
}

void Pirate::setRank(int newRank){
    m_rank = newRank;
}

int Pirate::getMoney() const{
    return m_money;
}

void Pirate::setMoney(int newMoney){
    m_money = newMoney;
}

void Pirate::increaseMoney(int amount){
    m_money += amount;
}

shared_ptr<Fleet> Pirate::getFleet() const{
    return m_motherFleet.lock();
}

void Pirate::setFleet(shared_ptr<Fleet> fleet){
    m_motherFleet = fleet;
} // not supposed to be used
