#ifndef PLAYER_H_
#define PLAYER_H_
#include "AVL_TREE_TEMPLATE.h"

class Team;

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
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
    ~Player() = default;
    int getId()const;
    void addGames(int newGames = 1);
    int getNumGames() const;
    void addGoals(int newGoals);
    int getGoals() const;
    void addCards(int newCards);
    int getCards() const;
    bool isGoalKeeper() const;
<<<<<<< HEAD
    void setTeam(Team* teamPtr);
    void updatePreviousInRank(AVL<PlayerStats, Player*> rankedTree);
=======
    void putTeam(Team*);
    void updatePreviousInRank(AVL<PlayerStats, Player> rankedTree);
>>>>>>> bbd610c391c92cf9bebbed0f2a7c24eb1c41041f
    Player* GetpreviousInRank()const;
    Player* GetNextInRank()const;
    void updateNextInRank(AVL<PlayerStats, Player*> rankedTree);
    PlayerStats getPlayerStats()const;

private:
    const int m_playerId;
    int m_gamePlayed;
    int m_goals;
    int m_cards;
    const bool m_goalKeeper;
    Team* m_team_ptr;
    Player* m_previousInRank;
    Player* m_nextInRank;

};

#endif //PLAYER_H_