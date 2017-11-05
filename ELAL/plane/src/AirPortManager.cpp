#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cerrno>
#include <cstring>

#include "AirPortManager.h"
#include "AirPort.h"

AirPortManager::AirPortManager()
{
    string line;
    string temp[4];
    size_t i = 0;
    size_t pos=0,pos2=0;

    ifstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);
    try
    {
        file.open("./db/airportsdb");
    }catch(const std::ios_base::failure& e)
    {
        cout<<"error = " <<e.what();
    }
    while(file.peek()!= EOF)
    {
        getline(file,line);
        if(file.eof()) break;
        while((pos = line.find("|",pos2)) != string::npos)
        {
           temp[i++] = line.substr(pos2,pos-pos2);
            pos2 = pos+1;
        }
        temp[i++] = line.substr(pos2,pos-pos2);
        AirPort* tempPort =new AirPort;

        tempPort->Create();
        tempPort->SetName(temp[0]);
        tempPort->SetCity(temp[1]);
        tempPort->SetContry(temp[2]);
        tempPort->SetCode(temp[3]);

        m_AirPorts.push_back(tempPort);
        line.clear();
        pos2=pos = i=0;
    }
    file.close();
}

AirPortManager::~AirPortManager()
{
    size_t i=0;
    size_t capaity = m_AirPorts.size();
    for(;i<capaity;++i)
    {
        AirPort* temp;
        temp = m_AirPorts[i];
        delete temp;
    }
    m_AirPorts.erase(m_AirPorts.begin(),m_AirPorts.end());
}

const AirPort* AirPortManager::GetAirPortByCode(string& _airPortCode) const
{
     for(vector<AirPort*>::const_iterator it=m_AirPorts.begin();it!=m_AirPorts.end();it++)
    {
           if( (*it)->GetCode()== _airPortCode)
                return *it;
    }

return NULL;
}

const AirPort* AirPortManager::GetAirPortByName(string& _airPortName) const
{
     for(vector<AirPort*>::const_iterator it=m_AirPorts.begin();it!=m_AirPorts.end();it++)
    {
           if( (*it)->GetName()== _airPortName)
                return *it;
    }
return NULL;
}


void AirPortManager::PrintAllAirPorts() const
{
     for(vector<AirPort*>::const_iterator it=m_AirPorts.begin();it!=m_AirPorts.end();it++)
    {
            (*it)->PrintAirPort();
    }
}

