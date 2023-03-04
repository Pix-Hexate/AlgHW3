#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct node {
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
	vector<node*> headers;


	graph(vector<int> vertex, vector<pair<int, int>> edges) {

		for (int i = 0; i < vertex.size(); i++) {
			node* new_node = new node(i);
			headers.push_back(new_node);
		}

		node* current = NULL;
		for (int i = 0; i < edges.size(); i++) {
			add_edge(edges[i].first, edges[i].second);
			add_edge(edges[i].second, edges[i].first);
		}

	}

	/*
	~graph() {
		node* current;
		node* temp;
		for (int i = 0; i < headers.size(); i++) {
			current = headers[i];
			while (current->next != NULL) {
				temp = current;
				current = current->next;
				delete temp;
			}
			delete current;
		}
	}
	*/

};

void graph::add_edge(int node1, int node2) {
	node* to_insert = new node(node2);
	node* current = headers[node1];
	while (current->next != NULL) { current = current->next; }
	current->next = to_insert;
}

void graph::delete_edge(int parent, int to_delete, bool selfcall) {
	bool error = false;
	if (parent == to_delete) { cout << "error, cannot delete header"; error = true; }
	node* current = headers[parent];
	if (current->next == NULL) { cout << "error, parent is empty"; error = true; }
	if (error = false) {
		node* previous = current;
		while ((current->next != NULL) && (current->data != to_delete)) { previous = current; current = current->next; };

		if (current->data == to_delete) {
			if (current->next == NULL) {
				previous->next = NULL;
				delete current;
			}
			else {
				previous->next = current->next;
				delete current;
			}
			delete_edge(to_delete, parent, true);
			cout << "Edge deleted";
		}
		else {
			if(!selfcall){ cout << "error, edge not found";}
		}

	}
}

vector<int> DFS(graph grap, int start) {
	vector<int> answer;
	vector<node*> to_check;
	node* current = grap.headers[start];
	answer.push_back(current->data);
	
	while (current->next != NULL) {
		to_check.push_back(current->next);
		current = current->next;
	}

	while (!to_check.empty()) {
		if ((find(answer.begin(), answer.end(), to_check[to_check.size() - 1]->data)) == answer.end()) {
			answer.push_back(to_check[to_check.size() - 1]->data);
		}
		to_check.pop_back();

		current = grap.headers[answer[answer.size() - 1]];
		if (((find(answer.begin(), answer.end(), current->data)) == answer.end()) && ((find(to_check.begin(), to_check.end(), current)) == to_check.end())) {
			to_check.push_back(current);
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

	vector<int> v;
	for (int i = 0; i < numbers[0]; i++) {
		v.push_back(i);
	}

	vector<pair<int, int>> edges;
	for (int i = 1; i < (numbers.size() - 1); i = i + 2) {
		edges.push_back(make_pair(numbers[i], numbers[i + 1]));
	}



		
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < edges.size(); i++) {
		cout << "(" << edges[i].first << "," << edges[i].second << "), ";
	}
	
	cout << endl << endl;

	
	graph The_Graph(v, edges);
	for (int i = 0; i < The_Graph.headers.size(); i++) { //This outputs data
		node* current = The_Graph.headers[i];

		//These If, elif, elif, else statements are simply here to implement proper grammer in all cases of connection length
		if(current->next == NULL){ cout << "Node " << current->data << " is linked to nothing" << endl; }
		else if (current->next->next == NULL) { cout << "Node " << current->data << " is linked to node " << current->next->data << endl; }
		else if (current->next->next->next == NULL) { cout << "Node " << current->data << " is linked to nodes " << current->next->data << " and " << current->next->next->data << endl; }
		else{
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
	
	vector<int> DFS_CHECK = DFS(The_Graph, 0);

	cout << endl << "DFS Result (0 Start) : ";
	for (int i = 0; i < DFS_CHECK.size(); i++) {
		cout << DFS_CHECK[i] << ", ";
	}

	return 0;
}
