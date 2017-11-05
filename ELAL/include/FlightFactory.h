#ifndef FLIGHTFACTORY_H
#define FLIGHTFACTORY_H
#include<string>
#include"FullFlightInterface.h"


using namespace std;

class FlightFactory
{
    public:
        FlightFactory(){}
        virtual ~FlightFactory(){}
        FullFlightInterface* GetFlight(const string& _flightName);



};

#endif // FLIGHTFACTORY_H
