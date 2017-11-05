#ifndef USERDATAFLIGHTDATAINT_H
#define USERDATAFLIGHTDATAINT_H


class UserDataFlightDataInt
{
    public:
        virtual ~UserDataFlightDataInt() {}
        virtual const string& GetFlightId()const =0;
        virtual const string& GetFlightDetails()const = 0;
        virtual const string& GetDepartureTime()const =0;
        virtual const string& GetArrivelTime()const =0;
        virtual const string& GetDepartureDate()const =0;
        virtual const string& GetArrivelDate()const =0;
        virtual const string& GetDepartureAirPortCode()const = 0;
        virtual const string& GetArrivelAirPortCode()const = 0;
};

#endif // USERDATAFLIGHTDATAINT_H
