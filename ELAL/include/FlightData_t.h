#ifndef FLIGHTDATA_T_H
#define FLIGHTDATA_T_H
#include <string>
#include "AirPort.h"
#include "UserDataFlightDataInt.h"

using namespace std;
class AirPort;

class FlightData_t : public UserDataFlightDataInt
{
    public:
        /** Default constructor */
        FlightData_t();
        /** Default destructor */
        virtual ~FlightData_t();
        void Create();

        /** Set Departure air port
        * \param const AirPort* _depatureAirPort = new depature air port;
        */
        void SetDepartureAirPort(const AirPort* _depatureAirPort){m_departure = _depatureAirPort;}

        /** Get Departure air port
        * \return const AirPort*  - depature air port;
        */
        const AirPort* GetDeparture()const {return m_departure;}

        /** Get Departure air port code
        * \return const string& - departue air port code
        */
        const string& GetDepartureAirPortCode()const {return m_departure->GetCode();}

        /** Set Arriver air port
        * \param const AirPort* _arrivelAirPort = new Arriver air port;
        */
        void SetArrivelAirPort(const AirPort* _arrivelAirPort){m_arrivel = _arrivelAirPort;}

        /** Get Arriver air port
        * \return const AirPort*  - Arriver air port;
        */
        const AirPort* GetArrivelAirPort()const {return m_arrivel;}

        /** Get Arriver air port code
        * \return const string& - Arriver air port code
        */
        const string& GetArrivelAirPortCode()const {return m_arrivel->GetCode();}
        void SetDepartureTime(const string& _departureTime){m_departedTime = _departureTime;}
        const string& GetDepartureTime()const {return m_departedTime;}
        void SetArrivelTime(const string& _arrivelTime) {m_arrivelTime = _arrivelTime;}
        const string& GetArrivelTime()const {return m_arrivelTime;}
        void SetDepartureDate(const string& _departureDate) {m_departedDate = _departureDate;}
        const string& GetDepartureDate()const {return m_departedDate;}
        void SetArrivelDate(const string& _arrivelDate) {m_arrivelDate = _arrivelDate;}
        const string& GetArrivelDate()const {return m_arrivelDate;}
        void SetFlightId(const string& _flightId) {m_flightId = _flightId;}
        virtual const string& GetFlightId()const {return m_flightId;}
        virtual const string& GetFlightDetails()const;

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
