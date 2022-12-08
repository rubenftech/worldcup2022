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
    explicit PlayerStats(int goals = 0, int cards = 0, int id = 0);
    ~PlayerStats() = default;
    PlayerStats operator-(const PlayerStats& playerStats)const;
    friend bool operator>(const PlayerStats& player1, const PlayerStats& player2);
    friend bool operator==(const PlayerStats& player1, const PlayerStats& player2);
};

bool operator<(const PlayerStats& player1, const PlayerStats& player2);
bool operator!=(const PlayerStats& player1, const PlayerStats& player2);


class Player{
public:
    Player(int playerId, int teamId, int gamesPlayed=0, int goals=0, int cards=0, bool goalKeeper=0);
    ~Player() = default;
    Player(const Player&)=default;
    Player& operator=(Player&)=default;

    void addGames(int newGames = 1);
    void addGoals(int newGoals);
    void addCards(int newCards);
    void setTeam(Team* teamPtr);
    void setPreviousInRank(Player* player);
    void setNextInRank(Player* player);
    void updatePreviousAndNextInRank(AVL<PlayerStats, Player*>& rankedTree);
    int getId()const;
    int getNumGames() const;
    int getCards() const;
    int getGoals() const;
    Team* getTeam();
    bool isGoalKeeper() const;
    PlayerStats getStats()const;
    Player* getPreviousInRank()const;
    Player* getNextInRank()const;
    PlayerStats getPlayerStats()const;
    int getClosest();


private:
    int m_playerId;
    int m_gamePlayed;
    int m_goals;
    int m_cards;
    bool m_goalKeeper;
    Team* m_team_ptr;
    Player* m_previousInRank;
    Player* m_nextInRank;

};

#endif //PLAYER_H_

