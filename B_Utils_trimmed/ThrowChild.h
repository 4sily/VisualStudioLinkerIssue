#pragma once

struct BaseWithVirtual
{
    virtual void what() {}       // !!! make this non-virtual --> Build succeeds
};

template<typename dummy>
struct ExceptionBase : public BaseWithVirtual
{
};

struct ExceptionChild : public  ExceptionBase<int>
{
};

inline void ThrowChild()
{
    ExceptionChild up;
    throw up;   // !!! comment this --> Build succeeds
}