#pragma once
#include "BlockFactory.h"
#include "CircleBlock.h"

class CircleBlockFactory : public BlockFactory
{
public:
    Block* createBlock() override;
};