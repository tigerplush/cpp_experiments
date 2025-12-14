#ifndef ITERABLE_BASE_H_
#define ITERABLE_BASE_H_

namespace Core
{
    template <typename Derived>
    class IterableBase
    {
    private:
        Derived &derived() { return static_cast<Derived &>(*this); }
        const Derived &derived() const { return static_cast<const Derived &>(*this); }

    public:
        size_t count() const
        {
            size_t count = 0;
            for (auto it = derived().begin(); it != derived().end(); ++it)
            {
                count += 1;
            }
            return count;
        }
    };
} // namespace Core

#endif