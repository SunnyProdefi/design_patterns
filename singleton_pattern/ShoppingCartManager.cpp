#include <iostream>
#include <map>

using namespace std;

class ShoppingCarManager
{
public:
    static ShoppingCarManager& getInstance()
    {
        static ShoppingCarManager instance;
        return instance;
    }

    void addToCart(const string& itemName, int quantity) { cart[itemName] += quantity; }

    void viewCart() const
    {
        for (const auto& item : cart)
        {
            cout << item.first << " " << item.second << endl;
        }
    }

private:
    // 私有构造函数
    ShoppingCarManager() {}

    // 购物车存储商品和数量的映射
    map<string, int> cart;
};

int main()
{
    string itemName;
    int quantity;

    while (cin >> itemName >> quantity)
    {
        // 获取购物车实例并添加商品
        ShoppingCarManager& cart = ShoppingCarManager::getInstance();
        cart.addToCart(itemName, quantity);
    }

    const ShoppingCarManager& cart = ShoppingCarManager::getInstance();
    cart.viewCart();

    return 0;
}