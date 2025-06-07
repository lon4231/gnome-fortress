#include <game_server.h>

void init_game_state(game_server_state_t *game_state, uint32_t client_count)
{
    game_state->client_count = client_count;

    for (uint32_t i = 0; i < (BOARD_W * BOARD_H); ++i)
    {
        game_state->board[i] = 2;
        game_state->disp_board[i] = rand() % 4;
    }

    for (uint32_t i = 0; i < 32; ++i)
    {
        uint32_t pos = rand() % (BOARD_W * BOARD_H);
        game_state->upper_board[pos] = 3;
        pos = rand() % (BOARD_W * BOARD_H);
        game_state->upper_board[pos] = 4;
    }

    /*  for (uint32_t i = 0; i < 32; ++i)
      {
      }
  */
    for (uint16_t i = 0; i < client_count; ++i)
    {
        while (true)
        {
            uint32_t pos = rand() % (BOARD_W * BOARD_H);

            if (game_state->upper_board[pos] == 0)
            {
                game_state->upper_board[pos] = 1;
                game_state->upper_disp_board[pos] = i;
                break;
            }
        }
    }
}

void update_game_state(game_server_state_t*game_state)
{

for(uint32_t i=0;i<game_state->client_count;++i)
{
game_server_client_t*client=&game_state->clients[i];

client->poblation*=client->poblation_breed_rate;



}

}