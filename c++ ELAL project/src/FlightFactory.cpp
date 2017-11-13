#include "FlightFactory.h"
//#include "Iflight.h"
#include "FullFlightInterface.h"
//#include "UserFlightInterface.h"
#include "Flight.h"

FullFlightInterface* FlightFactory::GetFlight(const string& _flightName)
{
    FullFlightInterface* ptrFlight = 0;
    if("commercial" == _flightName)
        ptrFlight = new Flight;

return ptrFlight;
}


