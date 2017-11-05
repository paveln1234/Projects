#ifndef IMESSAGE_H
#define IMESSAGE_H

template<typename T>
class Imessage
{
    public:

        virtual ~Imessage(){};
        virtual void SetData(const T& _data ) = 0;
        virtual T& GetData() const = 0;

    private:
    T m_data;
};

#endif // IMESSAGE_H
