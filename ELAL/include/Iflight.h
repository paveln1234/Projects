#ifndef IFLIGHT_H
#define IFLIGHT_H
#include <string>
using namespace std;
class Iplane;
class FlightData_t;

class Iflight
{
    public:

        virtual ~Iflight() {}
        virtual void Create() = 0;
        virtual void SetPlain(const Iplane* _plane) = 0;
        virtual const Iplane* GetPlain()const =0;
        virtual void SetFlightData(const FlightData_t* _flightData) = 0;
        virtual const FlightData_t* GetFlightData()const = 0;
        virtual void SetFlightBasePrise(size_t _basePrise) = 0;
        virtual size_t GetFlightBasePrise()const =0;
        virtual const string GetFlightDitals()const = 0;



};

#endif // IFLIGHT_H
