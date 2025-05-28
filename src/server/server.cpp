#include <server/client.h>
#include <server/server.h>
#include <rndr_routines.h>

static bool srv_initialized=false;
server_state_t srv_state;

inline void handle_events()
{
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        handle_window(&event);
    };
}

void init_server(uint16_t port)
{
if(srv_initialized==false)
{
if(SDLNet_ResolveHost(&srv_state.server_addr,NULL,port)==-1)
{
printf("UNABLE TO RESOLVE HOST, FUCKER!: %s\r\n",SDLNet_GetError());
return;
}

srv_state.server_socket=SDLNet_TCP_Open(&srv_state.server_addr);
if(!srv_state.server_socket)
{
printf("COULDN'T OPEN TCP SERVER, IDIOT!: %s\r\n",SDLNet_GetError());
return;
}

srv_initialized=true;
}
else
{
printf("SEVER ALREADY OPEN, DUMBASS!\r\n");
}

uint32_t clients_connected=1;
char text_buffer[27];
memcpy(text_buffer,"WAITING FOR PLAYERS:\0\0\0\0\0\0",27);
sprintf(text_buffer,"WAITING FOR PLAYERS: %02d/%02d",clients_connected,srv_state.client_count);

SDL_Texture*text=routines_render_text_texture(text_buffer,{47, 87, 83, 255});
SDL_Rect rect={400-((13)*12),300-8,26*16,16};

srv_state.client_count=2;

while(window_hnd.running && (clients_connected<=srv_state.client_count))
{
handle_events();

TCPsocket client_socket=SDLNet_TCP_Accept(srv_state.server_socket);
if(client_socket)
{
printf("AHHHHHH\r\n");
clients_connected++;
sprintf(text_buffer,"WAITING FOR PLAYERS: %02d/%02d",clients_connected,srv_state.client_count);
}


SDL_SetRenderTarget(window_hnd.renderer,window_hnd.render_texture);

SDL_SetRenderDrawColor(window_hnd.renderer,0,0,0,255);
SDL_RenderClear(window_hnd.renderer);

SDL_RenderCopy(window_hnd.renderer,text,NULL,&rect);

SDL_SetRenderTarget(window_hnd.renderer,NULL);

routines_draw_window();
}

}

void handle_server()
{

}