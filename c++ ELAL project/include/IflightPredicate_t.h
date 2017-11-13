#ifndef IFLIGHTPREDICATE_T_H
#define IFLIGHTPREDICATE_T_H
#include <string>
#include "FullFlightInterface.h"

template<namespace T>
class IflightPredicate_t
{
    public:
        /** Check Function  */
        virtual bool Check(const Iflight* _flight);
        /** add Key to Predicate */
        virtual void SetKey(const std::string& _key);

    private:
    T m_predicate;

};


class DeparturePred : public IflightPredicate_t<AirPort*>
{
    public:
        /** Check Function  */
        virtual bool Check(const Iflight* _flight);
        /** add Key to Predicate */
        virtual void SetKey(const std::string& _key);
        /** static Functiontu reseve the predicate  */
        static IFlightPredicate_t* Create();


};


class DepartureDatePred : public IflightPredicate_t<string>
{
    public:
        /** Check Function  */
        virtual bool Check(const Iflight* _flight);
        /** add Key to Predicate */
        virtual void SetKey(const std::string& _key);
        /** static Functiontu reseve the predicate  */
        static IFlightPredicate_t* Create();

    private;
    string m_arrivaldate;

};

class DepartureTimePred : public IflightPredicate_t
{
    public:
        /** Check Function  */
        virtual bool Check(const Iflight* _flight);
        /** add Key to Predicate */
        virtual void SetKey(const std::string& _key);
        /** static Functiontu reseve the predicate  */
        static IFlightPredicate_t* Create();

    private;
    string m_arrivalTime;

};

class ArrivalDatePred : public IflightPredicate_t
{
    public:
        /** Check Function  */
        virtual bool Check(const Flight_t* _flight);
        /** add Key to Predicate */
        virtual void SetKey(const std::string& _key);
        /** static Functiontu reseve the predicate  */
        static IFlightPredicate_t* Create();

    private;
    string m_arrivaldate;

};

class ArrivalTimePred : public IflightPredicate_t
{
    public:
        /** Check Function  */
        virtual bool Check(const Flight_t* _flight);
        /** add Key to Predicate */
        virtual void SetKey(const std::string& _key);
        /** static Functiontu reseve the predicate  */
        static IFlightPredicate_t* Create();

    private;
    string m_arrivalTime;

};




#endif // IFLIGHTPREDICATE_T_H
