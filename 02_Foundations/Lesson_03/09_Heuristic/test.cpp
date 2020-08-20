void TestHeuristic(){
	cout << "-----------------------------------------------------------" << endl;
	cout << "HEURISTIC FUCNTION TEST: ";
	if(Heuristic(1,2,3,4)!=4){
		cout << "failed"  << endl;
		cout << endl << "Heuristic(1,2,3,4)= " << Heuristic(1,2,3,4) << endl;
		cout << "Correct result: 4" << endl; 
	} else if (Heuristic(2,-1, 4, -7) != 8){
		cout << "TestHeristic Failed" << endl; 
		cout << endl << "Heuristic(2,-1,4,-7)=" << Heuristic(2,-1,4,-7)<< endl; 
		cout << "Correct result: 8" << endl; 
		cout << endl;
	}
	else {
		cout << "passed" << endl; 
	}
	cout << "-----------------------------------------------------------" << endl;
}