#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cerrno>
#include <cstring>

#include "PlaneManager.h"
#include "PlaneFactory.h"
#include "Iplane.h"

using namespace std;

PlaneManager::PlaneManager()
{
    PlaneFactory p ;
    string line;
    string temp[6];
    size_t i = 0;
    size_t pos=0,pos2=0;

    ifstream file("./db/airplanedb");
    while(file.peek()!= EOF)
    {
        getline(file,line);
        if(file.eof()) break;
        vector<pair<string,size_t> > PlaneArrangement;
        while((pos = line.find("|",pos2)) != string::npos)
        {
           temp[i++] = line.substr(pos2,pos-pos2);
            pos2 = pos+1;
        }
           temp[i++] = line.substr(pos2,pos-pos2);

        PlaneArrangement.push_back(make_pair(temp[2],atoi(temp[3].c_str())));
        PlaneArrangement.push_back(make_pair(temp[4], atoi(temp[5].c_str())));

        Iplane* tempPlane =p.GetPlane("Plane");

        tempPlane->Create();
        tempPlane->SetType(temp[0]);
        tempPlane->SetId(temp[1]);
        tempPlane->SetPlaneArrangement(PlaneArrangement);
        m_planes.push_back(tempPlane);
        line.clear();
        pos2=pos = i=0;
    }
    file.close();
}

PlaneManager::~PlaneManager()
{
    size_t i=0;
    size_t capaity = m_planes.size();
    for(;i<capaity;++i)
    {
        Iplane* temp;
        temp = m_planes[i];
        delete temp;
    }
    m_planes.erase(m_planes.begin(),m_planes.end());
}

const Iplane* PlaneManager::GetPlane(string& _planeId) const
{
    for(vector<Iplane*>::const_iterator it=m_planes.begin();it!=m_planes.end();it++)
    {
           if( (*it)->GetId()== _planeId)
                return *it;
    }
return NULL;
}


void PlaneManager::PrintAllPlance() const
{
        for(vector<Iplane*>::const_iterator it=m_planes.begin();it!=m_planes.end();it++)
        {
            (*it)->PrintPlane();
        }
}
