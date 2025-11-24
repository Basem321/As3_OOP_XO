#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"

class SUS_Board : public Board<char> {
private:
    int s_score;
    int u_score;

public:
    SUS_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    int get_s_score() const { return s_score; }
    int get_u_score() const { return u_score; }
};

class SUS_UI : public UI<char> {
public:
    SUS_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    Player<char>** setup_players() override;
};

#endif // SUS_CLASSES_H