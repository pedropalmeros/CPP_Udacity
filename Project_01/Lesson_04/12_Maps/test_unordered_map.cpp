#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
 
int main()
{
string key = "word";
string def_1 = "definition 01";
string def_2 = "definition 02";
string def_3 = "definition 03";
string def_4 = "definition 04";
string def_5 = "definition 05";

unordered_map <string, vector<string>> my_map;

cout << "The size of the map is: " << my_map.size() << endl;
if(my_map.empty()){
	cout << "The map is empty"  << endl; 
}else{
	cout << "The map is not empty" << endl;
}

cout << my_map.find(key) << endl; 

    return 0;
}