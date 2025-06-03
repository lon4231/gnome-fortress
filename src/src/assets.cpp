#include <assets.h>
#include <rndr_routines.h>

runtime_assets_t runtime_assets;

void load_assets()
{
    runtime_assets.menu_bg = routines_load_texture("assets/sprites/absolutegnome.png");
    runtime_assets.game_bg = routines_load_texture("assets/sprites/bg.png");
    runtime_assets.title_texture = routines_render_text_texture("GNOME FORTRESS", {47, 87, 83, 255});
    runtime_assets.buttons_texture = routines_load_texture("assets/sprites/button.png");
    runtime_assets.board_tiles=routines_load_texture("assets/sprites/tiles.png");   
    runtime_assets.songloop0=Mix_LoadMUS("assets/sound/songloop0.mp3");
    runtime_assets.songloop1=Mix_LoadMUS("assets/sound/songloop1.mp3");
}