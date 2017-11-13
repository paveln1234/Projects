#include "Comunicator.h"
#include "Message_t.h"

Comunicator::Comunicator()
{

}

Comunicator::~Comunicator()
{
    //dtor
}
bool Comunicator::Connect(bool _isClient)
{
    m_isClient = _isClient;
return true;
}

bool Comunicator::Send(Message_t* msg)
{
    if(m_isClient)
    {
        m_in.push(msg);
    }
    else
    {
        m_out.push(msg);
    }
return true;
}

Message_t* Comunicator::Resive()
{
    Message_t* newMsg;
    if(m_isClient)
    {
        newMsg = m_out.front();
     //   temp = *newMsg;
        //m_out.pop();
    }
    else
    {
        newMsg = m_in.front();
       // temp = *newMsg;

        //m_in.pop();
    }
return newMsg;
}
