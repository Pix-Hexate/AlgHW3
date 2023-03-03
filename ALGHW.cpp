#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;

struct node {
	int data;
	struct node* next;

	node(int dataa) {
		data = dataa;
	}
};

class graph {
public:
	vector<node*> headers;
	void add_edge(node x);
	void delete_edge(node x);

	graph(vector<int> vertex, vector<pair<int, int>> edges) {

		for (int i = 0; i < vertex.size(); i++) {
			node* new_node = new node(i);
			headers.push_back(new_node);
		}




	}





};



int main() {
	string input; //Taking input
	cout << "Example input is '5  0  1  1  4  2  3  1  3  3  4  -1 '" << endl << "Please use this exact formatting, this program does not have input error detection/correction'" << endl << "Enter the input : ";
	getline(cin, input);


	int tot = input.size();
	vector<int> numbers;
	string tempholder;

	for (int i = 0; i < tot; i++) //Translates the string input into a vector of ints
	{
		if (isdigit(input[i]))
		{
			tempholder = input[i]; //If this is not here for some reason, ascii representation of ints are pushed back rather than ints, stoi rejects input[i] as an input for some reason
			while (isdigit(input[i + 1])) { //for multi number digits
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

	/*
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < edges.size(); i++) {
		cout << "(" << edges[i].first << "," << edges[i].second << "), ";
	}
	*/




	return 0;
}
