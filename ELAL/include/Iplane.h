#ifndef IPLANE_H
#define IPLANE_H
#include <string>
#include <vector>
using namespace std;

class Iplane
{
    public:

        virtual~Iplane(){};
        virtual void Create() = 0;
        virtual void SetType(const string& _type)=0;
        virtual const string& GetType()const=0;
        virtual void SetPlaneArrangement(vector<pair <string,size_t> >& _PlaneArrangement) = 0;
        virtual const vector<pair <string,size_t> >& GetPlaneArrangement()const = 0;
        virtual void SetId(const string& _id)=0;
        virtual const string& GetId()const =0;
        virtual void PrintPlane()const  = 0;


};

#endif // IPLANE_H
