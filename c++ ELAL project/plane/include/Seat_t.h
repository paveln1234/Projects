#ifndef SEAT_T_H
#define SEAT_T_H
#include <stdlib.h>

class Seat_t
{
    public:
        enum SeatStatus{FREE,TAKEN};
        /** Default constructor */
        Seat_t();
        /** Default destructor */
        virtual ~Seat_t();

        /** Return Seat number
         * \return The current seat number
         */
        size_t GetNumber() { return m_number; }

        /** Set Seat number
         * \param _newSeatNumber =  New seat number;
         */
        void SetNumber(size_t _newSeatNumber) { m_number = _newSeatNumber; }

        /** return the seat status
         * \return The current seat status
         */
        SeatStatus GetStatus()const  { return m_status; }

        /** Set seat status
         * \param _status = New seat status
         */
        void SetStatus(SeatStatus _status) { m_status = _status; }
        void Print()const;
    private:
        Seat_t(const Seat_t& other);
        Seat_t& operator=(const Seat_t& other);

    private:
        size_t m_number; //!< Member variable "m_number" - seat number
        SeatStatus m_status; //!< Member variable "m_status" - seat status false = free true = taken
};

#endif // SEAT_T_H
