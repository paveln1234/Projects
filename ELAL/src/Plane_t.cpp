#include <iostream>
#include "Plane_t.h"
#include "Iplane.h"
Plane_t::~Plane_t()
{
        m_PlaneArrangement.clear();
        m_capacity = 0;
}

void Plane_t::Create()
{
    m_capacity = 0;
}


void Plane_t::SetPlaneArrangement(vector<pair<string, size_t> >& _PlaneArrangement)
{
    // all data types are primitives;
    m_PlaneArrangement =_PlaneArrangement;
    size_t range = m_PlaneArrangement.size();
    for(size_t i = 0; i<range ;++i)
    {
        m_capacity+=m_PlaneArrangement[i].second;
    }

}

const vector<pair<string, size_t> >& Plane_t::GetPlaneArrangement() const
{
    return m_PlaneArrangement;
}

void Plane_t::PrintPlane() const
{
    cout<<"Plane Type = "<<m_type <<" ID = "<<m_id<<" Capacity = "<<m_capacity <<endl;
    for(size_t i =0 ; i<m_PlaneArrangement.size();++i)
    {
        cout<<" class name- "<<(m_PlaneArrangement[i]).first << "capacity - "<<m_PlaneArrangement[i].second <<endl;
    }
}
