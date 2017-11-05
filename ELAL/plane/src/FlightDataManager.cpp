#include "FlightDataManager.h"

FlightDataManager::FlightDataManager()
{
    //ctor
}

FlightDataManager::~FlightDataManager()
{
    //dtor
}

FlightDataManager::FlightDataManager(const FlightDataManager& other)
{
    //copy ctor
}

FlightDataManager& FlightDataManager::operator=(const FlightDataManager& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
