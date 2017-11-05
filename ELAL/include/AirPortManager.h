#ifndef AIRPORTMANAGER_H
#define AIRPORTMANAGER_H
#include <vector>
class AirPort;
using namespace std;

class AirPortManager
{
    public:
        /** Default constructor */
        AirPortManager();
        /** Default destructor */
        virtual ~AirPortManager();
        const AirPort* GetAirPortByCode(string& _airPortCode)const;
        const AirPort* GetAirPortByName(string& _airPortName)const;
        void PrintAllAirPorts()const;

    protected:

    private:
    vector<AirPort*> m_AirPorts;
};

#endif // AIRPORTMANAGER_H
