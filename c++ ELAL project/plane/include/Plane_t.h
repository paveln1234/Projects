#ifndef PLANE_T_H
#define PLANE_T_H
#include <vector>
#include <string>
#include "Iplane.h"
using namespace std;

class Plane_t :public Iplane
{
    friend class PlaneFactory;
    public:
        /** Default destructor */
        virtual ~Plane_t();
         /** create new Plane */
        virtual void Create() ;

         /** Set new Plane Type    */
        virtual void SetType(const string& _type){m_type = _type;}

         /** Get Plane type
         * \return Plane type
         */
        virtual const string& GetType()const {return m_type;}

         /** Set Plane Arrangement
         * \param vector<pair<string,size_t> _PlaneArrange- vector of pairs <string - Tier name, size_t - tier capacity
         */
        virtual void SetPlaneArrangement(vector<pair <string,size_t> >& _PlaneArrangement);

         /** Get Plane Arrangement
         * \return vector<pair<string,size_t>& - vector of pairs <string - Tier name, size_t - tier capacity
         */
        virtual const vector<pair <string,size_t> >& GetPlaneArrangement()const;

         /** Set Plane id      */
        virtual void SetId(const string& _id){m_id = _id;}

        /** Get Plane is
         * \return string& plane id
         */
        virtual const string& GetId()const {return m_id;}
        /** print plane data */
        void PrintPlane()const ;

        static Iplane* NewPlane(){return new Plane_t;}

    private:
        Plane_t(const Plane_t& other);
        Plane_t& operator=(const Plane_t& other);
        Plane_t(){};

    private:
        string m_type;
        string m_id;
        vector<pair<string,size_t> > m_PlaneArrangement;
        size_t m_capacity;

};

#endif // PLANE_T_H
