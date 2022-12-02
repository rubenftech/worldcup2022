#include "worldcup23a1.h"

world_cup_t::world_cup_t(){
    AVL_team_by_id = AVL<int, Team*>();
    AVL_all_players_by_id = AVL<int, Player*>();
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
    AVL<int, Team*>::Node* to_delete = AVL_team_by_id.find(teamId);
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
        Player* new_player = new Player(playerId,teamId,gamesPlayed,goals,cards,goalKeeper);
    } catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    AVL_all_players_by_id.insert(player_to_add->getId(), player_to_add);
    AVL_all_players_by_goals.insert(player_to_add->getPlayerStats(), player_to_add);
    AVL_team_by_id.find(teamId).data->addPlayer(player_to_add);
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
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
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

