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
    player->addGames(-m_game_played);
    player->setTeam(this);
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

void Team::addPlayedgame(){
    m_game_played++;
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

bool operator>(const Team &team1, const Team &team2) {
    if (team1.getPoints()+team1.getTotalGoal()-team1.getTotalcards()>
                team2.getPoints()+team2.getTotalGoal()-team2.getTotalcards()){
        return true;
    }
    return false;
}

int Team::get_game_played() const {
    return m_game_played;
}

int Team::getTotalcards() const {
    return m_total_cards;
}

int Team::getTotalGoal() const {
    return m_total_goal;
}
Player* Team::getBestPlayer() const{
    return m_bestTeamPlayer;
}