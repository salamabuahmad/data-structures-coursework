#include "pirates24b1.h"


Ocean::Ocean()
{
    m_ships = AVLTree<int, shared_ptr<Ship>>();
    m_pirates = AVLTree<int, shared_ptr<Pirate>>();
}

Ocean::~Ocean()
{
    m_ships.~AVLTree();
    m_pirates.~AVLTree();
}

StatusType Ocean::add_ship(int shipId, int cannons)
{
    if (shipId <= 0 || cannons <= 0) 
        return StatusType::INVALID_INPUT;
    if(m_ships.search(shipId) != nullptr)
        return StatusType::FAILURE;

    shared_ptr<Ship> ship = make_shared<Ship>(shipId,cannons);

    if(!ship)
        return StatusType::ALLOCATION_ERROR;
    
    m_ships.insert(shipId,ship);
    return StatusType::SUCCESS;
}

StatusType Ocean::remove_ship(int shipId)
{
    if(shipId <= 0)
        return StatusType::INVALID_INPUT;
    
    shared_ptr<Ship> ship = m_ships.search(shipId);

    if(ship == nullptr || !ship->isEmpty())
        return StatusType::FAILURE;

    m_ships.remove(shipId);
    return StatusType::SUCCESS;
}

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure)
{
    if(pirateId <= 0 || shipId <= 0)
        return StatusType::INVALID_INPUT;
    if(m_pirates.search(pirateId) != nullptr || m_ships.search(shipId) == nullptr)
        return StatusType::FAILURE;
    
    shared_ptr<Ship> ship = m_ships.search(shipId);
    shared_ptr<Pirate> pirate = make_shared<Pirate>(pirateId,ship,treasure);
    if (!pirate)
        return StatusType::ALLOCATION_ERROR;
    
    ship->addPirate(pirate);
    m_pirates.insert(pirateId,pirate);
    return StatusType::SUCCESS;
}

StatusType Ocean::remove_pirate(int pirateId)
{
    if(pirateId <= 0)
        return StatusType::INVALID_INPUT;
    
    shared_ptr<Pirate> pirate = m_pirates.search(pirateId);
    if(!pirate)
        return StatusType::FAILURE;
    
    pirate->getMotherShip()->removePirateById(pirateId);
    m_pirates.remove(pirateId);

    return StatusType::SUCCESS;
}

StatusType Ocean::treason(int sourceShipId, int destShipId)
{
    if(sourceShipId<= 0 || destShipId <= 0 || destShipId == sourceShipId)
        return StatusType::INVALID_INPUT;
    
    shared_ptr<Ship> ship1 = m_ships.search(sourceShipId);
    shared_ptr<Ship> ship2 = m_ships.search(destShipId);

    if(ship1 == nullptr || ship2 == nullptr || ship1->isEmpty())
        return StatusType::FAILURE;
    
    shared_ptr<Pirate> pirate = ship1 -> getOldest();
    ship1 ->removePirateById(pirate->getPirateID());
    ship2 -> addPirate(pirate);

    return StatusType::SUCCESS;
}

StatusType Ocean::update_pirate_treasure(int pirateId, int change)
{
    if(pirateId <= 0)
        return StatusType::INVALID_INPUT;
    
    shared_ptr<Pirate> pirate = m_pirates.search(pirateId);
    if(pirate == nullptr)
        return StatusType::FAILURE;

    pirate->getMotherShip()->updatePirateTreasure(pirateId,change);

    return StatusType::SUCCESS;
}

output_t<int> Ocean::get_treasure(int pirateId)
{
    if(pirateId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    shared_ptr<Pirate> pirate = m_pirates.search(pirateId);
    if(pirate == nullptr)
        return output_t<int>(StatusType::FAILURE);
    
    return output_t<int>(pirate->getPirateTreasure());
}

output_t<int> Ocean::get_cannons(int shipId)
{
    if(shipId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    shared_ptr<Ship> ship = m_ships.search(shipId);
    if(ship == nullptr)
        return output_t<int>(StatusType::FAILURE);
    
    return output_t<int>(ship->getCanonsAmonut());
}

output_t<int> Ocean::get_richest_pirate(int shipId)
{
    if(shipId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    shared_ptr<Ship> ship = m_ships.search(shipId);
    if(ship == nullptr || ship->isEmpty())
        return output_t<int>(StatusType::FAILURE);

    return output_t<int>(ship->getRichestPirate());
}

StatusType Ocean::ships_battle(int shipId1,int shipId2)
{
    if(shipId1 <= 0 || shipId2 <= 0 || shipId1 == shipId2)
        return StatusType::INVALID_INPUT;
    
    shared_ptr<Ship> ship1 = m_ships.search(shipId1);
    shared_ptr<Ship> ship2 = m_ships.search(shipId2);

    if(ship1 == nullptr || ship2 == nullptr)
        return StatusType::FAILURE;
    
    int m1 = min(ship1->getCanonsAmonut(),ship1->getPirateAmount());
    int m2 = min(ship2->getCanonsAmonut(),ship2->getPirateAmount());
    
    if(m1 == m2) return StatusType::SUCCESS;

    int buff1 = ship2 -> getPirateAmount();
    int buff2 = ship1 -> getPirateAmount();

    if(m1 < m2) 
        buff1 *= -1;
    else buff2 *= -1;

    ship1->updateTreasure(buff1);
    ship2 -> updateTreasure(buff2);

    return StatusType::SUCCESS;
}



