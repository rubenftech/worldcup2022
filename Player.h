#ifndef PLAYER_H_
#define PLAYER_H_
#include "AVL_TREE_TEMPLATE.h"
class PlayerStats{
private: 
    int m_goals;
    int m_cards;
    int m_playerId;
public:
    PlayerStats(int goals, int cards, int id);
    ~PlayerStats() = default;
    friend bool operator>(const PlayerStats& player1, const PlayerStats& player2);
    friend bool operator==(const PlayerStats& player1, const PlayerStats& player2);
};

bool operator<(const PlayerStats& player1, const PlayerStats& player2);
bool operator!=(const PlayerStats& player1, const PlayerStats& player2);
class Player{
public:
    Player(int playerId, int gamesPlayed, int goals, int cards, bool goalKeeper);
    ~Player() = default;
    int getId()const;
    void addGames(int newGames = 1);
    int getGames() const;
    void addGoals(int newGoals);
    int getGoals() const;
    void addCards(int newCards);
    int getCards() const;
    bool isGoalKeeper() const;
    void updatePreviousInRank(AVL<PlayerStats, Player> rankedTree);
    Player* GetpreviousInRank()const;
    void updateNextInRank();
    Player* GetNextInRank()const;
    PlayerStats getPlayerStats()const;

private:
    const int m_playerId;
    int m_gamePlayed;
    int m_goals;
    int m_cards;
    const bool m_goalKeeper;
    Player* m_previousInRank;
    Player* m_nextInRank;

};
Player* findPreviousInRank;
#endif //PLAYER_H_