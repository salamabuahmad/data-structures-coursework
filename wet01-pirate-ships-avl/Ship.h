#ifndef SHIPS
#define SHIPS
#include "Pirates.h"
#include "AVLTree.h"
using namespace std;

class Pirate;

class Ship {
    private:
        int m_shipID;
        int m_canonsAmount;
        int m_pirateCounter;
        int m_piratesAmount;
        int m_treasureBuffer;
        shared_ptr<Pirate> m_richestPirate;

        AVLTree<int,shared_ptr<Pirate>> m_piratesById;
        AVLTree<int,shared_ptr<Pirate>> m_piratesByKey;
        AVLTree<int,shared_ptr<AVLTree<int,shared_ptr<Pirate>>>> m_piratesByTreasure;

    public:
        Ship(int shipID , int canonsAmount) : m_shipID(shipID) , m_canonsAmount (canonsAmount) , m_pirateCounter(0), 
        m_piratesById(AVLTree<int,shared_ptr<Pirate>>()) , m_treasureBuffer(0), m_piratesAmount(0), m_piratesByKey(AVLTree<int,shared_ptr<Pirate>>()) ,m_richestPirate(nullptr), m_piratesByTreasure(AVLTree<int,shared_ptr<AVLTree<int,shared_ptr<Pirate>>>>()){};
        ~Ship() = default;
        Ship(const Ship&) = delete;
        Ship operator= (const Ship&) = delete;

        int getCanonsAmonut() const; 
        void setCanonsAmount(int);
        void increaseCounter(int i = 1);
        shared_ptr<Pirate> getWealthiest();
        shared_ptr<Pirate> getOldest();
        StatusType addPirate(shared_ptr<Pirate>); //Adds the pirate to the trees
        StatusType removePirateById(int); //removes the pirate from the trees
        void updateTreasure (int); //increases/decreases the treasure of every pirate the given amount
        shared_ptr<Pirate> removeOldestPirate();
        StatusType updatePirateTreasure(int,int);
        int getRichestPirate() const;
        bool isEmpty() const;
        int getPirateAmount() const;
};




#endif // SHIPS