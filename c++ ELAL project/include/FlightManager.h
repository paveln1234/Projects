#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H
#include <map>
#include <string>
using namespace std;

class FullFlightInterface;

class FlightData_t;
class Iplane;
class FlightFactory;
class PlaneManager;

class FlightManager
{
    public:
        FlightManager();
        virtual ~FlightManager();

        /** add new flight to scheduler - for futer cane be add flight Type for difrent types;
        * \param const string& _plainId - plain id
        * \param FlightData_t* _flightData - flight data pointer
        * \param size_t _prise - prise of the flight
        * \return size_t flight number
        * \warning if Null plain given exception will throw <int = -1>
        */
         size_t AddFlight(const Iplane* _plain,FlightData_t* _flightData,size_t _prise);

        /** Remove flight from scheduler
        * \param size_t _flightNumber - flight number to remove
        * \return bool if success , false if wrong flight number given
        */
        const bool RemoveFlight(size_t _flightNumber);

        /** Update flight data
        * \param size_t _flightNumber - flight number to remove
        * \param FlightData_t* _flightData - flight data pointer whit new ditels
        * \return bool if success , false if wrong flight number given
        * \warning no check for Corette flight data
        */
        const bool UpdateFlight(size_t _flightNumber,FlightData_t* _flightData);

        /** Update flight prise
        * \param size_t _flightNumber - flight number to remove
        * \param size_t _prise, new prise
        * \return bool if success , false if wrong flight number given
        */
        const bool UpdateFlight(size_t _flightNumber,size_t _prise);

        /** Get Flight
        * \param size_t _flightNumber - flight number to remove
        * \return FullFlightInterface* - const pointer to the flight
        */
         const FullFlightInterface* GetFlight(size_t _flightNumber);

        /** Get Flights number
        * \return size_t Flight number
        */
        size_t GetFlightNumber(){return m_flights.size();}

        /** Print All Flight Details */
        void PrintAllFlights()const;

    private:
        map<size_t,FullFlightInterface*> m_flights;
        static size_t m_counter;
        PlaneManager* planeManager;
        FlightFactory* m_FlightFacorty;

};

#endif // FLIGHTMANAGER_H
