
#include"Player.h"

class Team{
public:
    Team(int team_id, int team_points, int numOfPlayers=0, int goal=0, int cards=0);
    ~Team();
    void addPlayer(Player *player);
    void removePlayer(Player *player);
    int getNumOfPlayer()const;
    void addPoints(int pointsToAdd);
    void addPlayedGame();
    int getPoints()const;
    int getTotalCards() const;
    int getTotalGoal() const;
    int get_game_played()const;
    void putAVLid(AVL<int,Player*>);
    void putAVLGoal(AVL<PlayerStats, Player*>);
    int updateBestPlayer();
    int updateBestPlayer(Player *player);
    Player* getBestPlayer()const;
    AVL<int, Player*>* getAvlTeamPlayersById();
    AVL<PlayerStats, Player*>* getAvlTeamPlayersByGoals();

private:
    AVL<int, Player*> teamPlayersById;
    AVL<PlayerStats, Player*> teamPlayersByGoals;
    Player* m_bestTeamPlayer;

    int m_team_id;
    int m_numOfPlayers;
    int m_points;
    int m_total_goal;
    int m_total_cards;
    int m_game_played;

};
bool operator>(const Team& team1, const Team& team2);