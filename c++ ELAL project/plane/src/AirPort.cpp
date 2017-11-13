#include<iostream>
#include "AirPort.h"

AirPort::AirPort()
{

}

AirPort::~AirPort()
{

}
void AirPort::Create()
{

}

void AirPort::PrintAirPort() const
{
    cout<<"AirPort Name = " << m_name << " City = " << m_city << " contry = " << m_contry << " Code = " <<m_code<<endl;
}

const string& AirPort::GetAirportData()const
{
    string* str = new string;
    *str += m_name;
    *str += " ";
    *str += m_city;
    *str += " ";
    *str += m_contry;
    *str += " ";
    *str += m_code;

return *str;
}
