
#include"Player.h"

class Team{
public:
    Team(int team_id, int team_points);
    ~Team();
    void addPlayer(Player *player);
    void removePlayer(Player *player);
    int getNumOfPlayer()const;
    void addPoints(int pointsToAdd);
    void addPlayedgame();
    int getPoints()const;
    int getTotalcards() const;
    int getTotalGoal() const;
    int get_game_played()const;
    int updateBestPlayer();
    int updateBestPlayer(Player *player);
    bool operator >(const Team* team1, const Team* team2);


private:
    AVL<int, Player*> teamPlayersById;
    AVL<PlayerStats, Player*> teamPlayersByGoals;
    Player* m_bestTeamPlayer;

    int m_numOfPlayers;
    int m_points;
    int m_total_goal;
    int m_total_cards;
    int m_game_played;


};
