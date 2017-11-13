#ifndef COMUNICATOR_H
#define COMUNICATOR_H
#include <queue>
using namespace std;
class Message_t;

class Comunicator
{
    public:
        Comunicator();
        virtual ~Comunicator();

        /**Establish connection
        * \param bool _isClient - Set comunicator side
        * \return bool - true in success to make connection , false if connection failed's
        */
        bool Connect(bool _isClient);

        /**Send message
        * \param Message_t* msg - message to send
        * \return bool - true if message sent , false if message failed to sent
        */
        bool Send(Message_t* msg);

        /**Resive message
        * \return Message_t* - if success or NULL pointer if failed
        */
        Message_t* Resive();

    private:
    queue<Message_t*> m_in;
    queue<Message_t*> m_out;
    bool m_isClient;
};

#endif // COMUNICATOR_H
