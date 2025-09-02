#include <memory>
#include <iostream>

using namespace std;

class IProduct
{
public:
    virtual ~IProduct() = default;
    virtual void doSome() = 0;
};

class ConcreteProduct_1: public IProduct
{
public:
    ConcreteProduct_1()
    {
        cout<<"ConcreteProduct_1 constructor called"<<endl;
    }
    ~ConcreteProduct_1() override
    {
        cout<<"ConcreteProduct_1 destructor called"<<endl;
    }
    void doSome() override
    {
        cout<<"do Some ConcreteProduct_1"<<endl;
    }
};

class ConcreteProduct_2: public IProduct
{
public:
    ConcreteProduct_2()
    {
        cout<<"ConcreteProduct_2 constructor called"<<endl;
    }
    ~ConcreteProduct_2() override
    {
        cout<<"ConcreteProduct_2 destructor called"<<endl;
    }
    void doSome() override
    {
        cout<<"do Some ConcreteProduct_2"<<endl;
    }
};

class ProductCreator
{
public: 
    virtual ~ProductCreator() = default;
    virtual unique_ptr<IProduct> createProduct() const = 0;
};

class ConcreteProductCreator_1: public ProductCreator
{
public:
    ~ConcreteProductCreator_1() override
    {
        cout<<"ConcreteProductCreator_1 destructor called"<<endl;
    }
    unique_ptr<IProduct> createProduct() const override
    {
        return make_unique<ConcreteProduct_1>();
    }
};

class ConcreteProductCreator_2: public ProductCreator
{
public:
    ~ConcreteProductCreator_2() override
    {
        cout<<"ConcreteProductCreator_2 destructor called"<<endl;
    }
    unique_ptr<IProduct> createProduct() const override
    {
        return make_unique<ConcreteProduct_2>();
    }
};

template <typename T>
void print_type(const T&) {
    cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
    unique_ptr<ProductCreator> pCreator = make_unique<ConcreteProductCreator_1>();
    print_type(pCreator);
    auto product = pCreator->createProduct();
    print_type(product);
    product->doSome();
    
    pCreator = make_unique<ConcreteProductCreator_2>();
    print_type(pCreator);
    product = pCreator->createProduct();
    print_type(product);
    product->doSome();
    return 0;
}

// Output:
/*
void print_type(const T&) [with T = std::unique_ptr<ProductCreator>]
ConcreteProduct_1 constructor called
void print_type(const T&) [with T = std::unique_ptr<IProduct>]
do Some ConcreteProduct_1
ConcreteProductCreator_1 destructor called
void print_type(const T&) [with T = std::unique_ptr<ProductCreator>]
ConcreteProduct_2 constructor called
ConcreteProduct_1 destructor called
void print_type(const T&) [with T = std::unique_ptr<IProduct>]
do Some ConcreteProduct_2
ConcreteProduct_2 destructor called
ConcreteProductCreator_2 destructor called
*/  