#include "worldcup23a1.h"


void getConcurrentTeamsHelper(Node<int, Team *> *pNode, int id, int id1, team_ptr_node **pNode1, int *pInt);

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
    Team* new_team;
    try{
        new_team = new Team(teamId, points);
    } catch (const std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    AVL_team_by_id.insert(teamId, new_team);
    return StatusType::SUCCESS;
}


StatusType world_cup_t::remove_team(int teamId){
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (!AVL_team_by_id.find(teamId)||AVL_team_by_id.find(teamId)->data->getNumOfPlayer()>0){
        return StatusType::FAILURE;
    }
    Node<int, Team *> *to_delete = AVL_team_by_id.find(teamId);
    if (to_delete){
        if (to_delete->data->isValid()){
            AVL_team_by_id.remove(teamId);
        }
        AVL_team_by_id.remove(teamId);
        return  StatusType::SUCCESS;
    }
    return StatusType::FAILURE;
}


StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper){
    if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 || ((gamesPlayed == 0) && (cards > 0 || goals > 0))){
        return StatusType::INVALID_INPUT;
    }
    if (!AVL_team_by_id.root||!AVL_team_by_id.find(teamId) || AVL_all_players_by_id.find(playerId)){
        return StatusType::FAILURE;
    }
    Player *player_to_add;
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
    player_to_add->getTeam()->updateBestTeamPlayer();
    updateBestAllPlayer();

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
    Player* previousInRank = player_to_remove->getPreviousInRank();
    Player* nextInRank = player_to_remove->getNextInRank();
    AVL_all_players_by_goals.remove(player_to_remove->getPlayerStats());
    if(previousInRank) {
        previousInRank->setNextInRank(nextInRank);
    }
    if(nextInRank) {
        nextInRank->setPreviousInRank(previousInRank);
    }
    AVL_all_players_by_id.remove(playerId);
    if (!player_to_remove->getTeam()->isValid()){
        AVL_valid_team.remove(player_to_remove->getTeam()->getTeamId());
    }
    player_to_remove->getTeam()->removePlayer(player_to_remove);
    player_to_remove->getTeam()->updateBestTeamPlayer();
    updateBestAllPlayer();
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
    playerToUpdate->getTeam()->updateBestTeamPlayer();
    updateBestAllPlayer();
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
    return AVL_team_by_id.find(teamId)->data->getPoints();
}


StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId){
    if (teamId1 <= 0||teamId2 <= 0|| teamId1==teamId2||newTeamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<int, Team*>* nodeTeam1= AVL_team_by_id.find(teamId1);
    Node<int, Team*>* nodeTeam2= AVL_team_by_id.find(teamId2);
    if (nodeTeam1== nullptr||nodeTeam2== nullptr||(AVL_team_by_id.find(newTeamId) != nodeTeam1 && AVL_team_by_id.find(newTeamId) != nodeTeam2)){
        return StatusType::FAILURE;
    }

    Team* team1= AVL_team_by_id.find(teamId1)->data;
    Team* team2= AVL_team_by_id.find(teamId2)->data;

    Player** arr_player_team1_byId= new Player*[team1->getNumOfPlayer()];
    Player** arr_player_team1_byGoals=new Player*[team1->getNumOfPlayer()];
    Player** arr_player_team2_byId= new Player*[team2->getNumOfPlayer()];
    Player** arr_player_team2_byGoals=new Player*[team2->getNumOfPlayer()];

    team1->getAvlTeamPlayersById()->AVL_to_array_inorder(&arr_player_team1_byId);//create an array of player by Id
    team1->getAvlTeamPlayersByGoals()->AVL_to_array_inorder(&arr_player_team1_byGoals); //create an array of player by goal

    int num_of_players_team2 = team2->getNumOfPlayer();
    team2->getAvlTeamPlayersById()->AVL_to_array_inorder(&arr_player_team2_byId);
    num_of_players_team2 = team2->getNumOfPlayer();
    team2->getAvlTeamPlayersByGoals()->AVL_to_array_inorder(&arr_player_team2_byGoals);


    Player **arr_player_newTeam_byId = nullptr;
    mergeId (arr_player_team1_byId, arr_player_team2_byId, arr_player_newTeam_byId, team1->getNumOfPlayer(), team2->getNumOfPlayer());
    int arr_id_newTeam_byId[team1->getNumOfPlayer()+team2->getNumOfPlayer()];
    Player **arr_player_newTeam_byGoals = nullptr;
    mergeGoal(arr_player_team1_byGoals,arr_player_team2_byGoals,arr_player_newTeam_byGoals,team1->getNumOfPlayer(), team2->getNumOfPlayer());

    PlayerStats arr_stats_newTeam_byGoals[team1->getNumOfPlayer()+team2->getNumOfPlayer()];
    for(int i = 0; i<team1->getNumOfPlayer()+team2->getNumOfPlayer(); i++){
        arr_id_newTeam_byId[i] = arr_player_newTeam_byId[i]->getId();
        arr_stats_newTeam_byGoals[i] = arr_player_newTeam_byGoals[i]->getStats();
    }

    Team* newTeam = new Team(  newTeamId,
                                team1->getPoints()+team2->getPoints(),
                                team1->getNumOfPlayer()+team2->getNumOfPlayer(),
                                team1->getTotalGoal()+team2->getTotalGoal(),
                                team1->getTotalCards() + team2->getTotalCards());


    AVL<int, Player*> AVLTeamId; // create the 2 new trees
    AVL<PlayerStats, Player*> AVLTeamGoal;

    AVLTeamId.array_to_AVL_inorder(arr_id_newTeam_byId, arr_player_newTeam_byId,  team1->getNumOfPlayer()+team2->getNumOfPlayer()); // put the arrays into trees
    AVLTeamGoal.array_to_AVL_inorder(arr_stats_newTeam_byGoals, arr_player_newTeam_byGoals,  team1->getNumOfPlayer()+team2->getNumOfPlayer());

    newTeam->putAVLid(AVLTeamId); //put the trees into the team
    newTeam->putAVLGoal(AVLTeamGoal);

    if (!AVL_valid_team.find(newTeam->getTeamId()) && AVL_team_by_id.find(newTeam->isValid())){
            AVL_valid_team.insert(newTeam->getTeamId(), newTeam);
        }

    AVL_team_by_id.insert(newTeamId, newTeam);
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
    if (!AVL_team_by_id.find(teamId)){
        return StatusType::FAILURE;
    }
    Team *team = AVL_team_by_id.find(teamId)->data;

    return team->getNumOfPlayer();
}


StatusType world_cup_t::get_all_players(int teamId, int *const output){
    if (teamId == 0 || output == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if (teamId < 0){
        Player *actualPlayer = best_player_all;
        for (int i = num_of_players-1; i >= 0; i--){
            output[i] = actualPlayer->getId();
            actualPlayer = actualPlayer->getPreviousInRank();
        }
        return StatusType::SUCCESS;
    }
    if (teamId > 0){

        if (!AVL_team_by_id.find(teamId)){
            return StatusType::FAILURE;
        }
        Team *team = AVL_team_by_id.find(teamId)->data;
        Player **playersArr = new Player* [team->getNumOfPlayer()];
        AVL<PlayerStats, Player *> *playersByGoals = team->getAvlTeamPlayersByGoals();
        playersByGoals->AVL_to_array_inorder(&playersArr);
        for (int i = 0; i < team->getNumOfPlayer(); i++){
            output[i] = playersArr[i]->getId();
        }
        delete[] playersArr;
        return StatusType::SUCCESS;
    }
    return StatusType::FAILURE;
}


output_t<int> world_cup_t::get_closest_player(int playerId, int teamId){
	return AVL_team_by_id.find(teamId)->data->getAvlTeamPlayersById()->find(playerId)->data->getClosest();
}


int getConcurrentTeams(AVL<int, Team*>* AVL_valid_team, int minTeamId, int maxTeamId, team_ptr_node* first_node){
    int nuOfTeams = 0;
    team_ptr_node** actualNodeInLinkedList = &first_node;
    getConcurrentTeamsHelper(AVL_valid_team->root, minTeamId, maxTeamId, actualNodeInLinkedList, &nuOfTeams);
    return nuOfTeams;
    
}


void getConcurrentTeamsHelper(Node<int, Team *> *actualNode, int minTeamId,
                                     int maxTeamId, team_ptr_node **actualNodeInLinkedList, int *numOfTeams){
    if(!actualNode){
        return;
    }
    if(!actualNode->right || actualNode->right->key > minTeamId){
        getConcurrentTeamsHelper(actualNode->right, minTeamId, maxTeamId, actualNodeInLinkedList, numOfTeams);
    }
    if (actualNode->key < maxTeamId && actualNode->key > minTeamId){
        team_ptr_node* newNode = new team_ptr_node();
        newNode->next_node = nullptr;
        newNode->teamPtr = actualNode->data;
        newNode-> score =  actualNode->data->getPoints()+actualNode->data->getTotalGoal()
                                                            -actualNode->data->getTotalCards();
        (*actualNodeInLinkedList)->next_node = newNode;
        actualNodeInLinkedList = &((*actualNodeInLinkedList)->next_node);
        *numOfTeams++;
    }
    if(!actualNode->left || actualNode->left->key < maxTeamId){
        getConcurrentTeamsHelper(actualNode->right, minTeamId, maxTeamId, actualNodeInLinkedList, numOfTeams);
    }
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId){
    team_ptr_node* first_node = new team_ptr_node();
    first_node->next_node = nullptr;
    first_node->teamPtr = nullptr;
    first_node->score = 0;
    int numOfConcurentTeams = getConcurrentTeams(&AVL_valid_team, minTeamId, maxTeamId, first_node);
    team_ptr_node* currentTeam = nullptr;
    while(numOfConcurentTeams > 1){
        currentTeam = first_node;
        while (currentTeam->next_node && currentTeam->next_node->next_node){
            if(currentTeam->next_node->score>currentTeam->next_node->next_node->score){
                currentTeam->next_node->score+=currentTeam->next_node->next_node->score;
                team_ptr_node* nodeTodelete = currentTeam->next_node->next_node;
                currentTeam->next_node->next_node = nodeTodelete->next_node;
                delete nodeTodelete;
            }
            else{
                currentTeam->next_node->next_node->score+=currentTeam->next_node->score;
                team_ptr_node* nodeTodelete = currentTeam->next_node;
                currentTeam->next_node = nodeTodelete->next_node;
                delete nodeTodelete;
            }currentTeam = currentTeam->next_node->next_node;
            numOfConcurentTeams--;
        }
        int winnerId = first_node ->next_node->teamPtr->getTeamId();
        delete first_node->next_node;
        delete first_node;
        return StatusType::SUCCESS;
    }
    return StatusType::FAILURE;

}


Player **world_cup_t::mergeGoal (Player* arrayTeam1[], Player* arrayTeam2[],Player* arrOfPlayerOf2Teams[], int sizeTeam1, int sizeTeam2) { // on lui donne deux tableaux de player

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


Player** world_cup_t::mergeId(Player* arrayTeam1[], Player* arrayTeam2[],Player* arrOfPlayerOf2Teams[], int sizeTeam1, int sizeTeam2){ // on lui donne deux tableaux de player

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

void world_cup_t::updateBestAllPlayer(){
    best_player_all = AVL_all_players_by_goals.dataOfTheMax();
}
