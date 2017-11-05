#ifndef CEASERMANAGER_H
#define CEASERMANAGER_H
#include <vector>
#include <string>

using namespace std;
class FlightManager;
class PassengerManager_t;
class ResrveationSystem;
class BookingManager;
class Comunicator;
class CeaserManager
{
    public:
        /** Default constructor */
        CeaserManager();
        /** Default destructor */
        virtual ~CeaserManager();
        /**
        *   Initialize the system
        */
        void Create();
        void Run();
        void Destroy();

    private:
        FlightManager* m_flightManager;
        PassengerManager_t* m_passengerManager;
        BookingManager* m_bookingManager;
        ResrveationSystem* m_resrveationSystem;
        Comunicator* m_comunicator;

};

#endif // CEASERMANAGER_H
