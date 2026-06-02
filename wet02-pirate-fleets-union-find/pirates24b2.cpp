#include "pirates24b2.h"

oceans_t::oceans_t()
{
	m_fleetsCounter = 0;
	m_pirates = make_shared<HashTable<int,shared_ptr<Pirate>>>();
	m_fleetsHash = make_shared<HashTable<int,shared_ptr<Fleet>>>();
	m_fleetsUnionFind = make_shared<UnionFind>();
}

oceans_t::~oceans_t()
{
	// TODO: Your code goes here
	//NOTHING TO DO...
}


StatusType oceans_t::add_fleet(int fleetId)
{
	if(fleetId <= 0)
		return StatusType::INVALID_INPUT;
	
	if(m_fleetsHash->findItem(fleetId))
		return StatusType::FAILURE;

	shared_ptr<Fleet> fleet;

	try {
		fleet = make_shared<Fleet>(fleetId);
	}
	catch (const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	
	m_fleetsHash -> insertItem(fleetId, fleet);
	m_fleetsUnionFind -> Makeset(m_fleetsCounter);
	fleet -> setCounter(m_fleetsCounter);
	m_fleetsCounter ++;
	return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{
	if(pirateId <= 0 || fleetId <= 0)
		return StatusType::INVALID_INPUT;

	if(m_pirates -> findItem(pirateId) || !((m_fleetsHash->findItem(fleetId)).get()))
		return StatusType::FAILURE;

	shared_ptr<Fleet> fleet = m_fleetsHash->findItem(fleetId);
	if(fleet -> isUsed())
		return StatusType::FAILURE;

	shared_ptr<Pirate> pirate;

	try {
		pirate = make_shared<Pirate>(pirateId,fleet->getPiratesAmount() + 1,fleet);
	}
	catch (const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}

	m_pirates -> insertItem(pirateId, pirate);
	fleet ->addPirate(pirate);
	return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
	if(pirateId <= 0 || salary <= 0)
		return StatusType::INVALID_INPUT;

	shared_ptr<Pirate> pirate = m_pirates -> findItem(pirateId);
	if(!pirate)
		return StatusType::FAILURE;	

	pirate ->increaseMoney(salary);
	return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
    if(fleetId <= 0)
		return output_t<int>(StatusType::INVALID_INPUT);
	
	shared_ptr<Fleet> fleet = m_fleetsHash -> findItem(fleetId);
	if(!fleet || fleet -> isUsed())
		return output_t<int>(StatusType::FAILURE);
	
    return output_t<int>(fleet ->getShipsAmount());
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
	if(pirateId <= 0)
		return output_t<int>(StatusType::INVALID_INPUT);


	shared_ptr<Pirate> pirate = m_pirates -> findItem(pirateId);
	if(!pirate)
		return output_t<int>(StatusType::FAILURE);
	
	return output_t<int>(pirate ->getMoney());

}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
	if(fleetId1 <= 0 || fleetId2 <= 0 || fleetId1 == fleetId2)
		return StatusType::INVALID_INPUT;
	
	shared_ptr<Fleet> fleet1 = m_fleetsHash -> findItem(fleetId1);
	shared_ptr<Fleet> fleet2 = m_fleetsHash -> findItem(fleetId2);
	if(!fleet1 || !fleet2 || fleet1 -> isUsed() || fleet2 -> isUsed() || fleet1 -> getPiratesAmount() == 0 || fleet2 -> getPiratesAmount() == 0 )
		return StatusType :: FAILURE;

	int pirates1 = fleet1 -> getPiratesAmount();
	int pirates2 = fleet2 -> getPiratesAmount();
	if(pirates1 >= pirates2){
		m_fleetsUnionFind -> Union(fleet1 -> getCounter(), fleet2 -> getCounter());
		fleet1 -> addShips(fleet2 ->getShipsAmount());
		fleet2 -> increaseRankDifference(fleet1 ->getPiratesAmount());
		fleet1 -> addMultiplePirates(fleet2 ->getPiratesAmount());
		fleet2 -> setMotherFleet(fleet1);
	} else {
		m_fleetsUnionFind -> Union(fleet2 -> getCounter(), fleet1 -> getCounter());
		fleet2 -> addShips(fleet1 ->getShipsAmount());
		fleet1 -> increaseRankDifference(fleet2 ->getPiratesAmount());
		fleet2 -> addMultiplePirates(fleet1 ->getPiratesAmount());
		fleet1 -> setMotherFleet(fleet2);

	}
    return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
    if(pirateId1 <= 0 || pirateId2 <= 0 || pirateId1 == pirateId2)
		return StatusType::INVALID_INPUT;
	
	shared_ptr<Pirate> pirate1 = m_pirates -> findItem(pirateId1);
	shared_ptr<Pirate> pirate2 = m_pirates -> findItem(pirateId2);
	if(!pirate1){
		//cout << "Failed - Pirate" << pirateId1 <<" DNE";
		return StatusType::FAILURE;
	}
	if(!pirate2){
		//cout << "Failed - Pirate" << pirateId2 <<" DNE";
		return StatusType::FAILURE;
	}

	if(!pirate1->getFleet() || !pirate2->getFleet()){
		return StatusType::FAILURE;
	}

	if(m_fleetsUnionFind->Find(pirate1->getFleet()->getCounter()) != m_fleetsUnionFind->Find(pirate2->getFleet()->getCounter())){
		return StatusType::FAILURE;
	}

	if(pirate2 -> getRank() > pirate1 ->getRank()){
		shared_ptr<Pirate> temp = pirate1;
		pirate1 = pirate2;
		pirate2 = temp;
	}

	int diff = pirate1 -> getRank() - pirate2 -> getRank();
	pirate1 -> increaseMoney(-1 * diff);
	pirate2 -> increaseMoney(diff);

    return StatusType::SUCCESS;
}
