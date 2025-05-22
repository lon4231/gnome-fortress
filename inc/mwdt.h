#ifndef _MAGIC_WORKING_GNOME_THREAD_DEFINED_
#define _MAGIC_WORKING_GNOME_THREAD_DEFINED_

#include "headers.h"
#include "rng.h"

struct gnome_attribs_t
{
    uint16_t q : 4;
    uint16_t health : 2;
    uint16_t armor : 2;
    uint16_t dmg : 2;

} __attribute__((packed));

struct gnome_t
{
    uint16_t x;
    uint16_t y;

    uint16_t active_task;
    gnome_attribs_t attribs;

}__attribute__((packed));

struct gnome_team_t
{
    uint32_t team_size;
    gnome_t *gnome_buffer;

    uint16_t target_x;
    uint16_t target_y;
}__attribute__((packed));

struct zone_def_t
{
uint32_t x;
uint32_t y;
uint8_t radius;
};

struct terrain_buffer_t
{
uint32_t w;
uint32_t h;

float*terrain;
uint16_t*biome;
uint16_t*resource_buffer;
zone_def_t*zdef;
zone_def_t*rs_zdef;

}__attribute__((packed));

gnome_team_t gen_gnome_team(uint32_t size);

terrain_buffer_t gen_terrain(uint32_t width,uint32_t height);



#endif