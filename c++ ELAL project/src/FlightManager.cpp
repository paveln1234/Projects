#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <time.h>

#include "FlightManager.h"
#include "AirPortManager.h"
#include "FullFlightInterface.h"
#include "PlaneManager.h"
#include "Iplane.h"
#include "FlightFactory.h"
#include "FlightData_t.h"

size_t FlightManager::m_counter = 0;

FlightManager::FlightManager()
{
    string temp[6];
    string line;
    size_t i = 0;
    size_t pos=0,pos2=0;
    size_t prise = 0;
    size_t planerundnumber = 0;
    string flightType = "commercial";
    string planeType = "Plane";
    string planeId;
    string  flightId;
    ifstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);
    try
    {
        file.open("./db/flightdatadb");
    }catch(const std::ios_base::failure& e)
    {
        cout<<"error = " <<e.what();
    }
    srand(time(0));

    AirPortManager* airPortManager = new AirPortManager;
    FlightFactory* flightFactory = new FlightFactory;
    planeManager = new PlaneManager;
    while(file.peek()!= EOF)
    {
        ostringstream str;
        ostringstream str1;

        getline(file,line);
        if(file.eof()) break;
        while((pos = line.find("|",pos2)) != string::npos)
        {
           temp[i++] = line.substr(pos2,pos-pos2);
            pos2 = pos+1;
        }
        temp[i++] = line.substr(pos2,pos-pos2);

        AirPort const* dep = airPortManager->GetAirPortByCode(temp[0]);
        AirPort const* arrive = airPortManager->GetAirPortByCode(temp[1]);

        FlightData_t* fdata = new FlightData_t;
        fdata->SetDepartureAirPort(dep);
        fdata->SetDepartureDate(temp[2]);
        fdata->SetDepartureTime(temp[3]);
        fdata->SetArrivelAirPort(arrive);
        fdata->SetArrivelDate(temp[4]);
        fdata->SetArrivelTime(temp[5]);
        str<<m_counter;
        flightId = str.str();
        fdata->SetFlightId(flightId);
        FullFlightInterface* newFlight = flightFactory->GetFlight(flightType);
        prise = ((rand() % 29) + 1) * 100;
        newFlight->SetFlightBasePrise(prise);
        planerundnumber =((rand() % 29) + 1);
        str1 <<planerundnumber;
        planeId = str1.str();
        Iplane const* plane = planeManager->GetPlane(planeId);
        newFlight->SetPlain(plane);
        newFlight->SetFlightData(fdata);
        m_flights[m_counter] = newFlight;
        ++m_counter;
        line.clear();
        planeId.clear();
        pos2=pos = i=0;
    }
    file.close();
    m_FlightFacorty = flightFactory;

}

FlightManager::~FlightManager()
{
     for(map<size_t,FullFlightInterface*>::const_iterator it = m_flights.begin();it!=m_flights.end();it++)
    {
       delete it->second;
    }
    m_flights.clear();

    //delete flightFactory;
    //delete planeManager;
}

size_t FlightManager::AddFlight(const Iplane* _plain, FlightData_t* _flightData, size_t _prise)
{
    if(!_plain)
        throw(-1);

    string flightType = "commercial";
    string flightnumber;
    ostringstream str1;

    FullFlightInterface* newFlight = m_FlightFacorty->GetFlight(flightType);
    newFlight->Create();
    newFlight->SetPlain(_plain);
    newFlight->SetFlightData(_flightData);
    newFlight->SetFlightBasePrise(_prise);
    str1<<m_counter;
    flightnumber = str1.str();
    _flightData->SetFlightId(flightnumber);
    m_flights[m_counter] = newFlight;

    ++m_counter;
return (m_counter-1);
}

const bool FlightManager::RemoveFlight(size_t _flightNumber)
{

    map<size_t,FullFlightInterface*>::iterator it= m_flights.find(_flightNumber);
    if(it != m_flights.end())
    {
        delete it->second;
        m_flights.erase(it);
        return true;
    }

return false;
}

const bool FlightManager::UpdateFlight(size_t _flightNumber, FlightData_t* _flightData)
{
    if(_flightData)
    {
        map<size_t,FullFlightInterface*>::iterator it= m_flights.find(_flightNumber);
        if(it != m_flights.end())
        {
            FullFlightInterface* temp = it->second;
            temp->SetFlightData(_flightData);
            return true;
        }
    }

return false;
}

const bool FlightManager::UpdateFlight(size_t _flightNumber, size_t _prise)
{
    map<size_t,FullFlightInterface*>::iterator it= m_flights.find(_flightNumber);
    if(it != m_flights.end())
    {
        FullFlightInterface* temp = it->second;
        temp->SetFlightBasePrise(_prise);
        return true;
    }

return false;
}

const FullFlightInterface* FlightManager::GetFlight(size_t _flightNumber)
{
    return (m_flights.count(_flightNumber) == 1)? m_flights[_flightNumber]:NULL;
}

void FlightManager::PrintAllFlights() const
{
    string str;
    for(map<size_t,FullFlightInterface*>::const_iterator it= m_flights.begin(); it!= m_flights.end(); it++)
    {
        FullFlightInterface* temp = it->second;
        str = temp->GetFlightDitals();
        cout << str << endl;
    }
}
