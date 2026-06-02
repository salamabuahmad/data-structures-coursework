#include "Ship.h"

int Ship::getCanonsAmonut() const{
    return m_canonsAmount;
}
void Ship::setCanonsAmount(int amount){
    m_canonsAmount = amount;
}
void Ship::increaseCounter(int i) {
    m_pirateCounter += i;
}
shared_ptr<Pirate> Ship::getWealthiest() {
    shared_ptr<AVLTree<int,shared_ptr<Pirate>>> temp = m_piratesByTreasure.maxValue();
    return temp -> maxValue();
}

shared_ptr<Pirate> Ship::getOldest(){
    return m_piratesByKey.search(m_piratesByKey.minKey());
}
StatusType Ship::addPirate(shared_ptr<Pirate> pirate){
    if(!pirate) return StatusType::INVALID_INPUT;
    m_piratesAmount++;
    m_pirateCounter++;

    int id = pirate -> getPirateID();
    pirate -> increaseTreasure(-1 * m_treasureBuffer);

    int key = m_pirateCounter;
    pirate -> setKey(key);
    int t_key = pirate-> getPirateTreasure();

    m_piratesById.insert(id,pirate);
    m_piratesByKey.insert(key,pirate);
    if(!m_piratesByTreasure.search(t_key)) m_piratesByTreasure.insert(t_key,make_shared<AVLTree<int,shared_ptr <Pirate>>>());
    m_piratesByTreasure.search(t_key)->insert(id,pirate);

    m_richestPirate = m_piratesByTreasure.maxValue()->maxValue();
}

StatusType Ship::removePirateById(int id){
    if(!m_piratesById.search(id)) return StatusType::INVALID_INPUT;
    shared_ptr<Pirate> pirate = m_piratesById.search(id);
    m_piratesByKey.remove(pirate -> getKey());
    m_piratesByTreasure.search(pirate -> getPirateTreasure())->remove(id);
    if(!m_piratesByTreasure.search(pirate -> getPirateTreasure()) -> getRoot()){
        m_piratesByTreasure.remove(pirate -> getPirateTreasure());
    }
    m_piratesById.remove(id);
    pirate->setMotherShip(nullptr);
    pirate -> increaseTreasure(m_treasureBuffer);

    m_richestPirate = m_piratesByTreasure.maxValue()->maxValue();
    m_piratesAmount--;
}

void Ship::updateTreasure (int amount){
    m_treasureBuffer += amount;
}

shared_ptr<Pirate> Ship::removeOldestPirate(){
    shared_ptr<Pirate> pirate = m_piratesByKey.search(m_piratesByKey.minKey());
    removePirateById(pirate -> getPirateID());
    return pirate;
} //opon use, most make sure that the ship isn't empty

StatusType Ship::updatePirateTreasure(int id,int change){
    shared_ptr<Pirate> pirate = m_piratesById.search(id);
    if (!pirate) return StatusType::FAILURE;

    int oldKey = pirate -> getPirateTreasure();
    m_piratesByTreasure.search(oldKey)->remove(id);

    pirate->increaseTreasure(change);
    int key = pirate -> getPirateTreasure();
    m_piratesByTreasure.search(key) -> insert(id,pirate);

    m_richestPirate = m_piratesByTreasure.maxValue()->maxValue();
    return StatusType::SUCCESS;
}

int Ship :: getRichestPirate() const{
    return m_richestPirate->getPirateID();
} //assumes that ship isn't empty

bool Ship::isEmpty() const{
    return m_piratesById.isEmpty();

}

int Ship :: getPirateAmount() const{
    return m_piratesAmount;
}