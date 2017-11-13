#include <iostream>
#include <vector>
#include "Iplane.h"
#include "PlaneManager.h"
#include "PlaneFactory.h"
#include "AirPortManager.h"
#include "AirPort.h"
#include "FlightData_t.h"
//#include "Iflight.h"
#include "UserFlightInterface.h"
#include "FlightFactory.h"
#include "FlightManager.h"
using namespace std;

int main()
{
    FlightManager FM;
    FM.PrintAllFlights();

    AirPortManager p;

    string str = "TLV";
    string str2 = "GFK";
    AirPort const* temp = p.GetAirPortByCode(str);
    AirPort const* temp2 = p.GetAirPortByCode(str2);

    FlightData_t* tmpData = new FlightData_t;
    string dtime = "15.23";
    string ddate = "28.06.17";
    string atime = "04.40";
    string adate = "29.06.17";
    string fid = "TLV001";

    tmpData->Create();
    tmpData->SetDepartureAirPort(temp);
    tmpData->SetArrivelAirPort(temp2);
    tmpData->SetDepartureTime(dtime);
    tmpData->SetDepartureDate(ddate);
    tmpData->SetArrivelTime(atime);
    tmpData->SetArrivelDate(adate);


    PlaneManager pmanger;
    string pid = "8";
    Iplane const* plane = pmanger.GetPlane(pid);
    size_t num = FM.AddFlight(plane,tmpData,555);
    UserFlightInterface * uiflight =  FM.GetFlight(num);
    cout << num<<endl;
    FM.PrintAllFlights();
    ddate = "08.09.17";
    string newSeat;

    newSeat = uiflight->SetSeat();
    cout<<newSeat;

    tmpData->SetDepartureDate(ddate);

    FM.UpdateFlight(num,tmpData);
    FM.UpdateFlight(num,800);
    string sseat = "b1";
    uiflight->SetSeat(UserFlightInterface::BISNESS,sseat);
    cout << uiflight->GetFlightDitals();

    //string r = "commercial";
    //FullFlightInterface* pp = ff.GetFlight(r);
/*
    pp->Create();
    pp->SetPlain(plane);
    pp->SetFlightBasePrise(1000);
    pp->SetFlightData(tmpData);
    string flighdetails = pp->GetFlightDitals();
    cout <<flighdetails<<endl;
    vector<string> fseats = pp->GetFreeSeatsList(UserFlightInterface::ECONNOME);
    for(vector<string>::const_iterator it = fseats.begin(); it != fseats.end();it++)
    {
        cout<<*it<<endl;
    }
    string seat = "e9";
    (UserFlightInterface::FREE_SEAT == pp->GetSeatSatus(UserFlightInterface::ECONNOME,seat))?cout<<"good"<<endl:cout<<"bad"<<endl;
    string seat1 = "e500";
    (UserFlightInterface::FREE_SEAT == pp->GetSeatSatus(UserFlightInterface::ECONNOME,seat1))?cout<<"good"<<endl:cout<<"bad"<<endl;

     seat = "e9";
    (pp->SetSeat(UserFlightInterface::ECONNOME,seat))?cout<<"seat serve"<<endl:cout<<"bad number"<<endl;
    (UserFlightInterface::FREE_SEAT == pp->GetSeatSatus(UserFlightInterface::ECONNOME,seat))?cout<<"seat free"<<endl:cout<<"seat taken"<<endl;
    for(int i =0 ; i< 800; ++i)
    {
        try{
         pp->SetSeat(UserFlightInterface::ECONNOME);
        }catch(int temp)
        {
            cout<<"bad number"<<endl;
        }

    }
     for(int i =0 ; i<10; ++i)
    {
        try{
        seat = pp->SetSeat();
        cout<< "seat number taken = " << seat << endl;
        }catch(int temp)
        {
            cout<<"bad number"<<endl;
        }

    }
    (pp->RealesSeat(UserFlightInterface::BISNESS,seat))?cout<<"seat realese"<<endl:cout<<"bad number"<<endl;
    seat = "b50";
    (pp->RealesSeat(UserFlightInterface::BISNESS,seat))?cout<<"seat realese"<<endl:cout<<"bad number"<<endl;

    UserFlightInterface* dd = ff.GetFlight(r);*/

return 0;
}
