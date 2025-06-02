#include <assets.h>
#include <rndr_routines.h>

runtime_assets_t runtime_assets;

void load_assets()
{
    runtime_assets.menu_bg = routines_load_texture("assets/sprites/absolutegnome.png");
    runtime_assets.title_texture = routines_render_text_texture("GNOME FORTRESS", {47, 87, 83, 255});
    runtime_assets.buttons_texture = routines_load_texture("assets/sprites/button.png");
    runtime_assets.board_tiles=routines_load_texture("assets/sprites/tiles.png");   
}