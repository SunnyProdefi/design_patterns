#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <string>

class Product
{
public:
    virtual void use() = 0;
    virtual ~Product() = default;
};

// 工厂类
class Factory
{
public:
    using Creator = std::function<std::unique_ptr<Product>()>;

    static Factory& instance()
    {
        static Factory f;
        return f;
    }

    void registerProduct(const std::string& name, Creator creator) { creators[name] = std::move(creator); }

    std::unique_ptr<Product> create(const std::string& name)
    {
        if (creators.count(name))
            return creators[name]();
        return nullptr;
    }

private:
    std::unordered_map<std::string, Creator> creators;
};

template <typename T>
class Registrar
{
public:
    Registrar(const std::string& name)
    {
        Factory::instance().registerProduct(name, []() { return std::make_unique<T>(); });
    }
};

#define REGISTER_PRODUCT_CLASS(T, name) static Registrar<T> reg_##T(name);

class ProductA : public Product
{
public:
    void use() override { std::cout << "Using ProductA\n"; }
};
REGISTER_PRODUCT_CLASS(ProductA, "A")

class ProductB : public Product
{
public:
    void use() override { std::cout << "Using ProductB\n"; }
};
REGISTER_PRODUCT_CLASS(ProductB, "B")

int main()
{
    auto p1 = Factory::instance().create("A");
    auto p2 = Factory::instance().create("B");

    p1->use();  // 输出 Using ProductA
    p2->use();  // 输出 Using ProductB
}
