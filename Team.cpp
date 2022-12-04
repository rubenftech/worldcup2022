#include"Team.h"


Team::Team(int team_id, int team_points, int numOfPlayers, int goal, int cards):teamPlayersById(*new AVL<int, Player*>),
                                        teamPlayersByGoals(*new AVL<PlayerStats, Player*>),
                                        m_team_id(team_id),
                                        m_points(team_points),
                                        m_numOfPlayers(numOfPlayers),
                                        m_total_goal(goal),
                                        m_total_cards(cards),
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

void Team::addPlayedGame(){
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
    if (team1.getPoints()+team1.getTotalGoal()-team1.getTotalCards()>
                team2.getPoints()+team2.getTotalGoal()-team2.getTotalCards()){
        return true;
    }
    return false;
}

int Team::get_game_played() const {
    return m_game_played;
}

int Team::getTotalCards() const {
    return m_total_cards;
}

int Team::getTotalGoal() const {
    return m_total_goal;
}
Player* Team::getBestPlayer() const{
    return m_bestTeamPlayer;
}

AVL<int, Player*>* Team::getAvlTeamPlayersById(){

    return (&teamPlayersById);
}
AVL<PlayerStats, Player*>* Team::getAvlTeamPlayersByGoals(){
    return (&teamPlayersByGoals);
}

void Team::putAVLid(AVL<int,Player*> tree ) {
    teamPlayersById=tree;
}

void Team::putAVLGoal(AVL<PlayerStats, Player *> tree) {
    teamPlayersByGoals=tree;
}
