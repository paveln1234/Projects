#ifndef REQUSTHANDLER_H
#define REQUSTHANDLER_H

class ResrveationSystem;
class Comunicator;
class Message_t;

using namespace std;
class RequstHandler
{
    public:
        RequstHandler();
        virtual ~RequstHandler();

        void create(Comunicator* _comunicator,ResrveationSystem* _resrvationSystem);
        void run();
        void Stop();

    private:
        bool AddPassenger(Message_t* _msg);
        bool AddFlight(Message_t* _msg);
        bool RemoveFlight(Message_t* _msg);
        bool RemovePassenger(Message_t* _msg);
        bool ReserveTicket(Message_t* _msg);
        bool FreeFlightTicket(Message_t* _msg);


    private:
        Comunicator* m_comunicator;
        ResrveationSystem* m_resrveationSystem;

};

#endif // REQUSTHANDLER_H
