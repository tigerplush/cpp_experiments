#ifndef ENTITY_META_DATA_H_
#define ENTITY_META_DATA_H_


namespace ECS
{
    struct EntityMetaData
    {
    public:
        EntityMetaData(size_t t_table_id, size_t t_table_row)
        : table_id(t_table_id)
        , table_row(t_table_row)
        {
        }

        size_t table_id;
        size_t table_row;
    };
} // namespace ECS

#endif