#include <client.h>
#include <game.h>

IPaddress client_ip;
SDLNet_SocketSet client_set;
TCPsocket client_socket;

const char *client_name;

void init_client(const char *host, const char *name)
{
    SDLNet_ResolveHost(&client_ip, host, 0xB00B);
    client_socket = SDLNet_TCP_Open(&client_ip);
    client_set = SDLNet_AllocSocketSet(1);
    SDLNet_AddSocket(client_set, (SDLNet_GenericSocket)client_socket);
    client_name = name;
}

void handle_client()
{
    int ready = SDLNet_CheckSockets(client_set, 10);

    if (ready <= 0)
    {
        return;
    }

    if (SDLNet_SocketReady(client_socket))
    {
        data_request_t request;
        SDLNet_TCP_Recv(client_socket, &request, sizeof(data_request_t));

        printf("recv request: %d\r\n", request.request_type);
        switch (request.request_type)
        {
        case DATA_REQUEST_STATE:
            SDLNet_TCP_Send(client_socket, &game_state.remote_state, sizeof(game_server_state_t));
            break;

        case DATA_REQUEST_READY:
            ui_layer.button_active = true;
            client_send_request(client_socket, DATA_REQUEST_STATE, &game_state.remote_state);

            update_text_wall();
            break;

        case DATA_REQUEST_INITIAL:
        {
            game_server_client_t client_init_data;
            memcpy(client_init_data.name,client_name,8);
            SDLNet_TCP_Send(client_socket,&client_init_data,sizeof(game_server_client_t));
        }
        break

            default : break;
        }
    }
}
