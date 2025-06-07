#include <client.h>
#include <game.h>

IPaddress client_ip;
SDLNet_SocketSet client_set;
TCPsocket client_socket;

void init_client(const char *host)
{
    SDLNet_ResolveHost(&client_ip, host, 0xB00B);
    client_socket = SDLNet_TCP_Open(&client_ip);
    client_set = SDLNet_AllocSocketSet(1);
    SDLNet_AddSocket(client_set, (SDLNet_GenericSocket)client_socket);
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

            break;

        default:
            break;
        }
    }
}
