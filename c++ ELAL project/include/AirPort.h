#ifndef AIRPORT_H
#define AIRPORT_H
#include <string>
using namespace std;

class AirPort
{
    public:
        /** Default constructor */
        AirPort();
        /** Default destructor */
        virtual ~AirPort();
        /** Create AirPort */
        void Create();

        /** Set AirPort name
        * \param const string& _name - AirPort name
        */
        void SetName(const string& _name) {m_name = _name;}
       \
        /** Get AirPort name
        * \return const string - AirPort name
        */
        const string& GetName()const {return m_name;}

        /** Set AirPort city
        * \param const string& _city - AirPort city
        */
        void SetCity(const string& _city) {m_city = _city;}

        /** Get AirPort city
        * \return const string& - AirPort city
        */
        const string& GetCity()const {return m_city;}

        /** Set AirPort contry
        * \param const string& _contry - AirPort contry
        */
        void SetContry(const string& _contry) {m_contry = _contry;}

        /** Get AirPort contry
        * \return const string& - AirPort conty
        */
        const string& GetContry()const {return m_contry;}

        /** Set AirPort code
        * \param const string& _code - AirPort code
        */
        void SetCode(const string& _code) {m_code = _code;}
        /** Get AirPort code
        * \return const string - AirPort code
        */
        const string& GetCode()const {return m_code;}

        /** Print  AirPort data
        * \brief - the function print on std out the air port data
        */
        void PrintAirPort()const;

        /** Get AirPort data
        * \brief - the function return air port data as const string&
        * \return - const string& whit the data
        */
        const string GetAirportData()const;

    private:
        AirPort& operator = (const AirPort& _other);
        AirPort(const AirPort& _other);
    private:
     string m_name;
     string m_city;
     string m_contry;
     string m_code;
};

#endif // AIRPORT_H
