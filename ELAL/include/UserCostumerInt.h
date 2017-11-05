#ifndef USERCOSTUMERINT_H
#define USERCOSTUMERINT_H
#include <string>
using namespace std;
class UserCostumerInt
{
    public:
        virtual ~UserCostumerInt(){};
        virtual const string& GetName()const =0;
        virtual const string& GetAdress()const=0;
        virtual const string& GetPhone()=0;
        virtual const string& GetEmail()const = 0;
        virtual const string GetCostumerDetails()const = 0;
};

#endif // USERCOSTUMERINT_H
