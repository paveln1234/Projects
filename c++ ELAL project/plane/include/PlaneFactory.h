#ifndef PLANEFACTORY_H
#define PLANEFACTORY_H
#include <string>
using namespace std;
class Iplane;

class PlaneFactory
{
    public:
        PlaneFactory(){};
        virtual ~PlaneFactory(){};
        Iplane* GetPlane(const string& _planeName);
};

#endif // PLANEFACTORY_H
