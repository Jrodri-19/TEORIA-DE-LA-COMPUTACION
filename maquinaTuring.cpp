#include <bits/stdc++.h>
using namespace std;
using namespace std;
enum Direction { I, D };
struct Transition {
	char writeSymbol;
	Direction moveDirection;
	string nextState;
};

class TuringMachine {
public:
	TuringMachine
	(const vector<char>& tapeInput, 
	 const string& startState, 
	 const unordered_map<string, unordered_map<char, Transition>>& transitions)
	: tape(tapeInput), headPosition(0), currentState(startState), transitionTable(transitions) {}
	
	void run ();
	void printTape(int);
	
private:
		vector<char> tape;
		size_t headPosition;
		string currentState;
		unordered_map<string, unordered_map<char, Transition>> transitionTable;
};
void TuringMachine::run(){
	while (transitionTable.find(currentState) != transitionTable.end()) {
		printTape(headPosition);
		char currentSymbol = tape[headPosition];
		if (transitionTable[currentState].find(currentSymbol) == transitionTable[currentState].end()) {
			break; // No transition defined for this symbol in the current state
		}
		Transition transition = transitionTable[currentState][currentSymbol];
		
		// Write the new symbol on the tape
		tape[headPosition] = transition.writeSymbol;
		
		// Move the head
		if (transition.moveDirection == I) {
			if (headPosition > 0) {
				headPosition--;
			} else {
				headPosition=0;
			}
		} else if (transition.moveDirection == D) {
			headPosition++;
			if (headPosition >= tape.size()) {
				// Extend the tape to the right
				tape.push_back('U');
			}
		}
		// Transition to the next state
		currentState = transition.nextState;
	}
	printTape(headPosition);
}

void TuringMachine::printTape(int v){
	int count=0;
	for (char c : tape) {
		cout<<"\033[32m";
		if(count==v){
			cout << "\033[31m";
		}
		
		cout << c<<"\033[0m";
		count++;
	}
	cout << endl;

}
int main(int argc, char *argv[]) {
	system("cls");
	vector<char> tape = { '1', '1', '1', '1','1', '#', '1', '1' ,'1','U'};
	
	// Define the transition table
	unordered_map<string, unordered_map<char, Transition>> sigma = {
	{"q0", {{'1', {'1', D, "q0"}}, {'#', {'1', D, "q1"}}}},
	{"q1", {{'1', {'1', D, "q1"}}, {'U', {'U', I, "q2"}}}},
	{"q2", {{'1', {'U', D, "halt"}}}},

	};
	// Create the Turing Machine
	TuringMachine tm(tape, "q0", sigma);
	
	// Run the Turing Machine
	tm.run();
	
	return 0;

}

