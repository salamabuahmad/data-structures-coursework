#include "pirates.h"


int Pirate :: getPirateID() const{
    return m_pirateID;
}

int Pirate :: getPirateTreasure() const{
    return m_treasure;
}
void Pirate :: setPirateTreasure(int treasure){
    m_treasure = treasure;
}
void Pirate :: increaseTreasure(int amount){
    m_treasure += amount;
}
shared_ptr<Ship> Pirate :: getMotherShip() const{
    return m_motherShip;
}
void Pirate :: setMotherShip(shared_ptr<Ship> motherShip){
    m_motherShip = motherShip;
}

int Pirate::getKey() const{
    return m_key;
}

void Pirate::setKey(int key){
    m_key = key;
}