#include "Customer_t.h"

Customer_t::Customer_t()
{
    //ctor
}

Customer_t::~Customer_t()
{
    //dtor
}


const string Customer_t::GetCostumerDetails() const
{
    string temp;

    temp = "name - ";
    temp += m_name;
    temp += " , Adress - ";
    temp += m_adress;
    temp += " , Phone - ";
    temp += m_phone;
    temp += " , E-mail - ";
    temp += m_email;

return temp;
}
