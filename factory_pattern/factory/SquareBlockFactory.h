#pragma once
#include "BlockFactory.h"
#include "SquareBlock.h"

class SquareBlockFactory : public BlockFactory
{
public:
    Block* createBlock() override;
};