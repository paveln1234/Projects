#include <iostream>
#include "SeatManager.h"
#include "Seat_t.h"
int main()
{
    SeatManager m;
    m.Creaty();
    m.initialize(50);
    int i=0;
    for(; i<50; i+=3)
    {
        m.SetSeat(i);
    }
    i = 0;
    vector<size_t> temp = m.GetAllFreeSeats();
    for(vector<size_t>::iterator it = temp.begin();it!= temp.end();it++)
    {
        cout<<*it<<"\n";
    }

    vector<vector<Seat_t*>::iterator> it;
    if(m.GetFreeSeat(it))
    for(vector<vector<Seat_t*>::iterator>::iterator g= it.begin();g!= it.end();g++)
    {
        cout<<(**g)->GetNumber()<<"\n";

    }


}

