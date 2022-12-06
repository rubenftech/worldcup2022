#ifndef TEAM_H_
#define TEAM_H_

#include"Player.h"

class Team{
public:
    Team(int team_id, int team_points, int numOfPlayers=0, int goal=0, int cards=0);
    ~Team();
    Team& operator=(const Team&)=default;

    void addPlayer(Player *player);
    void removePlayer(Player *player);
    void addPoints(int pointsToAdd);
    void addPlayedGame();
    void addGoals(int);
    void addCards(int);
    void putAVLid(AVL<int,Player*>);
    void putAVLGoal(AVL<PlayerStats, Player*>);
    void updateBestPlayer();
    void updateBestPlayer(Player *player);
    void addGoalKeeper(int def=1);

    int getTeamId()const;
    int getPoints()const;
    int getNumOfPlayer()const;
    int getTotalGoal() const;
    int getTotalCards() const;
    int get_game_played()const;
    Player* getBestPlayer()const;
    bool isValid() const;
    AVL<int, Player*>* getAvlTeamPlayersById();
    AVL<PlayerStats, Player*>* getAvlTeamPlayersByGoals();


private:
    AVL<int, Player*> teamPlayersById;
    AVL<PlayerStats, Player*> teamPlayersByGoals;
    Player* m_bestTeamPlayer;

    int m_numOfGoalKeeper=0;
    int m_team_id;
    int m_numOfPlayers;
    int m_points;
    int m_total_goal;
    int m_total_cards;
    int m_game_played;

};
bool operator>(const Team& team1, const Team& team2);

#endif