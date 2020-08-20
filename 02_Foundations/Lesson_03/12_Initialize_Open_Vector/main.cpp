#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;



enum class State{kEmpty, kObstacle,kClosed};

vector<State> ParseLine(string line);
vector<vector<State>> ReadBoardFile(string path);
void PrintBoard(const vector<vector<State>> board);
string CellString(State cell);
vector<vector<State>> Search (vector<vector<State>> grid,int start[2], int goal[2]);
int Heuristic(int x1, int y1, int x2, int y2);
void AddToOpen(int x, int y, int g, int h,
			   vector<vector<int>> &OpenNodes,
			    vector<vector<State>> &grid);

#include "test.cpp"

int main(){
	int init[] = {0,0};
	int goal[] = {4,5};
	vector<vector<State>> Map = ReadBoardFile("1.board");
	auto solution = Search(Map, init, goal);
	PrintBoard(solution);
	//Tests
	TestHeuristic();
	TestAddToOpen();
}

vector<State> ParseLine(string line){
	vector<State> myVector{};
	istringstream line2stream(line);
	int a;
	char c;
	while(line2stream >> a >> c && c==','){
		if (a == 0)
			myVector.push_back(State::kEmpty);
		else
			myVector.push_back(State::kObstacle);

	}
	return myVector;
}

vector<vector<State>> ReadBoardFile(string path){
	vector<vector<State>> Map={};
	ifstream myFile(path);
	string String2Parse;
	if(myFile){
		//cout << "File loaded successfully" << endl; 
		while(getline(myFile,String2Parse)){
			//cout << String2Parse << endl; 
			//cout << "Parsing..." << endl; 
			Map.push_back(ParseLine(String2Parse));
		}
	}
	else{
		cout << " Error" << endl; 
	}

	return Map;
}



void PrintBoard(const vector<vector<State>> board){
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board[i].size(); j++){
			cout << CellString(board[i][j]);
		}
		cout << endl;
	}
}

string CellString(State cell){
	if(cell == State::kEmpty)
		return "0 ";
	else
		return "/ ";
}

vector<vector<State>> Search (vector<vector<State>> grid,int start[2], int goal[2]){
	vector<vector<int>> open{};
	int g = 0;
	int h = Heuristic(start[0],start[1],goal[0],goal[1]);
	AddToOpen(start[0],start[1],g,Heuristic(start[0],start[1],goal[0],goal[1]), open,grid);
	cout << "No path found! " << endl; 
	return (vector<vector<State>> {});
}

int Heuristic(int x1, int y1, int x2, int y2){
	return (abs(x2-x1) + abs(y2-y1));
}


void AddToOpen(int x, int y, int g, int h,
			   vector<vector<int>> &OpenNodes,
			    vector<vector<State>> &grid){
	//vector<int> node ={x,y,g,h};
	//OpenNodes.push_back(node);
	OpenNodes.push_back(vector<int> {x,y,g,h});
	grid[x][y] = State::kClosed;
}