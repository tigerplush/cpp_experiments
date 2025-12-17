#ifndef ICOLUMN_H_
#define ICOLUMN_H_

namespace ECS
{
    /// @brief Type erased column interface
    class IColumn
    {
    private:
    public:
        virtual ~IColumn()
        {}
    };
} // namespace ECS
#endif