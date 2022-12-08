//
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
//
// Recommended TAB size to view this file: 8.
//
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
//

#include "worldcup23a1.h"
#include <string>
#include <iostream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void query_get_all_players(string cmd, world_cup_t *obj, int teamID);

int main()
{
    cin >> std::boolalpha;

    int d1, d2, d3, d4, d5;
    bool b1;

    // Init
	world_cup_t *obj = new world_cup_t();

    // Execute all commands in file
	string op;
	while (cin >> op)
    {
        if (!op.compare("add_team")) {
            cin >> d1 >> d2;
            print(op, obj->add_team(d1, d2));
        } else if (!op.compare("remove_team")) {
            cin >> d1;
            print(op, obj->remove_team(d1));
        } else if (!op.compare("add_player")) {
            cin >> d1 >> d2 >> d3 >> d4 >> d5 >> b1;
            print(op, obj->add_player(d1, d2, d3, d4, d5, b1));
        } else if (!op.compare("remove_player")) {
            cin >> d1;
            print(op, obj->remove_player(d1));
        } else if (!op.compare("update_player_stats")) {
            cin >> d1 >> d2 >> d3 >> d4;
            print(op, obj->update_player_stats(d1, d2, d3, d4));
        } else if (!op.compare("play_match")) {
            cin >> d1 >> d2;
            print(op, obj->play_match(d1, d2));
        } else if (!op.compare("get_num_played_games")) {
            cin >> d1;
            print(op, obj->get_num_played_games(d1));
        } else if (!op.compare("get_team_points")) {
            cin >> d1;
            print(op, obj->get_team_points(d1));
        } else if (!op.compare("unite_teams")) {
            cin >> d1 >> d2 >> d3;
            print(op, obj->unite_teams(d1, d2, d3));
        } else if (!op.compare("get_top_scorer")) {
            cin >> d1;
            print(op, obj->get_top_scorer(d1));
        } else if (!op.compare("get_all_players_count")) {
            cin >> d1;
            print(op, obj->get_all_players_count(d1));
        } else if (!op.compare("get_all_players")) {
            cin >> d1;
            query_get_all_players(op, obj, d1);
        } else if (!op.compare("get_closest_player")) {
            cin >> d1 >> d2;
            print(op, obj->get_closest_player(d1, d2));
        } else if (!op.compare("knockout_winner")) {
            cin >> d1 >> d2;
            print(op, obj->knockout_winner(d1, d2));
        } else {
            cout << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail()){
            cout << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit
	delete obj;
	return 0;
}

// Helpers
static const char *StatusTypeStr[] =
{
   	"SUCCESS",
	"ALLOCATION_ERROR",
	"INVALID_INPUT",
	"FAILURE"
};

void print(string cmd, StatusType res)
{
	cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
	    cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
	    cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_players(string cmd, world_cup_t *obj, int teamID)
{
	output_t<int> count = obj->get_all_players_count(teamID);
    // Allocate if okay
    int *out_mem = nullptr;
	if (count.status() == StatusType::SUCCESS && (count.ans() > 0)) {
        out_mem = new int[count.ans()];
        for (int i = 0; i < count.ans(); ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_players(teamID, out_mem);
    print(cmd, status);
    if (status == StatusType::SUCCESS) {
	    for (int i = 0; i < count.ans(); ++i)
        {
		    cout << out_mem[i] << endl;
	    }
    }
    delete[] out_mem;
}
//#include "worldcup23a1.h"
//#include "assert.h"
//#include "wet1util.h"
//int main(){
//    try{
//        world_cup_t worldCup;
//        StatusType sResult;
//
//        sResult = worldCup.add_team(10, 1);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_team(2, 0);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_team(3, 4);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_team(9, 1);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_team(4, 1);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_team(8, 3);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_team(6, 3);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_team(7, 2);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_team(1, 3);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_team(5, 3);
//        assert(sResult == StatusType::SUCCESS);
//
//
//        sResult = worldCup.add_player(1, 5, 3, 3, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(2, 6, 2, 4, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(3, 6, 3, 2, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(4, 6, 4, 2, 2, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(5, 4, 1, 0, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(6, 9, 3, 1, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(7, 1, 3, 1, 3, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(8, 8, 2, 1, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(9, 8, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(10, 8, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(11, 10, 4, 3, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(12, 10, 2, 4, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(13, 10, 0, 0, 0, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(14, 8, 2, 1, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(15, 6, 0, 2, 3, false);
//        assert(sResult == StatusType::INVALID_INPUT);
//        sResult = worldCup.add_player(15, 6, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(16, 2, 4, 2, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(17, 7, 0, 0, 0, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(18, 3, 1, 1, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(19, 2, 3, 2, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(20, 2, 4, 4, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(21, 5, 1, 3, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(22, 7, 4, 0, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(23, 6, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(24, 2, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(25, 9, 2, 1, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(26, 9, 4, 0, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(27, 5, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(28, 9, 1, 2, 1, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(29, 7, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(30, 7, 3, 3, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(31, 7, 2, 2, 4, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(32, 7, 4, 1, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(33, 6, 2, 2, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(34, 2, 4, 3, 4, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(35, 8, 3, 3, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(36, 9, 3, 0, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(37, 1, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(38, 3, 4, 4, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(39, 5, 2, 1, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(40, 10, 4, 4, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(41, 10, 1, 1, 4, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(42, 6, 3, 1, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(43, 7, 1, 0, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(44, 1, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(45, 1, 4, 3, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(46, 7, 1, 1, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(47, 9, 1, 2, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(48, 7, 1, 0, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(49, 4, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(50, 3, 0, 0, 0, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(51, 2, 3, 4, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(52, 2, 2, 4, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(53, 5, 4, 4, 2, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(54, 5, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(55, 8, 3, 2, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(56, 7, 4, 4, 2, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(57, 10, 2, 1, 1, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(58, 3, 4, 4, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(59, 8, 2, 2, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(60, 8, 2, 3, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(61, 2, 1, 3, 2, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(62, 3, 2, 1, 3, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(63, 8, 2, 4, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(64, 1, 2, 2, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(65, 7, 1, 2, 0, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(66, 2, 1, 1, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(67, 2, 2, 4, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(68, 4, 4, 1, 4, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(69, 6, 3, 0, 0, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(70, 7, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(71, 8, 3, 2, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(72, 6, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(73, 7, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(74, 10, 2, 0, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(75, 8, 3, 2, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(76, 1, 2, 1, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(77, 7, 3, 0, 2, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(78, 1, 2, 2, 4, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(79, 10, 4, 0, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(80, 5, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(81, 2, 1, 0, 3, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(82, 9, 4, 0, 0, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(83, 7, 10, 15, 0, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(83, 7, 10, 15, 0, true);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.add_player(84, 10, 3, 0, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(85, 7, 4, 3, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(86, 6, 4, 2, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(87, 3, 4, 0, 4, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(88, 10, 4, 1, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(89, 6, 2, 3, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(90, 9, 2, 10, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(91, 4, 0, 0, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(92, 3, 1, 0, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(93, 7, 1, 1, 4, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(94, 6, 4, 3, 3, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(95, 4, 1, 3, 4, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(96, 4, 3, 4, 0, false);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(97, 4, 2, 3, 4, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(98, 3, 0, 0, 0, true);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.add_player(99, 5, 3, 0, 1, false);
//        assert(sResult == StatusType::SUCCESS);
//
//        assert(worldCup.get_top_scorer(-1).ans() == 83);
//        assert(worldCup.get_top_scorer(7).ans() == 83);
//        worldCup.update_player_stats(22, 5, 40, 3);
//        assert(worldCup.get_top_scorer(-1).ans() == 22);
//        assert(worldCup.get_top_scorer(7).ans() == 22);
//        assert(worldCup.get_top_scorer(9).ans() == 90);
//        assert(worldCup.get_closest_player(98, 3).ans() == 91);
//        assert(worldCup.get_closest_player(49, 4).ans() == 50);
//        worldCup.unite_teams(1, 9, 19);
//        sResult = worldCup.remove_team(1);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_team(9);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_team(19);
//        assert(sResult == StatusType::FAILURE);
//        int winner = worldCup.knockout_winner(2, 20).ans(); //Only 2, 6, 7 and 19 are competing
//        worldCup.play_match(2, 19);
//        worldCup.unite_teams(2, 7, 2);
//        assert(worldCup.get_num_played_games(16).ans() == 5);
//
//        // Remove team 6
//        sResult = worldCup.remove_player(2);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(3);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(4);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(15);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(23);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(33);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(42);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(69);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(72);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(86);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(89);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::FAILURE);
//        sResult = worldCup.remove_player(94);
//        assert(sResult == StatusType::SUCCESS);
//        sResult = worldCup.remove_team(6);
//        assert(sResult == StatusType::SUCCESS);
//        cout << "Test run successfully" << endl;
//        return 0;
//    } catch(...){
//        return -1;
//    }
//}
