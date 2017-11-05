#include "PlaneFactory.h"
#include "Iplane.h"
#include "Plane_t.h"


Iplane* PlaneFactory::GetPlane(const string& _planeName)
{
    Iplane* ptr = 0;
    if("Plane" == _planeName)
        ptr= new Plane_t;

return ptr;
}
