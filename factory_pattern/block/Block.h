#pragma once
#include <iostream>

class Block
{
public:
    virtual void produce() = 0;
    virtual ~Block() = default;
};