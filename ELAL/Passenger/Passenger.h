#ifndef PASSENGER_H
#define PASSENGER_H


class Passenger
{
    public:
        /** Default constructor */
        Passenger();
        /** Default destructor */
        virtual ~Passenger();

    private:
        Passenger(const Passenger& other);
        Passenger& operator=(const Passenger& other);

    private:

};

#endif // PASSENGER_H
