#ifndef MY_COMPARISIONS_H
#define MY_COMPARISIONS_H

template <typename Derived>
class SimpleOrderOperators
{
	Derived* self;
protected:
	constexpr SimpleOrderOperators() : self{static_cast<Derived*>(this)} {}

public:
	constexpr bool operator<(Derived const& rhs) { return self->value < rhs.value; }
	constexpr bool operator==(Derived const& rhs) { return self->value == rhs.value; }
};

template <typename Derived>
class AddOrderOperators
{
	Derived* self;
protected:
	constexpr AddOrderOperators() : self{static_cast<Derived*>(this)} {}

public:
	constexpr bool operator>(Derived const& rhs) { return !(self->operator<(rhs) && self->operator==(rhs)); }
	constexpr bool operator>=(Derived const& rhs) { return !self->operator<(rhs); }
	constexpr bool operator<=(Derived const& rhs) { return self->operator<(rhs) || self->operator==(rhs); }
	constexpr bool operator!=(Derived const& rhs) { return !self->operator==(rhs); }
};






#endif // MY_COMPARISIONS_H

