#include <iostream>
#include <memory>

using namespace std;

class BaseAdpatee
{
public:
    virtual ~BaseAdpatee() = default;
    virtual void specificRequest() = 0;
};

class ConcreteAdaptee: public BaseAdpatee
{
public:
    virtual void specificRequest() override
    {
        cout<<"ConcreteAdaptee method"<<endl;
    }
};

class Adapter
{
public:
    virtual ~Adapter() = default;
    virtual void request() = 0;
};

class ConcreteAdapter: public Adapter
{
public:
    ConcreteAdapter(shared_ptr<BaseAdpatee> adaptee): adaptee(adaptee) {}
    void request() override
    {
        cout<<"Adapter: ";
        if (adaptee)
            adaptee->specificRequest();
        else
            cout<<"Empty!"<<endl;
    }

private:
    shared_ptr<BaseAdpatee> adaptee;
};


int main()
{
    shared_ptr<BaseAdpatee> adaptee = make_shared<ConcreteAdaptee>();
    shared_ptr<Adapter> adapter = make_shared<ConcreteAdapter>(adaptee);

    adapter->request();
    return 0;
}

/*
Output:
Adapter: ConcreteAdaptee method
*/