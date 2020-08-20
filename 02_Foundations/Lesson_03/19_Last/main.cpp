#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



enum class State{kEmpty, kObstacle,kClosed,kPath,kStart,kFinish};
const int delta[4][2]{{-1,0},{0,-1},{1,0},{0,1}};

vector<State> ParseLine(string line);
vector<vector<State>> ReadBoardFile(string path);
void PrintBoard(const vector<vector<State>> board);
string CellString(State cell);
vector<vector<State>> Search (vector<vector<State>> grid,int start[2], int goal[2]);
int Heuristic(int x1, int y1, int x2, int y2);
void AddToOpen(int x, int y, int g, int h,
			   vector<vector<int>> &OpenNodes,
			    vector<vector<State>> &grid);
bool Compare (vector<int> node1, vector<int> node2);
void CellSort(vector<vector<int>> *v);
bool CheckValidCell(int x, int y,vector<vector<State>> &grid);
void ExpandNeighbors(const vector<int> &current_node,int goal[2], vector<vector<int>> &open,vector<vector<State>> &grid);

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
	TestCompare();
	TestSearch();
	TestCheckValidCell();
	TestExpandNeighbors();
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
	switch(cell){
		case State::kEmpty:
			return "0 " ;
			break;
		case State::kStart:
			return "i ";
			break;
		case State::kFinish:
			return "f ";
			break;
		case State::kObstacle:
			return "x ";
			break;
		case State::kPath:
			return "# ";
			break;
		default:
			return "0 " ;
	}
}

vector<vector<State>> Search (vector<vector<State>> grid,int start[2], int goal[2]){

	vector<vector<int>> open{};
	int x = start[0];
	int y = start[1];

	grid[x][y] = State::kStart;
	grid[goal[0]][goal[1]] = State::kFinish;

	int g = 0;
	int h = Heuristic(x,y,goal[0],goal[1]);
	AddToOpen(x,y,g,h, open,grid);

	while(open.size() > 0) 
	{
		CellSort(&open);
		vector<int> current_node = open.back();
		open.pop_back();
		x = current_node[0];
		y = current_node[1];

		grid[x][y] = State::kPath;
		if((x == goal[0]) && (y == goal[1])){
			cout << "We have reached the goal"  << endl; 
			return grid;
		}
		ExpandNeighbors(current_node,goal,open,grid);
	}

	cout << "No path found" << endl; 
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

bool Compare (vector<int> node1, vector<int> node2){
	if((node1[2]+node1[3]) > (node2[2]+node2[3]))
		return true;
	else
		return false;
}

void CellSort(vector<vector<int>> *v){
	sort(v->begin(), v->end(),Compare);
}


bool CheckValidCell(int x, int y,vector<vector<State>> &grid){
	if (x >= 0 &&
		x < grid.size() &&
		y >= 0 && 
		y < grid[x].size()&&
		grid[x][y]==State::kEmpty)
		return true;
	else
		return false;
}


void ExpandNeighbors(const vector<int> &current_node, 
					 int goal[2],
					 vector<vector<int>> &open, 
					 vector<vector<State>> &grid){
	int current_x = current_node[0];
	int current_y = current_node[1];
	int current_h = current_node[2];
	for(int i = 0; i < 4; i++){
			int x_test = current_x + delta[i][0];
			int y_test = current_y + delta[i][1];

			if(CheckValidCell(x_test, y_test, grid)){
				AddToOpen(x_test, y_test,current_h+1,Heuristic(x_test,y_test,goal[0],goal[1]),open, grid);
				cout << "The cell x: "  << x_test << " y: " << y_test << " has been added to open" << endl;

}}}
		



