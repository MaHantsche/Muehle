// Muehle.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include <iostream>
#include <array>
#include <ctime>
#include <random>

typedef unsigned char uc;

const std::array<std::array<uc, 4>, 24> board = { {
	{1,7,100,100}, //0
	{0,2,9,100},
	{1,3,100,100},
	{2,4,11,100},
	{3,5,100,100}, //4
	{4,6,13,100},
	{5,7,100,100},
	{0,6,15,100},
	{9,15,100,100}, 
	{1,8,10,17}, //9
	{9,11,100,100},
	{3,10,12,19},
	{11,13,100,100},
	{5,12,14,21},
	{13,15,100,100}, //14
	{7,8,14,23},
	{17,23,100,100},
	{9,16,18,100}, 
	{17,19,100,100},
	{11,18,20,100}, //19
	{19,21,100,100},
	{13,20,22,100}, 
	{21,23,100,100},
	{15,16,22,100} //23
} };
const std::array<uc, 24> board_count = { 2,3,2,3,2,3,2,3,2,4,2,4,2,4,2,4,2,3,2,3,2,3,2,3 };
const std::array<std::array<std::array<uc, 2>, 2>, 24> row = { {
	{{{1,2},{7,6}}},
	{{{0,2},{9,17}}},
	{{{0,1},{3,4}}},
	{{{2,4},{19,11}}},
	{{{2,3},{5,6}}},
	{{{4,6},{13,21}}},
	{{{4,5},{7,0}}},
	{{{0,6},{15,23}}},
	{{{9,10},{14,15}}},
	{{{8,10},{1,17}}},
	{{{8,9},{11,12}}},
	{{{10,12},{3,19}}},
	{{{10,11},{13,14}}},
	{{{12,14},{5,21}}},
	{{{12,13},{15,8}}},
	{{{8,14},{7,23}}},
	{{{17,18},{22,23}}},
	{{{16,18},{9,1}}},
	{{{16,17},{19,20}}},
	{{{18,20},{11,3}}},
	{{{18,19},{21,22}}},
	{{{20,22},{5,13}}},
	{{{20,21},{23,16}}},
	{{{16,22},{15,7}}}
} };

struct state {
	uc round = 0;
	uc phase = 0;
	std::array<std::array<uc, 9>, 2> player_nodes;
	std::array<uc, 2> player_nodes_count = { {0,0} };
	std::array<std::array<uc, 4>, 24> node_moves;
	std::array<uc, 24> node_moves_count = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	std::array<uc, 24> moves = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
	std::array<uc, 2> moves_count = { 23,23 };
	std::array<uc, 24> nodes = { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10 };
};


void random_move_update_state(state &s);
void show_board(state &s);
char position(uc pos);
void print_moves(state &s);

int main()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_int_distribution<>dist(0, 23);

	std::cout << dist(e2) << " " << dist(e2) << " " << dist(e2) << " " << std::endl;
	
	state s;
	state s2 = s;

	s2.round = 10;
	std::cout << int(s.round) << std::endl;

	uc i;

	//print_moves(s);

	while (s.round < 18 || s.player_nodes_count[0] > 2 || s.player_nodes_count[1] > 2) {
		print_moves(s);
		std::cout << "round: " << short(s.round) << " " << "p1 nodes: " << short(s.player_nodes_count[0]) << " p2 nodes: " << short(s.player_nodes_count[1]) << std::endl;
		random_move_update_state(s);
		std::cout << "last move: " << short(s.player_nodes[(s.round-1) % 2][s.player_nodes_count[(s.round-1) % 2]-1]) << std::endl;
		show_board(s);
		i = 0;
	}

	std::cout << sizeof(s) << std::endl;
	std::cout << sizeof(board_count) << std::endl;
    std::cout << "Hello World!\n"; 
	//std::cin >> i;
}

void print_moves(state &s) {
	std::sort(std::begin(s.moves),std::end(s.moves));
	for (int i = 0;i < 24;i++) {
		std::cout << short(s.moves[i]) <<" ";
	}
	std::cout << std::endl;
}

char position(uc pos) {
	pos = short(pos);
	if (pos == 10) {
		return ' ';
	}
	else {
		if (pos == 0) {
			return 'W';
		}
		else {
			return 'B';
		}
	}
}

void show_board(state &s) {
	std::cout << position(s.nodes[0]) << "--------" << position(s.nodes[1]) << "--------" << position(s.nodes[2]) << std::endl;
	std::cout << "|        |        |" << std::endl;
	std::cout << "|   " << position(s.nodes[8]) << "----" << position(s.nodes[9]) << "----" << position(s.nodes[10]) << "   |" << std::endl;
	std::cout << "|   |    |    |   |" << std::endl;
	std::cout << "|   |  " << position(s.nodes[16]) << "-" << position(s.nodes[17]) << "-" << position(s.nodes[18]) << "  |   |" << std::endl;
	std::cout << position(s.nodes[7]) << "---" << position(s.nodes[15]) << "--" << position(s.nodes[23]) << "   " << position(s.nodes[19]) << "--" << position(s.nodes[11]) << "---" << position(s.nodes[3]) << std::endl;
	std::cout << "|   |  " << position(s.nodes[22]) << "-" << position(s.nodes[21]) << "-" << position(s.nodes[20]) << "  |   |" << std::endl;
	std::cout << "|   |    |    |   |" << std::endl;
	std::cout << "|   " << position(s.nodes[14]) << "----" << position(s.nodes[13]) << "----" << position(s.nodes[12]) << "   |" << std::endl;
	std::cout << "|        |        |" << std::endl;
	std::cout << position(s.nodes[6]) << "--------" << position(s.nodes[5]) << "--------" << position(s.nodes[4]) << std::endl;

}


void random_move_update_state(state &s) {
	uc p;
	std::random_device rd;
	std::mt19937 e2(rd());
	if (s.phase == 0) {
		p = s.round % 2;
		if (s.round < 18) {
			std::uniform_int_distribution<>dist(0, s.moves_count[p]);
			uc r = dist(e2);
			uc move = s.moves[r];
			s.moves[r] = s.moves[s.moves_count[p]];
			s.moves_count[0]--;
			s.moves_count[1]--;
			s.nodes[move] = p;
			s.player_nodes[p][s.round / 2] = move;
			s.player_nodes_count[p]++;
			if ((s.nodes[row[move][0][0]] == p) && (s.nodes[row[move][0][1]] == p) || (s.nodes[row[move][1][0]] == p) && (s.nodes[row[move][1][1]] == p)) {
				s.phase = 1;
			}
			else {
				s.round++;
			}
		}
		else {
			if (s.round == 18) { //upate node_moves, node_moves_count, moves_count
				for (uc p = 0;p < 2;p++) {
					s.moves_count[p] = 0;
					for (uc pnc = 0;pnc < s.player_nodes_count[p];pnc++) {
						uc from_node = s.player_nodes[p][pnc];
						s.node_moves_count[from_node] = 0;
						for (uc pnnc = 0; pnnc < board_count[from_node];pnnc++) {
							uc to_node = board[from_node][pnnc];
							if (s.nodes[to_node] == 10) {
								s.node_moves[from_node][s.node_moves_count[from_node]] = to_node;
								s.node_moves_count[from_node]++;
								s.moves_count[p]++;
							}
						}
					}
				}
			}
			std::uniform_int_distribution<>dist(0, s.moves_count[p]);
			uc r = dist(e2);
			uc sum = 0;
			uc i = 0;
			do {
				sum += s.node_moves_count[s.player_nodes[p][i]] + 1;
				i++;
			} while (sum > r);
			sum -= s.node_moves_count[s.player_nodes[p][i - 1]] + 1;
			uc from_node = s.player_nodes[p][i];
			uc to_node = s.node_moves[from_node][r - sum];

			s.nodes[from_node] = 10;
			s.nodes[to_node] = p;

			s.player_nodes[p][i] = to_node;

			for (uc n=0;n < board_count[from_node];n++) {
				uc to_node2 = board[from_node][n];
				if (s.nodes[to_node2] != 10) {
					uc p2 = s.nodes[to_node2];
					s.moves[p2] -= s.node_moves_count[to_node2];
					s.node_moves_count[to_node2] = 0;
					for (uc n_n=0;n < board_count[to_node2];n_n++) {
						uc to_to_node = board[to_node2][n_n];
						if (s.nodes[to_to_node] == 10) {
							s.node_moves[to_node2][s.node_moves_count[to_node2]] = to_to_node;
							s.node_moves_count[to_node2]++;
							s.moves_count[p2]++;
						}
					}
				}
			}
			if ((s.nodes[row[to_node][0][0]] == p) && (s.nodes[row[to_node][0][1]] == p) || (s.nodes[row[to_node][1][0]] == p) && (s.nodes[row[to_node][1][1]] == p)) {
				s.phase = 1;
			}
			else {
				s.round++;
			}
		}
	}
	else {
		p = (s.round + 1) % 2;
		std::uniform_int_distribution<>dist(0, s.player_nodes_count[p]-1);
		bool b = true;
		uc r;
		uc from_node;
		do {
			r = dist(e2);
			from_node = s.player_nodes[p][r];
			if ((s.nodes[row[from_node][0][0]] != p) || (s.nodes[row[from_node][0][1]] != p) && (s.nodes[row[from_node][1][0]] != p) || (s.nodes[row[from_node][1][1]] != p)) {
				b = false;
			}
		} while (b);
		
		s.nodes[from_node] = 10;
		s.player_nodes[p][r] = s.player_nodes[p][s.player_nodes_count[p] - 1];
		s.player_nodes_count[p]--;
		if (s.round > 17) {
			s.moves_count[p] -= s.node_moves_count[from_node];
			for (uc n = 0;n < board_count[from_node];n++) {
				uc to_node2 = board[from_node][n];
				if (s.nodes[to_node2] != 10) {
					uc p2 = s.nodes[to_node2];
					s.moves[p2] -= s.node_moves_count[to_node2];
					s.node_moves_count[to_node2] = 0;
					for (uc n_n = 0;n < board_count[to_node2];n_n++) {
						uc to_to_node = board[to_node2][n_n];
						if (s.nodes[to_to_node] == 10) {
							s.node_moves[to_node2][s.node_moves_count[to_node2]] = to_to_node;
							s.node_moves_count[to_node2]++;
							s.moves_count[p2]++;
						}
					}
				}
			}
		}
		s.phase = 0;
		s.round++;
	}
}




// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
