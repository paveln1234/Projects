#ifndef PLANEMANAGER_H
#define PLANEMANAGER_H
#include <vector>
using namespace std;
class Iplane;

class PlaneManager
{
    public:
        PlaneManager();
        virtual ~PlaneManager();
        const Iplane* GetPlane(string& _planeId)const;
        void PrintPlain(const string& _planeId)const;
        virtual void PrintAllPlance()const;

    private:
        PlaneManager(const PlaneManager& _other);
        PlaneManager& operator = (const PlaneManager& _other);
        vector<Iplane*> m_planes;


};

#endif // PLANEMANAGER_H
