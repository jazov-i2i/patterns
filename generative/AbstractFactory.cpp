#include <iostream>
#include <memory>

using namespace std;

class Image {}; class Color {};

class BasePen
{

};

class BaseBrush
{

};

class Pen: public BasePen
{

};


class Brush: public BaseBrush
{

};

class BaseGraphics
{
public:
    virtual ~BaseGraphics() = 0;
};

class ConcreteGraphics: public BaseGraphics
{
public:
    ConcreteGraphics()
    {
        cout << "Calling the ConcreteGraphics constructor;" << endl; 
    }

    ~ConcreteGraphics() override
    {
        cout<<"Calling the ConcreteGraphics destructor"<<endl;
    }
};

class AbstractGraphFactory
{
public:
    virtual unique_ptr<BaseGraphics> createGraphics(shared_ptr<Image> img) = 0;
    virtual unique_ptr<BaseBrush> createBrush(shared_ptr<Color> cl) = 0;
    virtual unique_ptr<BasePen> createPen(shared_ptr<Color> cl) = 0;
};

class ConcreteGraphFactory: public AbstractGraphFactory
{
public:
    unique_ptr<BaseGraphics> createGraphics(shared_ptr<Image> img) override
    {
        return make_unique<ConcreteGraphics>();
    }
    unique_ptr<BaseBrush> createBrush(shared_ptr<Color> cl) override
    {
        return make_unique<Brush>();
    }
    unique_ptr<BasePen> createPen(shared_ptr<Color> cl) override
    {
        return make_unique<Pen>();
    }
};

class User
{
public:
    void use(shared_ptr<AbstractGraphFactory>& agr)
    {
        shared_ptr<Image> img = make_shared<Image>();
        // auto graphics = agr->createGraphics();
    }
};



int main()
{
    return 0;
}