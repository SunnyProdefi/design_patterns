#include "BlockFactorySystem.h"

void BlockFactorySystem::produceBlocks(BlockFactory* factory, int quantity)
{
    for (int i = 0; i < quantity; ++i)
    {
        Block* block = factory->createBlock();
        blocks.push_back(block);
        block->produce();
    }
}

const std::vector<Block*>& BlockFactorySystem::getBlocks() const { return blocks; }

BlockFactorySystem::~BlockFactorySystem()
{
    for (Block* block : blocks)
    {
        delete block;
    }
}