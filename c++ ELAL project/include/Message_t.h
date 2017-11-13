#ifndef MESSAGE_T_H
#define MESSAGE_T_H
#include <list>
#include <string>
using namespace std;

class Message_t
{
    public:
        enum MsgType{GETER,SETER,END,ERROR};
        enum ClassType{FLIGHT,BOOKING,PASSENGER};

        Message_t();
        Message_t(const Message_t& other);
        Message_t& operator=(const Message_t & other);

        virtual ~Message_t();

        /** set the message type
        *\param MsgType _type - message type
        */
        void SetMsgType(MsgType _type) {m_type =_type;}

        /** Get the message type
        *\return MsgType - message type
        */
        MsgType GetMsgType()const {return m_type;}

        /** set the message class
        *\param ClassType _type - message class
        */
        void SetClass(ClassType _type) {m_class = _type;}

        /** Get the message class
        *\return ClassType - message type
        */
        ClassType GetClass()const {return m_class;}

        /** set function that need to use
        *\param const string& _funcname - function as string
        */
        void SetFunc(const string& _funcname) {m_funcname = _funcname;}

        /** Get function
        *\return string - function to use
        */
        const string GetFuncName(){return m_funcname;}

        /** add string to message
        *\param const string& _param - string to add
        */
        void AddParamsString( string& _param) {m_strings.push_back(_param);}

        /** Get string from message
        *\return string
        */
        string GetStrings()  {string str =  m_strings.front();m_strings.pop_front(); return str;}

        /** add number to message
        *\param size_t _num - number to add
        */
        void AddParamseNum(size_t _num) {m_num.push_back(_num);}

        /** Get num from message
        *\return size_t
        */
        size_t GetParamseNum() {size_t num =  m_num.front() ;m_num.pop_front();return num;}

    public:
        MsgType m_type;
        ClassType m_class;
        string m_funcname;
        list<string> m_strings;
        list<size_t> m_num;
};

#endif // MESSAGE_T_H
