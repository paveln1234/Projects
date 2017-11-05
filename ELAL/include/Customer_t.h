#ifndef CUSTOMER_T_H
#define CUSTOMER_T_H

#include <string>
#include "UserCostumerInt.h"

using namespace std;
class Customer_t : public UserCostumerInt
{
    public:
        Customer_t();
        virtual ~Customer_t();

        /** Set Costumer Name
        * \param const string& _name - name to set
        */
        void SetName(const string& _name) {m_name = _name;}

        /** Get Costumer Name
        * \return const string& Costumer name
        */
        const string& GetName()const {return m_name;}

        /** Set Costumer adress
        * \param const string& _adress - adress to set
        */
        void SetAdress(const string& _adress) {m_adress = _adress;}

        /** Get Costumer adress
        * \return const string& Costumer adress
        */
        const string& GetAdress()const {return m_adress;}

        /** Set Costumer phone
        * \param const string& _phone - phone to set
        */
        void SetPhone(const string& _phoneNumber) {m_phone = _phoneNumber;}

        /** Get Costumer phone
        * \return const string& - Costumer phone
        */
        const string& GetPhone(){return m_phone;}

        /** Set Costumer Email
        * \param const string& _email - Email to set
        */
        void SetEmail(const string& _email){m_email =_email;}

        /** Get Costumer Email
        * \return const string& - Costumer Email
        */
        const string& GetEmail()const {return m_email;}

        /** Get Costumer Details
        * \return const string - Costumer details in onw line
        */
        const string GetCostumerDetails()const;

    private:
        Customer_t(const Customer_t& other);
        Customer_t& operator=(const Customer_t& other);

    private:
        string m_name;
        string m_adress;
        string m_phone;
        string m_email;


};

#endif // CUSTOMER_T_H
