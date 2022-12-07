// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef WORLDCUP23A1_H_
#define WORLDCUP23A1_H_

#include "wet1util.h"
#include "AVL_TREE_TEMPLATE.h"
#include "Team.h"

struct team_ptr_node{
	Team* teamPtr;
	team_ptr_node* next_node;
	int score;
};

class world_cup_t {
private:
    AVL<int , Team*> AVL_team_by_id;     // arbre de toutes les equipes key = id
    AVL<int , Player*> AVL_all_players_by_id;     // arbre de tous les joueurs key = id
    AVL<PlayerStats, Player*> AVL_all_players_by_goals; // arbre de tous les joueurs key = goal
    AVL<int , Team*> AVL_valid_team;
    Player* best_player_all = nullptr; // meilleur de tous les joueurs
	int num_of_players=0;
	int num_of_valid_teams=0;

public:
    static Player** mergeId(Player**, Player**,Player** ,int, int);
    static Player **mergeGoal(Player **arrayTeam1, Player **arrayTeam2,Player** , int player, int player1);
    void updateBestAllPlayer();
    // <DO-NOT-MODIFY> {
	
	world_cup_t();
	virtual ~world_cup_t();
	
	StatusType add_team(int teamId, int points);
	
	StatusType remove_team(int teamId);
	
	StatusType add_player(int playerId, int teamId, int gamesPlayed,
	                      int goals, int cards, bool goalKeeper);
	
	StatusType remove_player(int playerId);
	
	StatusType update_player_stats(int playerId, int gamesPlayed,
	                                int scoredGoals, int cardsReceived);
	
	StatusType play_match(int teamId1, int teamId2);
	
	output_t<int> get_num_played_games(int playerId);
	
	output_t<int> get_team_points(int teamId);
	
	StatusType unite_teams(int teamId1, int teamId2, int newTeamId);
	
	output_t<int> get_top_scorer(int teamId);
	
	output_t<int> get_all_players_count(int teamId);
	
	StatusType get_all_players(int teamId, int *const output);
	
	output_t<int> get_closest_player(int playerId, int teamId);
	
	output_t<int> knockout_winner(int minTeamId, int maxTeamId);
	
	// } </DO-NOT-MODIFY>
};

#endif // WORLDCUP23A1_H_
