#include "FlightData_t.h"
#include "AirPort.h"

FlightData_t::FlightData_t()
{
    m_departure = 0;
    m_arrivel = 0;
}

FlightData_t::~FlightData_t()
{
    //dtor
}
void FlightData_t::Create()
{

}

const string& FlightData_t::GetFlightDetails() const
{
    string * str = new string;
    string temp;
    *str += "Flight Id: ";
    *str += m_flightId;
    *str += " From : ";
    temp = m_departure->GetCode();
    *str += temp;
    *str += " At : ";
    *str += m_departedDate;
    *str += ", ";
    *str += m_departedTime;
    *str += " To : ";
    *str += m_arrivel->GetCode();
    *str += " At : ";
    *str += m_arrivelDate;
    *str += ", ";
    *str += m_arrivelTime;
return *str;
}

