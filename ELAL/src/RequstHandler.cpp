#include <iostream>
#include "RequstHandler.h"
#include "Comunicator.h"
#include "ResrveationSystem.h"
#include "Message_t.h"

RequstHandler::RequstHandler()
{
    //ctor
}

RequstHandler::~RequstHandler()
{
    //dtor
}

void RequstHandler::create(Comunicator* _comunicator, ResrveationSystem* _resrvationSystem)
{
    m_comunicator = _comunicator;
    m_resrveationSystem = _resrvationSystem;
}

void RequstHandler::run()
{

}

void RequstHandler::Stop()
{

}

bool RequstHandler::AddPassenger(Message_t* _msg)
{

}

bool RequstHandler::AddFlight(Message_t* _msg)
{

}

bool RequstHandler::RemoveFlight(Message_t* _msg)
{

}

bool RequstHandler::RemovePassenger(Message_t* _msg)
{

}

bool RequstHandler::ReserveTicket(Message_t* _msg)
{

}

bool RequstHandler::FreeFlightTicket(Message_t* _msg)
{

}
