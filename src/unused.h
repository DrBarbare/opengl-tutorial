#ifndef MY_UNUSED_H
#define MY_UNUSED_H

namespace my
{
template<typename... T>
void unused(T&&...) {}
} // namespace my;

#endif // MY_UNUSED_H
