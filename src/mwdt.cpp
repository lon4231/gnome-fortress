#include "mwdt.h"

uint8_t dwarf_rng()
{

}

dwarf_buffer_t gen_dwarf_buffer(uint32_t size)
{
dwarf_buffer_t buffer;

buffer.dwarf_buffer=(dwarf_t*)malloc(size*sizeof(dwarf_t));
buffer.dwarf_count=size;

for(uint32_t i=0;i<size;++i)
{
buffer.dwarf_buffer[i].attribs.q=dwarf_rng();
buffer.dwarf_buffer[i].attribs.health=dwarf_rng();
buffer.dwarf_buffer[i].attribs.armor=dwarf_rng();
buffer.dwarf_buffer[i].attribs.dmg=dwarf_rng();
}

return buffer;
}