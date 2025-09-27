#pragma once
#include "Block.h"

class BlockFactory
{
public:
    virtual Block* createBlock() = 0;
    virtual ~BlockFactory() = default;
};