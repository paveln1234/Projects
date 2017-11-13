#include <iostream>
#include<string>
#include "Customer_t.h"
#include "Passenger_t.h"
#include "UserCostumerInt.h"
#include "PassengerManager_t.h"
using namespace std;

int main()
{
    PassengerManager_t* Ps = new PassengerManager_t;
    //Ps->PrintAllPasengers();
    Customer_t const* tempCus = Ps->GetCustomer(0);
    cout<<tempCus->GetCostumerDetails() <<endl;
    UserCostumerInt const* tempUserCus = Ps->GetCustomer(450);
    cout<<tempUserCus->GetCostumerDetails() <<endl;
    string ticket = "45rr";
    string ticket1 = "452rr";
    Ps->AddTicketToPassenger(0,ticket);
    Ps->AddTicketToPassenger(0,ticket1);
    cout<<Ps->GetPassengerData(0) <<endl;
    Ps->RemoveTicketFromPassenger(0,ticket1);
    cout<<Ps->GetPassengerData(0) <<endl;
    Ps->BordedPassenger(0,true);
    string newName = "bob habani";
    const_cast<Customer_t*>(tempCus)->SetName(newName);

    cout<<Ps->GetPassengerData(0) <<endl;
    return 0;
}
