#ifndef FLIGHTDATAMANAGER_H
#define FLIGHTDATAMANAGER_H


class FlightDataManager
{
    public:
        FlightDataManager();
        virtual ~FlightDataManager();


    private:
        FlightDataManager(const FlightDataManager& other);
        FlightDataManager& operator=(const FlightDataManager& other);
    private:
};

#endif // FLIGHTDATAMANAGER_H
