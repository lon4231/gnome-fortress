#include <server.h>
#include <game_server.h>
#include <client.h>

bool running;

uint32_t players_ready = 0;
uint32_t clients_connected = 0;

game_server_state_t game_state;

SDLNet_SocketSet server_set;

IPaddress server_addr;
TCPsocket server_socket;
TCPsocket client_sockets[MAX_CLIENTS];

inline void handle_events()
{
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = 0;
            break;

        default:
            break;
        }
    };
}

void handle_client_joins()
{

    TCPsocket newsocket = SDLNet_TCP_Accept(server_socket);

    if (newsocket != NULL)
    {
        client_sockets[clients_connected] = newsocket;
        SDLNet_TCP_AddSocket(server_set, newsocket);

        clients_connected++;
    }
}

void handle_requests()
{
    int num_ready = SDLNet_CheckSockets(server_set, 10);
    if (num_ready <= 0)
    {
        return;
    }

    data_request_t data_request;

    for (uint32_t i = 0; i < clients_connected; ++i)
    {
        TCPsocket sock = client_sockets[i];

        if (SDLNet_SocketReady(sock))
        {
            int received = SDLNet_TCP_Recv(sock, &data_request, sizeof(data_request_t));
            if (received <= 0)
            {
                SDLNet_TCP_DelSocket(server_set, sock);
                SDLNet_TCP_Close(sock);
                client_sockets[i] = client_sockets[clients_connected - 1];
                client_sockets[clients_connected - 1] = NULL;
                --clients_connected;
                --i;
                continue;
            }
            printf("recv request: %d\r\n",data_request.request_type);
            switch (data_request.request_type)
            {
            case DATA_REQUEST_STATE:
                SDLNet_TCP_Send(sock, &game_state, sizeof(game_server_state_t));
                break;

            case DATA_REQUEST_READY:
                players_ready++;
                break;

            default:
                break;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();
    SDLNet_ResolveHost(&server_addr, NULL, 0xB00B);
    server_socket = SDLNet_TCP_Open(&server_addr);
    server_set = SDLNet_AllocSocketSet(MAX_CLIENTS);
    running = true;
    init_game_state(&game_state, MAX_CLIENTS);

    while (running)
    {
        handle_events();
        handle_client_joins();
        if (clients_connected > 0)
        {
            handle_requests();
            if (players_ready >= clients_connected)
            {
                update_game_state(&game_state);
                for (uint32_t i = 0; i < clients_connected; ++i)
                {
                    client_send_request(client_sockets[i], DATA_REQUEST_READY, NULL);
                }
                players_ready=0;
            }
        }
    }

    return 0;
}