#include "mwdt.h"

gnome_team_t gen_gnome_team(uint32_t size)
{
    rng_state = time(NULL);
    static uint8_t rng_n;
    gnome_team_t team;

    team.gnome_buffer = (gnome_t *)malloc(size * sizeof(gnome_t));
    team.team_size = size;

    for (uint32_t i = 0; i < size; i++)
    {
        rng_n = fast_rng();
        team.gnome_buffer[i].attribs.q = rng_n;
        team.gnome_buffer[i].attribs.dmg = rng_n >> 4;
        rng_n = fast_rng();
        team.gnome_buffer[i].attribs.armor = rng_n;
        team.gnome_buffer[i].attribs.health = rng_n >> 4;
    }

    return team;
}

terrain_buffer_t gen_terrain(uint32_t width, uint32_t height)
{
    terrain_buffer_t terrain;

    terrain.w = width;
    terrain.h = height;

    terrain.terrain = (float *)malloc(width * height * sizeof(float));
    terrain.biome = (uint16_t *)malloc(width * height * sizeof(uint16_t));

    rng_state = time(NULL);

    for (uint32_t y = 0; y < height; ++y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {

            terrain.terrain[x + (y * width)] = 0;

            for (uint32_t n = 0; n < 5; ++n)
            {
                uint32_t r_n_x = fast_rng() % 32;
                uint32_t r_n_y = fast_rng() % 32;

                float noise = ((glm::perlin(
                                    glm::vec2(
                                        (((float)x + ((float)r_n_x)) * (0.01f * (1.0f / (n + 1)))),
                                        (((float)y + ((float)r_n_y)) * (0.01f * (1.0f / (n + 1)))))) *
                                0.5f) +
                               0.5f);

                terrain.terrain[x + (y * width)] += noise * 0.1 * (1.0 / ((n * 2) + 1));
            }
            terrain.terrain[x + (y * width)] = (terrain.terrain[x + (y * width)] > 1) ? 1 : terrain.terrain[x + (y * width)];
        }
    }
    rng_state = time(NULL);

    uint8_t zone_count = mmax(fast_rng() % 32, 16);

    zone_def_t *zones = (zone_def_t *)malloc(zone_count * sizeof(zone_def_t));

    for (uint8_t i = 0; i < zone_count; ++i)
    {
        zones[i].x = fast_rng() % width;
        zones[i].y = fast_rng() % height;
        zones[i].radius = fast_rng() % 128;
    }

    terrain.zdef=zones;

    for (uint32_t y = 0; y < height; ++y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {
            uint8_t nearest_zone=0;
            float nearest_dist=FLT_MAX;
            for(uint8_t i=0;i<zone_count;++i)
            {
                float dist=sqrtf(((zones[i].x-x)*(zones[i].x-x))+((zones[i].y-y)*(zones[i].y-y)));
                if(dist<nearest_dist)
                {
                nearest_dist=dist;
                nearest_zone=i;
                }
            }
            terrain.biome[x+(y*width)]=nearest_zone;
        }
    }

    return terrain;
}