#include"Team.h"

/*
    AVL<int, Player *> teamPlayersById;
    AVL<PlayerStats, Player *> teamPlayersByGoals;
    int numOfPlayers;
    int points;
    Player *bestTeamPlayer;

*/
Team::Team(int team_id, int team_points):teamPlayersById(*new AVL<int, Player*>),
                                        teamPlayersByGoals(*new AVL<PlayerStats, Player*>),
                                        m_numOfPlayers(0),
                                        m_points(team_points),
                                        m_bestTeamPlayer(nullptr){};



Team::~Team(){
    delete &teamPlayersByGoals;
    delete &teamPlayersById;
}


void Team::addPlayer(Player *player){
    if(player == nullptr){
        return;
    }
    teamPlayersById.insert(player->getId(), player);
    teamPlayersByGoals.insert(player->getPlayerStats(), player);
    m_numOfPlayers++;
    if(m_bestTeamPlayer==nullptr){
        m_bestTeamPlayer = player;
    }
    else if(player->getPlayerStats() > m_bestTeamPlayer->getPlayerStats()){
        m_bestTeamPlayer = player;
    }
}

void Team::removePlayer(Player *player){
    teamPlayersById.remove(player->getId());
    teamPlayersByGoals.remove(player->getPlayerStats());
    m_numOfPlayers--;
    updateBestPlayer();
}

int Team::getNumOfPlayer() const{
    return m_numOfPlayers;
}

void Team::addPoints(int pointsToAdd){
    m_points+=pointsToAdd;
}

int Team::getPoints() const{
    return m_points;
}

int Team::updateBestPlayer(){
    m_bestTeamPlayer = teamPlayersByGoals.dataOfTheMax();
}

int Team::updateBestPlayer(Player *player){
    m_bestTeamPlayer = player;
}
