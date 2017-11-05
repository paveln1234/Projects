#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cerrno>
#include <cstring>

#include "PassengerManager_t.h"
#include "Customer_t.h"
using namespace std;
size_t PassengerManager_t::m_counter = 0;
PassengerManager_t::PassengerManager_t()
{
    string line;
    string customerId;
    string temp[4];
    size_t i = 0;
    size_t pos=0,pos2=0;

    ifstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);
    try
    {
        file.open("./db/custemmerdb");
    }catch(const std::ios_base::failure& e)
    {
        cout<<"error = " <<e.what();
    }
    while(file.peek()!= EOF)
    {
        ostringstream str;

        getline(file,line);
        if(file.eof()) break;
        while((pos = line.find("|",pos2)) != string::npos)
        {
           temp[i++] = line.substr(pos2,pos-pos2);
            pos2 = pos+1;
        }
        temp[i++] = line.substr(pos2,pos-pos2);

        Customer_t* tempCusttomer =new Customer_t;

        tempCusttomer->SetName(temp[0]);
        tempCusttomer->SetAdress(temp[1]);
        tempCusttomer->SetPhone(temp[2]);
        tempCusttomer->SetEmail(temp[3]);

        Passenger_t* newPassenger = new Passenger_t;
        newPassenger->SetCustomer(tempCusttomer);
        newPassenger->SetPassengerId(m_counter);
        m_passengers[m_counter] = newPassenger;

        line.clear();
        pos2=pos = i=0;
        ++m_counter;
    }
    file.close();
}


PassengerManager_t::~PassengerManager_t()
{
  for(map<size_t,Passenger_t*>::const_iterator it = m_passengers.begin();it!=m_passengers.end();it++)
    {
       delete it->second;
    }
    m_passengers.clear();
}

const bool PassengerManager_t::AddPassenger(const Customer_t* _costumer)
{
    if(!_costumer)
    {
        return false;
    }
    Passenger_t* newPassenger = new Passenger_t;
    newPassenger->SetCustomer(_costumer);
    newPassenger->SetPassengerId(m_counter);
    m_passengers[m_counter] = newPassenger;
    ++m_counter;

return true;
}

const bool PassengerManager_t::RemovePassenger(size_t _passengerId)
{
    map<size_t,Passenger_t*>::iterator it= m_passengers.find(_passengerId);
    if(it != m_passengers.end())
    {
        delete it->second;
        m_passengers.erase(it);
        return true;
    }

return false;
}

const bool PassengerManager_t::UpdatePassenger(const Customer_t* _costumer, size_t _passengerId)
{
    Customer_t* temp = const_cast<Customer_t*>(_costumer);
    map<size_t,Passenger_t*>::iterator it= m_passengers.find(_passengerId);
    if(it != m_passengers.end())
    {
        it->second->SetCustomer(temp);
        return true;
    }

return false;

}

const bool PassengerManager_t::AddTicketToPassenger(size_t _passengerId, const string& _ticketId)
{
    map<size_t,Passenger_t*>::iterator it= m_passengers.find(_passengerId);
    if(it != m_passengers.end())
    {
        it->second->AddTicket(_ticketId);
        return true;
    }
return false;
}

const bool PassengerManager_t::RemoveTicketFromPassenger(size_t _passengerId,const string& _ticketId)
{
    map<size_t,Passenger_t*>::iterator it= m_passengers.find(_passengerId);
    if(it != m_passengers.end())
    {
        it->second->RemoveTicket(_ticketId);
        return true;
    }

return false;
}

const bool PassengerManager_t::BordedPassenger(size_t _passengerId, bool _status)
{
    map<size_t,Passenger_t*>::iterator it= m_passengers.find(_passengerId);
    if(it != m_passengers.end())
    {
         it->second->SetBorded(_status);
         return true;
    }

return false;
}

const bool PassengerManager_t::IsBorded(size_t _passengerId, bool _status) const
{
    map<size_t,Passenger_t*>::const_iterator it= m_passengers.find(_passengerId);
    if(it != m_passengers.end())
    {
         return it->second->IsBorded();
    }

return false;
}


const Customer_t* PassengerManager_t::GetCustomer(size_t _passengerId) const
{
    map<size_t,Passenger_t*>::const_iterator it= m_passengers.find(_passengerId);
    if(it != m_passengers.end())
    {
        return it->second->GetCustomer();
    }

return NULL;
}
const vector<string> PassengerManager_t::GetPasengerTiket(size_t _passengerId) const
{
    map<size_t,Passenger_t*>::const_iterator it= m_passengers.find(_passengerId);
    if(it != m_passengers.end())
    {
        return it->second->GetTicketList();
    }

throw(-1);
}

const string PassengerManager_t::GetPassengerData(size_t _passengerId) const
{
    map<size_t,Passenger_t*>::const_iterator it= m_passengers.find(_passengerId);
    if(it != m_passengers.end())
    {
        return it->second->GetPassengerDitals();
    }

throw(-1);
}

void PassengerManager_t::PrintAllPasengers() const
{
    for(map<size_t,Passenger_t*>::const_iterator it= m_passengers.begin(); it!= m_passengers.end(); it++)
    {
        cout << it->second->GetPassengerDitals() << endl;
    }
}
