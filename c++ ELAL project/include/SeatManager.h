#ifndef SEATMANAGER_H
#define SEATMANAGER_H

#include <vector>
class Seat_t;
using namespace std;
class SeatManager
{
    public:
        enum SeatManagerStatus{FREE_SEAT,TAKEN_SEAT,BADNUMBER,NOFREESEAT};
        /** Default constructor */
        SeatManager();
        /** Default destructor */
        virtual ~SeatManager();
          /** Creaty new seat Manager;
         */
        void Creaty();

          /** Get Capacity
         * \return The current capacity
         */
        size_t GetCapacity()const { return m_capacity; }

          /** Set Capacity create seat by gevein capasi
         * \param _capacity = New sea
         */
        void initialize(size_t _capacity);

          /** return Seat Status by given seat number
          * \param _seatNumber - seat number
         * \return SeatManagerStatus
         */
        SeatManagerStatus GetSeatStatus(size_t _seatNumber)const;

          /** Set seat by given number
          * \param _seatNumber - seat to set
         * \return bool if success , false if Seat "TAKEN" or bud number given
         */
        bool SetSeat(size_t _seatNumber);

          /** Set first "FREE" seat
         * \return bool if success , false if no "FREE" seats
         */
        bool SetSeat();

          /** Get Free Seat
         * \return first free seat
         *\warnign if no free seats exeprion will throw <int =-1>;
         */
        size_t GetFreeSeat()const;
        vector<size_t> GetAllFreeSeats()const;
        bool GetFreeSeat(vector<vector<Seat_t*>::iterator>& _it);

    private:
        SeatManager(const SeatManager& other);
        SeatManager& operator=(const SeatManager& other);
        Seat_t* FindSeat(size_t _number)const;
    private:
        vector<Seat_t*> m_seats;
        size_t m_capacity;
};

#endif // SEATMANAGER_H
