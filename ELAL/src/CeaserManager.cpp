#include "CeaserManager.h"
#include "FlightManager.h"
#include "PassengerManager_t.h"
#include "BookingManager.h"
#include "ResrveationSystem.h"
#include "Comunicator.h"
using namespace std;
CeaserManager::CeaserManager()
{
    //ctor
}

CeaserManager::~CeaserManager()
{
    delete m_flightManager;
    delete m_passengerManager;
    delete m_bookingManager;
    delete m_resrveationSystem;

}

void CeaserManager::Create()
{
    m_flightManager = new FlightManager;
    m_passengerManager = new PassengerManager_t;
    m_bookingManager = new BookingManager;
    m_resrveationSystem = new ResrveationSystem;

}



