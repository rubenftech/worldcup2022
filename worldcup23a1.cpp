#include "worldcup23a1.h"

world_cup_t::world_cup_t(){
    AVL_team_by_id = AVL<int, Team*>();
    AVL_all_players_by_id = AVL<int , Player*>();
    AVL_all_players_by_goals = AVL<PlayerStats, Player*>();
} // The 3 Trees are initialisized, best_player_all is NULL

world_cup_t::~world_cup_t(){
    AVL_team_by_id.clearTree(); // il faut supprimer les ARBRES DE JOUEURS
    AVL_all_players_by_goals.clearTree();
    AVL_all_players_by_id.clearDataAndTree();
}


StatusType world_cup_t::add_team(int teamId, int points){
    if (teamId<=0 || points<0){
        return StatusType::INVALID_INPUT;
    }
    if( AVL_team_by_id.find(teamId)){
       return StatusType::FAILURE;
    }
    Team* new_team = nullptr;
    try {
        new_team = new Team(teamId, points);
    } catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

    AVL_team_by_id.insert(teamId, new_team);
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId){
    if (teamId<=0){
    return StatusType::INVALID_INPUT;
    }
    Node<int, Team*>* to_delete = AVL_team_by_id.find(teamId);
    if (to_delete){
        AVL_team_by_id.remove(teamId);
    }
	return StatusType::FAILURE;
}


StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper){
    if(playerId<=0||teamId<=0||gamesPlayed<0||goals<0||cards<0||((gamesPlayed=0)&&(cards>0||goals>0))){
        return StatusType::INVALID_INPUT;
    }
    if (!AVL_team_by_id.find(teamId)||AVL_team_by_id.find(playerId)){
        return StatusType::FAILURE;
    }
    Player* player_to_add = nullptr;
    try{
        player_to_add = new Player(playerId,teamId,gamesPlayed,goals,cards,goalKeeper);
    } catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    AVL_all_players_by_id.insert(player_to_add->getId(), player_to_add);
    AVL_all_players_by_goals.insert(player_to_add->getPlayerStats(), player_to_add);
    (AVL_team_by_id.find(teamId))->data->addPlayer(player_to_add);
    player_to_add->updatePreviousInRank(AVL_all_players_by_goals);
    player_to_add->updateNextInRank(AVL_all_players_by_goals);
	return StatusType::SUCCESS;
}


StatusType world_cup_t::remove_player(int playerId)
{
    if(playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    if(!AVL_all_players_by_id.find(playerId)){
        return StatusType::FAILURE;
    }
    //AVL_all_players_by_id.find(playerId)->data->
    // dont forget to update the closest players
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2){
    if (teamId2<=0||teamId1<=0||teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }
    Team* team1 = AVL_team_by_id.find(teamId1)->data;
    Team* team2 = AVL_team_by_id.find(teamId2)->data;
    if (team1== nullptr||team2 == nullptr||team1->getNumOfPlayer()<11||team2->getNumOfPlayer()<11){
        return StatusType::FAILURE;
    }
    if (team1>team2){
        team1->addPoints(3);
    }
    else if  (team2<team1) {
            team2->addPoints(3);
        }
    else{
        team1->addPoints(1);
        team2->addPoints(1);
    }
    team1->addPlayedgame();
    team2->addPlayedgame();
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId){
    if (playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    Player* player= AVL_all_players_by_id.find(playerId)->data;
    if (player = nullptr){
        return StatusType::FAILURE;
    }
    return player->getNumGames();
}

output_t<int> world_cup_t::get_team_points(int teamId){
    
    AVL_team_by_id.find(teamId)->data->getPoints();
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId == 0){
        return StatusType::INVALID_INPUT;
    }
	if(teamId < 0){
        return best_player_all->getId();
    }
    Team *team = AVL_team_by_id.find(teamId)->data;
    if(!team || !team->getBestPlayer()){
        return StatusType::FAILURE;
    }
    return team->getBestPlayer()->getId();
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if(teamId == 0){
        return StatusType::INVALID_INPUT;
    }
	if(teamId < 0){
        return get_num_played_games();
    }
    Team *team = AVL_team_by_id.find(teamId)->data;
    if(!team){
        return StatusType::FAILURE;
    }
    return team->get_game_played();
}


StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

