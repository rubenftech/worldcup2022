#include"Player.h"


PlayerStats::PlayerStats(int goals, int cards, int id): m_goals(goals),
                                                        m_cards(cards),
                                                        m_playerId(id){}

PlayerStats PlayerStats::operator-(const PlayerStats& playerStats)const{
    return PlayerStats(m_goals-playerStats.m_goals, m_cards-playerStats.m_cards, m_playerId-playerStats.m_playerId);
}
bool operator>(const PlayerStats& player1, const PlayerStats& player2){
    if(player1.m_goals > player2.m_goals){
        return true;
    }
    if(player1.m_goals < player2.m_goals){
        return false;
    }
        if(player1.m_cards > player2.m_cards){
        return true;
    }
        if(player1.m_cards < player2.m_cards){
        return false;
    }
    return(player1.m_playerId > player2.m_playerId);
}

bool operator<(const PlayerStats& player1, const PlayerStats& player2){
    return !(player1 > player2);
}

bool operator==(const PlayerStats& player1, const PlayerStats& player2){
    return(player1.m_playerId == player2.m_playerId);
}

bool operator!=(const PlayerStats& player1, const PlayerStats& player2){
    return !(player1==player2);
}

Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper):m_playerId(playerId),
                                                                                    m_gamePlayed(gamesPlayed),
                                                                                    m_goals(goals),
                                                                                    m_cards(cards),
                                                                                    m_goalKeeper(goalKeeper),
                                                                                    m_team_ptr(nullptr),
                                                                                    m_previousInRank(nullptr),
                                                                                    m_nextInRank(nullptr){}

int Player::getId() const{
    return m_playerId;
}

void Player::addGames(int newGames){
    if (newGames > 0){
    m_gamePlayed+= newGames;
    }
}
int Player::getNumGames() const{
    return m_gamePlayed;
}

void Player::addGoals(int newGoals){
    if (newGoals > 0){
        m_goals+= newGoals;
    }
}

int Player::getGoals() const{
    return m_goals;
}

void Player::addCards(int newCards){
    if (newCards > 0){
        m_cards+= newCards;
    }
}

int Player::getCards() const{
    return m_cards;
}

bool Player::isGoalKeeper() const{
    return m_goalKeeper;
}

void Player::updatePreviousInRank(AVL<PlayerStats, Player*> rankedTree){
    PlayerStats keyInRankedTree(m_goals, m_cards, m_playerId);
    m_previousInRank = rankedTree.getPreviousInorder(keyInRankedTree);   
}
PlayerStats Player::getStats()const{
    return PlayerStats(m_goals, m_cards, m_playerId);
}
Player* Player::getPreviousInRank() const{
    return m_previousInRank;
}

void Player::updateNextInRank(AVL<PlayerStats, Player*> rankedTree){
    PlayerStats keyInRankedTree(m_goals, m_cards, m_playerId);
    m_nextInRank = rankedTree.getNextInorder(keyInRankedTree);
}

Player* Player::getNextInRank() const{
    return m_nextInRank;
}

PlayerStats Player::getPlayerStats()const{
    return PlayerStats(m_goals, m_cards, m_playerId);
}

void Player::setTeam(Team* teamPtr) {
    m_team_ptr = teamPtr;
}


Team *Player::getTeam() {
    return m_team_ptr;
}

int Player::getClosest() {
    Player* playerNext= getNextInRank();
    Player* playerPrevious= getPreviousInRank();
    return (playerNext->getStats()-this->getStats()<this->getStats()-playerPrevious->getStats())? 
                                                    playerNext->getId() : playerPrevious->getId();
}
