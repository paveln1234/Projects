#include <sstream>
#include <string>
#include "Flight.h"
#include "Tier_t.h"
#include "FlightData_t.h"
Flight::Flight()
{

}

Flight::~Flight()
{

    for(map<string, Tier_t*>::iterator it = m_tiers.begin(); it != m_tiers.end(); it++ )
    {
       delete it->second;
    }
    m_tiers.clear();

}
void Flight::Create()
{
    m_plane = 0;
    m_flightData = 0;
    m_basePrise = 0;
    m_capacity =0;
    m_Passengers = 0;

}
void Flight::SetPlain(const Iplane* _plane)
{
    m_plane = _plane;
    size_t i = 0;
    vector<pair <string,size_t> >  temp = m_plane->GetPlaneArrangement();
    size_t planeTeir = temp.size();
    for(;i<planeTeir;++i)
    {
        Tier_t* tempTier = new Tier_t;
        tempTier->initialize(temp[i].first,temp[i].second,0);
        m_capacity+=temp[i].second;
        m_tiers[temp[i].first] = tempTier;
    }

}

void Flight::SetFlightBasePrise(size_t _basePrise)
{
    m_basePrise = _basePrise;
    for(map<string, Tier_t*>::iterator it = m_tiers.begin(); it != m_tiers.end(); it++ )
    {
        Tier_t* temp = it->second;
        ("economy" ==  it->first)?temp->SetPrise(m_basePrise):temp->SetPrise(m_basePrise*2);
    }

}

const string Flight::GetFlightDitals() const
{
    string FlightDitals = "Flight information : \n";
    FlightDitals += m_flightData->GetFlightDetails();
    FlightDitals += "\n";
    FlightDitals += "Flight capacity = ";
    stringstream ss;
    ss<< m_capacity;
    string temp;
    temp = ss.str();
    FlightDitals += temp;
    FlightDitals += " Flight booked Passengers = ";
    stringstream ss1;
    ss1<< m_Passengers;
    temp = ss1.str();
    FlightDitals += temp;
    FlightDitals += " Flight free seats = ";
    size_t num = m_capacity - m_Passengers;
    stringstream ss2;
    ss2<< num;
    temp = ss2.str();
    FlightDitals += temp;
    FlightDitals += "\n";
    FlightDitals += "Free seats at the flight: \n";
    for(map<string, Tier_t*>::const_iterator it = m_tiers.begin(); it != m_tiers.end(); it++ )
    {
        FlightDitals += "Free seats at Tier : ";
        FlightDitals +=  it->first;
        FlightDitals += "\n";
        Tier_t* tempTier = it->second;
        vector<string> freeseats = tempTier->GetAllFreeSeats();
        for(vector<string>::const_iterator it = freeseats.begin(); it != freeseats.end();it++)
        {
            FlightDitals += " , ";
            FlightDitals += *it;
        }
        FlightDitals += "\n";
    }

return FlightDitals;
}
vector<string> Flight::GetFreeSeatsList(UserFlightInterface::FlightTier _tier) const
{
    Tier_t* tempTier = GetTair(_tier);

return tempTier->GetAllFreeSeats();
}

UserFlightInterface::FlightSeatStatus Flight::GetSeatSatus(UserFlightInterface::FlightTier _tier, const string& _seatnumber) const
{
    Tier_t* tempTier = GetTair(_tier);
    Tier_t::SeatTeirStatus status = tempTier->GetSeatStatus(_seatnumber);
    switch (status)
    {
        case Tier_t::FREE_SEAT:
            return UserFlightInterface::FREE_SEAT;
        case Tier_t::TAKEN_SEAT:
            return UserFlightInterface::TAKEN_SEAT;
        case Tier_t::BAD_NUMBER:
            return UserFlightInterface::BAD_SEAT_NUMBER;
    }

return UserFlightInterface::BAD_SEAT_NUMBER;
}
const string Flight::SetSeat()
{
    for(map<string, Tier_t*>::const_iterator it = m_tiers.begin(); it != m_tiers.end(); it++ )
    {
        Tier_t* tempTier = it->second;
        try
        {
            string seat = tempTier->GetFreeSeat();
            tempTier->SetSeat(seat);
            ++m_Passengers;
            return seat;
        }catch(int execption)
        {
            continue;
        }
    }
throw(-1);
}

const string Flight::SetSeat(UserFlightInterface::FlightTier _tier)
{
    Tier_t* tempTier = GetTair(_tier);

    try
    {
        string seat = tempTier->GetFreeSeat();
        tempTier->SetSeat(seat);
        ++m_Passengers;
        return seat;
    }catch(int execption)
    {
        throw(-1);
    }
}

bool Flight::SetSeat(UserFlightInterface::FlightTier _tier, const string& _seatNumber)
{
    if(UserFlightInterface::FREE_SEAT == GetSeatSatus(_tier,_seatNumber))
    {
        Tier_t* tempTier = GetTair(_tier);
        tempTier->SetSeat(_seatNumber);
        ++m_Passengers;
        return true;
    }

return false;
}

bool Flight::RealesSeat(UserFlightInterface::FlightTier _tier,const string& _seatNumber)
{
    Tier_t* tempTier = GetTair(_tier);
    return tempTier->RealesSeat(_seatNumber);
}

Tier_t* Flight::GetTair(UserFlightInterface::FlightTier _tier)const
{
    Tier_t* tempTier =0;
    if(UserFlightInterface::ECONNOME == _tier)
    {
        tempTier = m_tiers.at("economy");
    }
    else
    {
        tempTier = m_tiers.at("business");
    }

return tempTier;
}

