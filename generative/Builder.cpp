#include <iostream>
#include <memory>

using namespace std;

class IProduct
{
public:
    virtual ~IProduct() = default;
    virtual void doSome() = 0;
};

class ConcreteProduct: public IProduct
{
public:
    ConcreteProduct()
    {
        cout<<"ConcreteProduct constructor"<<endl;
    }
    ~ConcreteProduct() override
    {
        cout<<"ConcreteProduct destructor"<<endl;
    }
    void doSome() override
    {
        cout<<"ConcreteProduct: doSome"<<endl;
    }
};

class IProductBuilder
{
public:
    virtual ~IProductBuilder() = default;
    virtual bool createPartA() = 0;
    virtual bool createPartB() = 0;

    shared_ptr<IProduct> getProduct()
    {
        if (!product) product = create();
        return product;
    }
protected:
    size_t part { 0 };
    shared_ptr<IProduct> product { nullptr }; 
    virtual shared_ptr<IProduct> create() = 0;
};

class ConcreteProductBuilder: public IProductBuilder
{
public:
    bool createPartA() override
    {
        if (!part)
            ++part;
        
        if (part != 1) return false;

        cout<<"Build part A"<<endl;
        return true;
    }
    bool createPartB() override
    {
        if (part == 1)
            ++part;
        
        if (part != 2) return false;

        cout<<"Build part B"<<endl;        
        return true;
    }

protected:
    shared_ptr<IProduct> create() override
    {
        if (part == 2)
            product = make_shared<ConcreteProduct>();
        return product;
    }
};

class IDirector
{
public:
    virtual ~IDirector() = default;
    virtual shared_ptr<IProduct> create() = 0;
};

class Director: public IDirector
{
public:
    Director(shared_ptr<IProductBuilder> builder): builder(builder) {}

    shared_ptr<IProduct> create() override
    {
        if (builder->createPartA() && builder->createPartB())
            return builder->getProduct();
        return nullptr;
    }
private:
    shared_ptr<IProductBuilder> builder;
};

class User
{
public:
    void use(shared_ptr<IDirector> director)
    {
        shared_ptr<IProduct> product = director->create();
        if (product)
            product->doSome();
    }
};

int main()
{
    shared_ptr<IProductBuilder> builder = make_shared<ConcreteProductBuilder>();
    shared_ptr<IDirector> director = make_shared<Director>(builder);

    User{}.use(director);
    return 0;
}

/*
Output:
Build part A
Build part B
ConcreteProduct constructor
ConcreteProduct: doSome
ConcreteProduct destructor
*/