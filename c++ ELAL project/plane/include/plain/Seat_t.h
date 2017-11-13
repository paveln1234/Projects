#ifndef SEAT_T_H
#define SEAT_T_H
template<class T>
class Seat_t
{
public:
    /** Default constructor */
    explicit Seat_t(T _id):m_id(_id),m_status(true){};
        /** Default destructor */
    virtual ~Seat_t();
    inline bool SeatStatus()const {return m_status;}
    inline void TakeSeat(){m_status = true;}
    inline void RealeseSeat(){m_status = false};
private:
    T m_id;
    bool m_status;
};

#endif // SEAT_T_H
