#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct node { // Simple node struct
	int data;
	struct node* next = NULL;

	node(int dataa) {
		data = dataa;
	}
};



class graph {
public:
	void add_edge(int node1, int node2);
	void delete_edge(int parent, int to_delete, bool selfcall = false);
	vector<int> DFS(int start);
	void components();
	void matrix();
	vector<node*> headers;


	graph(vector<int> vertex, vector<pair<int, int>> edges) { 
		for (int i = 0; i < vertex.size(); i++) {//Create headers based on vertexes, basically 1 to x
			node* new_node = new node(i);
			headers.push_back(new_node);
		}

		node* current = NULL; //For each edge, we simply call the add_edge function twice
		for (int i = 0; i < edges.size(); i++) {
			add_edge(edges[i].first, edges[i].second);
			add_edge(edges[i].second, edges[i].first);
		}

	}

	
	~graph() { // A simple singly linked list destructor 
		node* current;
		node* next;
		for (int i = 0; i < headers.size(); i++) {
			current = headers[i];
			while (current != NULL) {
				next = current->next;
				delete current;
				current = next;
			}
		}
	}
	

};

void graph::add_edge(int node1, int node2) {
	node* to_insert = new node(node2); 
	node* current = headers[node1];
	while (current->next != NULL) { current = current->next; } //This is simply a bit of logic to add a node to a header list to "add an edge"
	current->next = to_insert;
}

void graph::delete_edge(int parent, int to_delete, bool selfcall) { //This deletes two objects from two header lists via one self call
	bool error = false;
	if (parent == to_delete) { cout << "error, cannot delete header"; error = true; } //Some error checking in case improper inputs were given
	node* current = headers[parent];
	if (current->next == NULL) { cout << "error, parent is empty"; error = true; } //Some error checking in case improper inputs were given
	if (error == false) { //If no error
		node* previous = current;
		while ((current->next != NULL) && (current->data != to_delete)) { previous = current; current = current->next; }; //Loop until cant, or found
		if (current->data == to_delete) { //If found, we delete the found thing
			if (current->next == NULL) { //And some logic to reconnect the linked list if necessary
				previous->next = NULL;
				delete current;
			}
			else {
				previous->next = current->next;
				delete current;
			}
			if(!selfcall){ delete_edge(to_delete, parent, true); } //This calls delete on the *other* header, since connections go two ways, but only once
			cout << "Edge deleted";
		}
		else {
			if (!selfcall) { cout << "error, edge not found"; } //This error lessage plays if not found and not self call
		}

	}
}

vector<int> graph::DFS(int start) {
	vector<int> answer; //This is also the "visited" list
	vector<node*> to_check;
	node* current = headers[start];
	answer.push_back(current->data); //We assume we have a header and that's always first

	while (current->next != NULL) { //We push back all of the header's connections onto the "to check" list
		to_check.push_back(current->next);
		current = current->next;
	}

	while (!to_check.empty()) { //This loop runs until there is nothing more to check
		if ((find(answer.begin(), answer.end(), to_check[to_check.size() - 1]->data)) == answer.end()) {
			answer.push_back(to_check[to_check.size() - 1]->data); //If  last item in to_check not visited, add to visted list
		}
		to_check.pop_back(); // and delete it

		current = headers[answer[answer.size() - 1]]; //We then look at the "most recent" addition to the "visited" list
		if (((find(answer.begin(), answer.end(), current->data)) == answer.end()) && ((find(to_check.begin(), to_check.end(), current)) == to_check.end())) {
			to_check.push_back(current); //And check if any of it's neighbors need adding to the to_check list
		}
		while (current->next != NULL) {
			current = current->next;
			if (((find(answer.begin(), answer.end(), current->data)) == answer.end()) && ((find(to_check.begin(), to_check.end(), current)) == to_check.end())) {
				to_check.push_back(current);
			}
		}

	}

	return answer;
}

void graph::components() { //Components literally just calls dfs for each header, see dfs
	vector<int> output;
	for (int i = 0; i < headers.size(); i++) {
		output = DFS(i);

		cout << "Connected Components of " << i << " : ";
		for (int j = 0; j < output.size(); j++) {
			cout << output[j] << " ";
		}
		cout << endl;
	}

}

void graph::matrix() {
	bool found = false;
	node* current;
	for (int i = 0; i < headers.size(); i++) { //These two for loops loop y 
		for (int j = 0; j < headers.size(); j++) {// and x respectively
			if (i == j) { cout << "0 "; }
			else {
				current = headers[j]; //Using a bit of logic to determine whether or not to output a 0 or 1 for the matrix
				while (current != NULL) {
					if (current->data == i) { found = true; }
					current = current->next;
				}
				if (found) { cout << "1 "; }
				else { cout << "0 ";}

			}

			found = false;

		}
		cout << endl;


	}

}

int main() {
	string input; //Taking input
	cout << "Example input is '5  0  1  1  4  2  3  1  3  3  4  -1 '" << endl << "Please use this exact formatting, this program does not have input error detection/correction'" << endl << "Enter the input : ";
	getline(cin, input); // Grabbing the entire input string, this logic was grabbed from a previous hw assignment of mine that extracted numbers from strings


	int tot = input.size();
	vector<int> numbers;
	string tempholder;

	for (int i = 0; i < tot; i++) //Translates the string input into a vector of ints
	{
		if (isdigit(input[i])) //If letter of string is a digit, then stick the digit into the numbers vector
		{
			tempholder = input[i]; //If this is not here for some reason, ascii representation of ints are pushed back rather than ints, stoi rejects input[i] as an input for some reason
			while (isdigit(input[i + 1])) { //this logic here is for multi-digit numbers
				tempholder = tempholder + input[i + 1];
				i++;
			}
			numbers.push_back(stoi(tempholder));
		}
	}


	
	vector<int> v; //Creating the vertexes from our data, simply just making a vector of numbers 1-n
	for (int i = 0; i < numbers[0]; i++) {
		v.push_back(i);
	}

	vector<pair<int, int>> edges; //Creating the edges from the large string input 
	for (int i = 1; i < (numbers.size() - 1); i = i + 2) {
		edges.push_back(make_pair(numbers[i], numbers[i + 1]));
	}



	/* --READ ME-- This was a function to output our vertexes and edges, feel free to turn back on
	
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < edges.size(); i++) {
		cout << "(" << edges[i].first << "," << edges[i].second << "), ";
	}

	cout << endl << endl;
	*/



	//  --- READ ME --- This is a test function we had for testing node linkage, feel free to turn it back on
	/*
	for (int i = 0; i < The_Graph.headers.size(); i++) { //This outputs data
		node* current = The_Graph.headers[i];

		//These If, elif, elif, else statements are simply here to implement proper grammer in all cases of connection length
		if (current->next == NULL) { cout << "Node " << current->data << " is linked to nothing" << endl; }
		else if (current->next->next == NULL) { cout << "Node " << current->data << " is linked to node " << current->next->data << endl; }
		else if (current->next->next->next == NULL) { cout << "Node " << current->data << " is linked to nodes " << current->next->data << " and " << current->next->next->data << endl; }
		else {
			cout << "Node " << current->data << " is linked to nodes ";
			while (current->next != NULL) {
				current = current->next;

				if (current->next == NULL) {
					cout << "and " << current->data;
				}
				else { cout << current->data << ","; }
			}
			cout << endl;
		}
	}
	*/
	

	//Creating the graph and calling our two functions
	graph The_Graph(v, edges);
	The_Graph.matrix();
	The_Graph.components();
	

	return 0;
}
