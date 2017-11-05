#ifndef USERFLIGHTINTERFACE_H
#define USERFLIGHTINTERFACE_H
#include<vector>


class UserFlightInterface
{
    public:
        enum FlightTier{ECONNOME,BISNESS};
        enum FlightSeatStatus{FREE_SEAT,TAKEN_SEAT,BAD_SEAT_NUMBER};
        virtual ~UserFlightInterface() {}
        virtual bool RealesSeat(FlightTier _tier,const string& _seatNumber)=0;
        virtual bool SetSeat(FlightTier _tier, const string& _seatNumber) = 0;
        virtual const string SetSeat(FlightTier _tier) = 0;
        virtual const string SetSeat() = 0;
        virtual FlightSeatStatus GetSeatSatus(FlightTier _tier,const string& _seatnumber)const = 0;
        virtual vector<string> GetFreeSeatsList(FlightTier _tier)const = 0;
        virtual const string GetFlightDitals()const = 0;






};

#endif // USERFLIGHTINTERFACE_H
