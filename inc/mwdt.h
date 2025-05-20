#ifndef _MAGIC_WORKING_DWARF_THREAD_DEFINED_
#define _MAGIC_WORKING_DWARF_THREAD_DEFINED_

#include "headers.h"

struct dwarf_attribs_t
{
    uint16_t q : 4;
    uint16_t health : 2;
    uint16_t armor : 2;
    uint16_t dmg : 2;

} __attribute__((packed));

struct dwarf_t
{
    uint16_t x;
    uint16_t y;

    uint16_t active_task;
    dwarf_attribs_t attribs;

} __attribute__((packed));

struct dwarf_team_t
{
    uint32_t team_size;
    dwarf_t **dwarf_buffer;

    uint16_t target_x;
    uint16_t target_y;
}__attribute__((packed));

struct dwarf_batch_t
{
dwarf_t batch_items[4096];
dwarf_batch_t*next;
}__attribute__((packed));

struct dwarf_buffer_t
{
    uint16_t id;
    uint32_t dwarf_count;
    dwarf_batch_t *dwarf_buffer;
};


dwarf_buffer_t gen_dwarf_buffer(uint32_t size);







#endif