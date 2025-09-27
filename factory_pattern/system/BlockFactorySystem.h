#pragma once
#include <vector>
#include "BlockFactory.h"  // 需要工厂接口
#include "Block.h"         // 需要Block* 类型

class BlockFactorySystem
{
private:
    std::vector<Block*> blocks;  // 存放生产的积木对象

public:
    // 生产积木
    void produceBlocks(BlockFactory* factory, int quantity);

    // 获取所有积木
    const std::vector<Block*>& getBlocks() const;

    // 析构函数释放积木内存
    ~BlockFactorySystem();
};