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
        void Create();
        void SetName(const string& _name) {m_name = _name;}
        const string& GetName()const {return m_name;}
        void SetCity(const string& _city) {m_city = _city;}
        const string& GetCity()const {return m_city;}
        void SetContry(const string& _contry) {m_contry = _contry;}
        const string& GetContry()const {return m_contry;}
        void SetCode(const string& _code) {m_code = _code;}
        const string& GetCode()const {return m_code;}
        void PrintAirPort()const;
        const string& GetAirportData()const;
        AirPort& operator = (const AirPort& _other);
        AirPort(const AirPort& _other);
    private:
    private:
     string m_name;
     string m_city;
     string m_contry;
     string m_code;
};

#endif // AIRPORT_H
