#ifndef FULLFLIGHTINTERFACE_H
#define FULLFLIGHTINTERFACE_H

#include "Iflight.h"

#include "UserFlightInterface.h"

class FullFlightInterface : public Iflight, public UserFlightInterface
{
    public:

        virtual ~FullFlightInterface() {}
        virtual void Create() = 0;
        virtual void SetPlain(const Iplane* _plane) = 0;
        virtual const Iplane* GetPlain()const =0;
        virtual void SetFlightData(const FlightData_t* _flightData) = 0;
        virtual const FlightData_t* GetFlightData()const = 0;
        virtual void SetFlightBasePrise(size_t _basePrise) = 0;
        virtual size_t GetFlightBasePrise()const =0;
        virtual bool RealesSeat(FlightTier _tier,const string& _seatNumber)=0;
        virtual bool SetSeat(FlightTier _tier, const string& _seatNumber) = 0;
        virtual const string SetSeat(FlightTier _tier) = 0;
        virtual const string SetSeat() = 0;
        virtual FlightSeatStatus GetSeatSatus(FlightTier _tier,const string& _seatnumber)const = 0;
        virtual vector<string> GetFreeSeatsList(FlightTier _tier)const = 0;
        virtual const string GetFlightDitals()const = 0;

    protected:

    private:
};

#endif // FULLFLIGHTINTERFACE_H
