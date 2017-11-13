#ifndef FLIGHT_H
#define FLIGHT_H
#include <vector>
#include <map>
#include <string>
#include "FullFlightInterface.h"
#include "Iplane.h"
using namespace std;
class Tier_t;

class Flight : public FullFlightInterface
{
    public:
        enum FlightTier{ECONNOME,BISNESS};
        enum FlightSeatStatus{FREE_SEAT,TAKEN_SEAT,BAD_SEAT_NUMBER};
        /** Default constructor */
        Flight();
        /** Default destructor */
        virtual ~Flight();
        /** create new Plane */
        virtual void Create();

        /** Set Plane for the flight
        * \param const Iplane* _plane = new plane to the flight
        */
        virtual void SetPlain(const Iplane* _plane);

        /** Get Flight Plane
        * \return const Iplane* - Flight plane
        */
        virtual const Iplane* GetPlain()const{return m_plane;}

        /** Set Flight Data
        * \param const FlightData_t* _flightData = new Data to the flight
        */
        virtual void SetFlightData(const FlightData_t* _flightData){m_flightData = _flightData;};

        /** Get Flight Data
        * \return const FlightData_t* - Flight Data;
        */
        virtual const FlightData_t* GetFlightData()const {return m_flightData;}

        /** Set Flight Data
        * \param const FlightData_t* _flightData = new Data to the flight
        */
        virtual void SetFlightBasePrise(size_t _basePrise);

        /** Get Flight base prise
        * \return size_t - Flight base prise
        */
        virtual size_t GetFlightBasePrise()const {return m_basePrise;}

        /** Get Flight Details: Flight Data, capacity, number of booked passengers, and free seats by tier
        * \return string - Flight Details
        */
        virtual const string GetFlightDitals()const;

        /** Get Flight Details: Flight Data, capacity, number of booked passengers, and free seats by tier
        * \param FlightTier _tier = Tier ENUM name
        * \return vector<string> - free seats at the tier
        */
        virtual vector<string> GetFreeSeatsList(UserFlightInterface::FlightTier _tier)const;

        /** Get Seat status as Flight seat ENUM
        * \param FlightTier _tier = Tier ENUM name
        * \param const string& _seatnumber = seat number
        * \return FlightSeatStatus;
        */
        virtual UserFlightInterface::FlightSeatStatus GetSeatSatus(UserFlightInterface::FlightTier _tier,const string& _seatnumber)const;

        /** Set First Free seat
        * \param FlightTier _tier = Tier ENUM name
        * \return string - seat number
        *\warnign if no free seats exeprion will throw <int =-1>;
        */
        virtual const string SetSeat();

        /** Set First Free seat at given Tier
        * \param FlightTier _tier = Tier ENUM name
        * \return string - seat number
        *\warnign if no free seats exeprion will throw <int =-1>;
        */
        virtual const string SetSeat(UserFlightInterface::FlightTier _tier);

        /** Set First Free seat at given Tier
        * \param FlightTier _tier = Tier ENUM name
        * \param const string& _seatnumber = seat number
        * \return bool - if success true,  fail cause bad seat number or the seat are taken
        */
        virtual bool SetSeat(UserFlightInterface::FlightTier _tier, const string& _seatNumber);

        /** Realese taken seat
        * \param FlightTier _tier = Tier ENUM name
        * \param _seatNumber - seat number to Realese
        * \return bool if success , false if bud number given
        */
        virtual bool RealesSeat(UserFlightInterface::FlightTier _tier,const string& _seatNumber);


    private:
        Flight(const Flight& other);
        Flight& operator=(const Flight& other);
        Tier_t* GetTair(UserFlightInterface::FlightTier _tier)const;
    private:
        FlightData_t const* m_flightData;
        Iplane const* m_plane;
        map<string,Tier_t*> m_tiers;
        size_t m_basePrise;
        size_t m_capacity;
        size_t m_Passengers;
};

#endif // FLIGHT_H
