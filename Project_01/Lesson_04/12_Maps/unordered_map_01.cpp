#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int main(){

unordered_map <int, string> lada = {{972,"Israel"},
									{93,"Afghanistan"},
									{213,"Algeria"}};

int lada2find = 960;

if(lada.find(lada2find)==lada.end()){
	cout << "Lada 960: NOT FOUND" << endl;
	lada[lada2find] = "Maldivas";
}

if(lada.find(lada2find)==lada.end()){
	cout << "Lada 960: NOT FOUND" << endl;
}
else{
	cout << "Lada 960: FOUND"  << endl; 
}

cout << "La lada 960 corresponde a "  << lada[960] << endl; 

return 0;
}

