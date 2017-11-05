#ifndef FLIGHTDATA_T_H
#define FLIGHTDATA_T_H
#include <string>
#include "AirPort.h"

using namespace std;
class AirPort;

class FlightData_t
{
    public:
        /** Default constructor */
        FlightData_t();
        /** Default destructor */
        virtual ~FlightData_t();
        void Create();

        void SetDepartureAirPort(const AirPort* _depatureAirPort){m_departure = _depatureAirPort;}
        const AirPort* GetDeparture()const {return m_departure;}
        void SetArrivelAirPort(const AirPort* _arrivelAirPort){m_arrivel = _arrivelAirPort;}
        const AirPort* GetArrivelAirPort()const {return m_arrivel;}
        void SetDepartureTime(const string& _departureTime){m_departedTime = _departureTime;}
        const string& GetDepartureTime()const {return m_departedTime;}
        void SetArrivelTime(const string& _arrivelTime) {m_arrivelTime = _arrivelTime;}
        const string& GetArrivelTime()const {return m_arrivelTime;}
        void SetDepartureDate(const string& _departureDate) {m_departedDate = _departureDate;}
        const string& GetDepartureDate()const {return m_departedDate;}
        void SetArrivelDate(const string& _arrivelDate) {m_arrivelDate = _arrivelDate;}
        const string& GetArrivelDate()const {return m_arrivelDate;}
        void SetFlightId(const string& _flightId) {m_flightId = _flightId;}
        const string& GetFlightId(){return m_flightId;}
        const string& GetFlightDetails()const;

    private:
        AirPort const* m_departure;
        AirPort const * m_arrivel;
        string m_departedTime;
        string m_departedDate;
        string m_arrivelTime;
        string m_arrivelDate;
        string m_flightId;
};

#endif // FLIGHTDATA_T_H
