#include "worldcup23a1.h"


world_cup_t::world_cup_t(){
    AVL_team_by_id = AVL<int, Team *>();
    AVL_all_players_by_id = AVL<int, Player *>();
    AVL_all_players_by_goals = AVL<PlayerStats, Player *>();
    AVL_valid_team = AVL<int , Team*>();
}


world_cup_t::~world_cup_t(){
    AVL_team_by_id.clearTree(); // il faut supprimer les ARBRES DE JOUEURS
    AVL_all_players_by_goals.clearTree();
    AVL_valid_team.clearTree();
    AVL_all_players_by_id.clearDataAndTree();
}


StatusType world_cup_t::add_team(int teamId, int points){
    if (teamId <= 0 || points < 0){
        return StatusType::INVALID_INPUT;
    }
    if (AVL_team_by_id.find(teamId)){
        return StatusType::FAILURE;
    }
    Team *new_team = nullptr;
    try{
        new_team = new Team(teamId, points);
    }
    catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
    AVL_team_by_id.insert(teamId, new_team);
    return StatusType::SUCCESS;
}


StatusType world_cup_t::remove_team(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<int, Team *> *to_delete = AVL_team_by_id.find(teamId);
    if (to_delete){
        if (to_delete->data->isValid()){
            AVL_team_by_id.remove(teamId);
        }
        AVL_team_by_id.remove(teamId);
    }
    return StatusType::FAILURE;
}


StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper){
    if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 || ((gamesPlayed = 0) && (cards > 0 || goals > 0))){
        return StatusType::INVALID_INPUT;
    }
    if (!AVL_team_by_id.find(teamId) || AVL_team_by_id.find(playerId)){
        return StatusType::FAILURE;
    }
    Player *player_to_add = nullptr;
    try{
        player_to_add = new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
    }
    catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
    AVL_all_players_by_id.insert(player_to_add->getId(), player_to_add);
    AVL_all_players_by_goals.insert(player_to_add->getPlayerStats(), player_to_add);
    (AVL_team_by_id.find(teamId))->data->addPlayer(player_to_add);
    if  (AVL_team_by_id.find(teamId)->data->isValid()){
        AVL_valid_team.insert(teamId,AVL_team_by_id.find(teamId)->data);
    }
    player_to_add->updatePreviousInRank(AVL_all_players_by_goals);
    player_to_add->updateNextInRank(AVL_all_players_by_goals);
    num_of_players++;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId){
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (!AVL_all_players_by_id.find(playerId)){
        return StatusType::FAILURE;
    }
    Player* player_to_remove= AVL_all_players_by_id.find(playerId)->data;
    AVL_all_players_by_goals.remove(player_to_remove->getPlayerStats());
    player_to_remove->getPreviousInRank()->updateNextInRank(AVL_all_players_by_goals);
    player_to_remove->getNextInRank()->updateNextInRank(AVL_all_players_by_goals);
    AVL_all_players_by_id.remove(playerId);
    if (!player_to_remove->getTeam()->isValid()){
        AVL_valid_team.remove(player_to_remove->getTeam()->getTeamId());
    }
    player_to_remove->getTeam()->removePlayer(player_to_remove);
    return StatusType::SUCCESS;
}


StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived){

    if (playerId<=0||gamesPlayed<0||scoredGoals<0||cardsReceived<0){
        return StatusType::INVALID_INPUT;
    }
    if (!AVL_all_players_by_id.find(playerId)){
        return StatusType::FAILURE;
    }

    Player* playerToUpdate = AVL_all_players_by_id.find(playerId)->data;
    playerToUpdate->addGames(gamesPlayed-playerToUpdate->getTeam()->get_game_played());
    playerToUpdate->addGoals(scoredGoals-playerToUpdate->getGoals());
    playerToUpdate->getTeam()->addGoals(scoredGoals-playerToUpdate->getGoals());
    playerToUpdate->addCards(cardsReceived-playerToUpdate->getCards());
    playerToUpdate->getTeam()->addCards(scoredGoals-playerToUpdate->getCards());
    playerToUpdate->updatePreviousInRank(AVL_all_players_by_goals);
    playerToUpdate->updateNextInRank(AVL_all_players_by_goals);
    playerToUpdate->getTeam()->updateBestPlayer();
	return StatusType::SUCCESS;
}


StatusType world_cup_t::play_match(int teamId1, int teamId2){
    if (teamId2 <= 0 || teamId1 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    Team *team1 = AVL_team_by_id.find(teamId1)->data;
    Team *team2 = AVL_team_by_id.find(teamId2)->data;
    if (team1 == nullptr || team2 == nullptr || team1->getNumOfPlayer() < 11 || team2->getNumOfPlayer() < 11){
        return StatusType::FAILURE;
    }
    if (team1 > team2){
        team1->addPoints(3);
    }
    else if (team2 < team1){
        team2->addPoints(3);
    }
    else{
        team1->addPoints(1);
        team2->addPoints(1);
    }
    team1->addPlayedGame();
    team2->addPlayedGame();
    return StatusType::SUCCESS;
}


output_t<int> world_cup_t::get_num_played_games(int playerId){
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (AVL_all_players_by_id.find(playerId) == nullptr){
        return StatusType::FAILURE;
    }
    Player* player = AVL_all_players_by_id.find(playerId)->data;
    return player->getNumGames()+ player->getTeam()->get_game_played();
}


output_t<int> world_cup_t::get_team_points(int teamId){
    AVL_team_by_id.find(teamId)->data->getPoints();
}


StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId){
    if (teamId1 <= 0||teamId2 <= 0|| teamId1==teamId2||newTeamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Team* team1= AVL_team_by_id.find(teamId1)->data;
    Team* team2= AVL_team_by_id.find(teamId2)->data;
    if (team1== nullptr||team2== nullptr||(AVL_team_by_id.find(newTeamId)->data!= team1 && AVL_team_by_id.find(newTeamId)->data!=team2)){
        return StatusType::FAILURE;
    }

    Player** arr_player_team1_byId;
    Player** arr_player_team1_byGoals;
    Player** arr_player_team2byId;
    Player** arr_player_team2_byGoals;

    team1->getAvlTeamPlayersById()->AVL_to_array_inorder(arr_player_team1_byId,team1->getNumOfPlayer());
    team1->getAvlTeamPlayersByGoals()->AVL_to_array_inorder(arr_player_team1_byGoals,team1->getNumOfPlayer());
    team2->getAvlTeamPlayersById()->AVL_to_array_inorder(arr_player_team2byId,team2->getNumOfPlayer());
    team2->getAvlTeamPlayersByGoals()->AVL_to_array_inorder(arr_player_team2_byGoals,team2->getNumOfPlayer());


    Player** arr_player_newTeam_byId = mergeId (arr_player_team1_byId,arr_player_team2byId, team1->getNumOfPlayer(), team2->getNumOfPlayer());
    Player** arr_player_newTeam_byGoals = mergeGoal(arr_player_team1_byGoals,arr_player_team2_byGoals,team1->getNumOfPlayer(), team2->getNumOfPlayer());

    Team* newTeam = new Team(  newTeamId,
                                team1->getPoints()+team2->getPoints(),
                                team1->getNumOfPlayer()+team2->getNumOfPlayer(),
                                team1->getTotalGoal()+team2->getTotalGoal(),
                                team1->getTotalCards() + team2->getTotalCards());


    AVL<int, Player*> AVLTeamId; // create the 2 new trees
    AVL<PlayerStats, Player*> AVLTeamGoal;

    array_to_AVL_inorder(arr_player_newTeam_byId, AVLTeamId); // put the arrays into trees, fonction a ajuster dans AVL template ligne 175
    array_to_AVL_inorder(arr_player_newTeam_byGoals, AVLTeamGoal);

    newTeam->putAVLid(AVLTeamId); //put the trees into the team
    newTeam->putAVLGoal(AVLTeamGoal);

    if (!AVL_valid_team.find(newTeam->getTeamId()) && AVL_team_by_id.find(newTeam->isValid())){
            AVL_valid_team.insert(newTeam->getTeamId(), newTeam);
        }

    AVL_team_by_id.insert(newTeamId, newTeam);
    AVL_team_by_id.remove(teamId1);
    AVL_team_by_id.remove(teamId2);

    return StatusType::SUCCESS;
}


output_t<int> world_cup_t::get_top_scorer(int teamId){
    if (teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if (teamId < 0){
        return best_player_all->getId();
    }
    Team *team = AVL_team_by_id.find(teamId)->data;
    if (!team || !team->getBestPlayer()){
        return StatusType::FAILURE;
    }
    return team->getBestPlayer()->getId();
}


output_t<int> world_cup_t::get_all_players_count(int teamId){
    if (teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if (teamId < 0){
        return num_of_players;
    }
    Team *team = AVL_team_by_id.find(teamId)->data;
    if (!team){
        return StatusType::FAILURE;
    }
    return team->getNumOfPlayer();
}


StatusType world_cup_t::get_all_players(int teamId, int *const output){
    if (teamId == 0 || output == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if (teamId < 0){
        Player *actualPlayer = best_player_all;
        for (int i = num_of_players; i > 0; i--){
            output[i] = actualPlayer->getId();
            actualPlayer = actualPlayer->getPreviousInRank();
        }
    }
    if (teamId > 0){
        Team *team = AVL_team_by_id.find(teamId)->data;
        if (team == nullptr){
            return StatusType::FAILURE;
        }
        Player **playersArr = new Player *[team->getNumOfPlayer()];
        AVL<PlayerStats, Player *> *playersByGoals = team->getAvlTeamPlayersByGoals();
        playersByGoals->AVL_to_array_inorder(playersArr, 0);
        for (int i = 0; i < team->getNumOfPlayer(); i++){
            output[i] = playersArr[i]->getId();
        }
        delete[] playersArr;
        return StatusType::SUCCESS;
    }
}


output_t<int> world_cup_t::get_closest_player(int playerId, int teamId){
	return AVL_team_by_id.find(teamId)->data->getAvlTeamPlayersById()->find(playerId)->data->getClosest() ;
}


output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId){

    if (minTeamId<0|| maxTeamId<0||maxTeamId<minTeamId){
        return StatusType::INVALID_INPUT;
    }
    Node<int, Team*>* nodeFirstTeam = nullptr;
    while (nodeFirstTeam == nullptr && minTeamId < AVL_valid_team.dataOfTheMax()->getTeamId()){
        nodeFirstTeam= AVL_valid_team.find(minTeamId);
        minTeamId++;
    }
    if (nodeFirstTeam = nullptr){
        return StatusType::FAILURE;
    }
    Team* firstTeam = AVL_valid_team.find(minTeamId)->data;
    Node<int, Team*>* nodeLastTeam = nullptr;
    while (maxTeamId>=minTeamId &&  AVL_valid_team.find(maxTeamId)==0){
        AVL_valid_team.find(maxTeamId);
        maxTeamId--;
    }
    Team* lastTeam = AVL_valid_team.find(maxTeamId)->data;



    /*cloner les r equipes dans un arbres
     * inorder play match
     * unit team if equipe perd
     * retourne lequipe qui gagne
     *
     *
     * */
	return ;
}


Player **world_cup_t::mergeGoal (Player* arrayTeam1[], Player* arrayTeam2[], int sizeTeam1, int sizeTeam2) { // on lui donne deux tableaux de player

    Player *arrOfPlayerOf2Teams[sizeTeam1 + sizeTeam2];
    int i = 0, j = 0, k = 0;
    while (i < sizeTeam1 && j < sizeTeam2) {
        if (arrayTeam1[i]->getPlayerStats() > arrayTeam2[j]->getPlayerStats()) {
            arrOfPlayerOf2Teams[k] = arrayTeam1[i];
            i++;
        } else {
            arrOfPlayerOf2Teams[k] = arrayTeam2[j];
            j++;
        }
    }
    if (i == sizeTeam1) {
        while (j < sizeTeam2) {
            arrOfPlayerOf2Teams[k] = arrayTeam2[j];
            j++;
        }
    } else {
        while (i < sizeTeam1) {
            arrOfPlayerOf2Teams[k] = arrayTeam1[i];
            i++;
        }
    }
    return arrOfPlayerOf2Teams;
}


Player** world_cup_t::mergeId(Player* arrayTeam1[], Player* arrayTeam2[], int sizeTeam1, int sizeTeam2){ // on lui donne deux tableaux de player

    Player* arrOfPlayerOf2Teams [sizeTeam1+sizeTeam2];
    int i=0, j=0,k=0;
    while (i<sizeTeam1 && j<sizeTeam2){
        if (arrayTeam1[i]->getId() > arrayTeam2[j]->getId()) {
            arrOfPlayerOf2Teams[k] = arrayTeam1[i];
            i++;
        }
            else{
                arrOfPlayerOf2Teams[k]= arrayTeam2[j];
                j++;
            }
        }
    if (i==sizeTeam1){
        while (j<sizeTeam2){
            arrOfPlayerOf2Teams[k] = arrayTeam2[j];
            j++;
        }
    }
        else{
            while (i<sizeTeam1){
                arrOfPlayerOf2Teams[k] = arrayTeam1[i];
                i++;
        }
    }
    return arrOfPlayerOf2Teams;
}


