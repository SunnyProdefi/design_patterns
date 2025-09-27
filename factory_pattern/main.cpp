#include "BlockFactorySystem.h"
#include "CircleBlockFactory.h"
#include "SquareBlockFactory.h"
#include <iostream>

int main()
{
    BlockFactorySystem factorySystem;
    int productionCount;
    std::cin >> productionCount;

    for (int i = 0; i < productionCount; i++)
    {
        std::string blockType;
        int quantity;
        std::cin >> blockType >> quantity;

        if (blockType == "Circle")
        {
            factorySystem.produceBlocks(new CircleBlockFactory(), quantity);
        }
        else if (blockType == "Square")
        {
            factorySystem.produceBlocks(new SquareBlockFactory(), quantity);
        }
    }
    return 0;
}