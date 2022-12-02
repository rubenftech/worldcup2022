
#include"Player.h"

class Team{
public:
    Team(int team_id, int team_points);
    ~Team();
    void addPlayer(Player *player);
    void removePlayer(Player *player);
    int getNumOfPlayer()const;
    void addPoints(int pointsToAdd);
    int getPoints()const;
    int updateBestPlayer();
    int updateBestPlayer(Player *player);


private:
    AVL<int, Player*> teamPlayersById;
    AVL<PlayerStats, Player*> teamPlayersByGoals;
    int m_numOfPlayers;
    int m_points;
    Player* m_bestTeamPlayer;
};
