#ifndef TIER_T_H
#define TIER_T_H
#include <vector>
#include <string>
#include <map>
class Seat_t;
using namespace std;
class Tier_t
{
    public:
        enum SeatTeirStatus{FREE_SEAT,TAKEN_SEAT,BAD_NUMBER};
        /** Default constructor */
        Tier_t();
        /** Default destructor */
        virtual ~Tier_t();

        /** create new Tier
         */
        void Create();

        /** Tier Capacity
         * \return The current value of m_capacity
         */
        size_t GetCapacity()const  { return m_capacity; }

        /** Set new Tier capacity
         * \param size_t _capacity -  New capacity to set
         */
        void SetCapacity(size_t _capacity) { m_capacity = _capacity; }

        /**  Tier prise
         * \return The current value of m_prise
         */
        size_t GetPrise()const { return m_prise; }

        /** Set new Tier prise
         * \param size_t _prise -  New prise to set
         */
        void SetPrise(size_t _prise) { m_prise = _prise; }

        /** Set new Tier name
         * \param const string& _newName -  New name to set
         */
        void SetName(const string& _newName) {m_name = _newName;}

          /** return Tier name
         * \return tier name
         */
        const string& GetName()const {return m_name;}

          /** return Passenger amout
         * \return tier name
         */
        size_t GetPasengersAmout()const {return m_passangers;}

          /** inilialize the Teir
         * \param size_t _capacity - Tier capacity
         * \param size_t _prise - Tier prise
         */
        void initialize(const string& _name,size_t _capacity, size_t _prise);

          /** return Seat Status by given seat number
          * \param _seatNumber - seat number
         * \return SeatManagerStatus
         */
        SeatTeirStatus GetSeatStatus(const string& _seatNumber)const;

         /** Set seat by given number
          * \param _seatNumber - seat to set
         * \return bool if success , false if Seat "TAKEN" or bud number given
         */
        bool SetSeat(const string& _seatNumber);

          /** Set first "FREE" seat
         * \return Seat Number.
         *\warnign if no free seats exeprion will throw <int =-1>;
         */
        const string SetSeat();

        /** Realese taken seat
          * \param _seatNumber - seat number to Realese
         * \return bool if success , false if bud number given
         */
        bool RealesSeat(const string& _seatNumber);

        /** Get Free Seat
         * \return first free seat
         *\warnign if no free seats exeprion will throw <int =-1>;
         */
        const string& GetFreeSeat()const;

           /** the method return vector of all Free Seat
         * \return vector of all Free Seat if no free seats vector return emptey
         */
        vector<string> GetAllFreeSeats()const;

        /** return Number Of Taken seats
         * \return The current value Taken seats
         */
        size_t GetTakenSeats()const{return m_seats.size();}

    private:
        Tier_t(const Tier_t& other);
        Tier_t& operator=(const Tier_t& other);
        Seat_t* FindSeat(size_t _number)const;
        string GetSeatNumber(size_t _number);
        string ToString(size_t _number);


    private:
        string m_name;
        size_t m_capacity; //!< Member variable capacity;
        size_t m_passangers; //!< number of Passengers
        size_t m_prise; //!< Member variable tier pries
        map<string,Seat_t*> m_seats;//!< Member variable seats string - SeatNumber,Seat_t* - Seat;
};

#endif // TIER_T_H
