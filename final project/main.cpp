#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <array>
#include "Graph.hpp"
using namespace std;

Graph::Graph(){
	vector<vertex> temp;
	this->vertices = temp;
}

Graph::~Graph(){}

void Graph::addEdge(char v1, char v2, int weight)
{
	vertex *v = findVertex(v1);
	for(int i = 0; i < v->Edges.size();i++){
		if(v2 == v->Edges[i].v->letter){
			v->Edges[i].weight++;
			return;
		}
	}
	vertex *current = findVertex(v1);
	vertex *to_add = findVertex(v2);
	Edge *temp = new Edge;
	temp->v = to_add;
	temp->weight = weight;
	current->Edges.push_back(*temp);

}


void Graph::addVertex(char letter)
{

    vertex temp;
    temp.letter = letter;
    temp.visited = false;
    vector<Edge> e;
	temp.Edges = e;

    vertices.push_back(temp);
}

void Graph::displayEdges(){
	for(int i = 0; i < vertices.size(); i++){
		cout << "letter " << vertices[i].letter << ":";
		int count = 0;
		char c;
	    for(int j = 0;j < vertices[i].Edges.size();j++){
			if(count < vertices[i].Edges[j].weight){
				count = vertices[i].Edges[j].weight;
				c = vertices[i].Edges[j].v->letter;
			}
	        if(vertices[i].Edges[j].weight > 0){
				cout << " ---> " << vertices[i].Edges[j].v->letter <<" weight "<< vertices[i].Edges[j].weight << " ";
			}
	    }
		cout << "\n\n";
		//cout <<  vertices[i].letter << " ---> " << c << " weight: " << count << endl;
    }
}

string Graph::encrypt(string alphabet, string cipher, string message){
	int position;
	int size = message.size();
	string encrypted;
	for(int i = 0; i < message.length(); i++){
		position = alphabet.find(message[i]);
		if(position < 26 && position >= 0){
			encrypted += cipher[position];
			//cout << alphabet[position] << " " << position << " " << cipher[position] << endl;
		}
		else{
			encrypted += " ";
		}

	}
	return encrypted;
}

string Graph::decrypt(string alphabet, string cipher, string message){
	int position;
	int size = message.size();
	string decrypted;
	for(int i = 0; i < message.length(); i++){
		position = cipher.find(message[i]);
		if(position < 26 && position >= 0){
			decrypted += alphabet[position];
			//cout << alphabet[position] << " " << position << " " << cipher[position] << endl;
		}
		else{
			decrypted += " ";
		}

	}
	return decrypted;
}

void Graph::printDFS()
{
    setAllVerticesUnvisited();
	for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].visited == false){
            DFTraversal(&vertices[i]);
        }
    }
}


  void Graph::setAllVerticesUnvisited(){
	  for(int i = 0; i < vertices.size(); i++){
          vertices[i].visited = false;
      }
  }


vertex* Graph::findVertex(char letter){

	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].letter == letter){
			return &vertices[i];
		}
	}
}

void Graph::BFTraversalLabel(char start_letter)
{
    vertex *start = findVertex(start_letter);

	start->visited = true;

	for(int i = 0; i < start->Edges.size(); ++i){
		if(!(start->Edges[i].v->visited)){
			start->Edges[i].v->visited = true;
			BFTraversalLabel( start->Edges[i].v->letter);
		}
	}

}


void Graph::DFTraversal(vertex* v)
{
    v->visited = true;
	cout << v->letter << endl;
	for(int i = 0; i < v->Edges.size();i++){
		if(!(v->Edges[i].v->visited)){
			DFTraversal(v->Edges[i].v);
		}
	}
}

string Graph::makeCipher(string alphabet){
	string cipher = "";
	for(int i = 0;i < 26; i++){
		vertex *current = findVertex(alphabet[i]);
		int count = 0;
		char c;
	    for(int j = 0;j < current->Edges.size();j++){

			if(count < current->Edges[j].weight){
				count = current->Edges[j].weight;
				c = current->Edges[j].v->letter;
			}
	    }
		if(cipher.find(c) > cipher.size()){
				cipher = cipher + c;
		}
		else{
			int i = 0;
			while(i < current->Edges.size()){
				c = current->Edges[i].v->letter;
				if(cipher.find(c) > cipher.size()){
					cipher = cipher + c;
					break;
				}
				i++;
			}
		}


	}
	return cipher;
}


int main(int argc, char* argv[]){

	//g.displayEdges();
	string t = "the";
	//cout << "\n\n";


	// string message = "hello world";
	// cout << "original: " << message << endl;
	// message = g.encrypt(alphabet, cipher, message);
	// cout << "encrypted: " << message << endl;
	// message = g.decrypt(alphabet, cipher, message);
	// cout << "decrypted: " << message << endl;
	Graph g;
	string cipher;
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	string least_to_most = "qjzxvkwyfbghmpduclsntoirae";
	string x;
    bool open = true;
	string file;
	cout << "Enter fine name:" << endl;
	//cin.ignore();
	getline(cin, file);
	ifstream myfile (file);
	if (myfile.is_open()){
		for(int i = 0; i < 26; i++){
			g.addVertex(alphabet[i]);
		}
		char ch;
		char last = 'a';
		fstream fin(file, fstream::in);
		while (fin >> noskipws >> ch) { //makes it read in file char by char
			ch = tolower(ch);
			if(isalpha(ch)){
				g.addEdge(last, ch, 1);
				last = ch;
			}
			else{
				ch = last;
			}
		}


		myfile.close();
	}
	else{
	  cout << "failed to open file" << endl;
	  cout << file << endl;
	  return 1;
		}
	cipher = g.makeCipher(least_to_most);
	cout << "\n" << "cipher:" << endl << alphabet << endl << cipher <<  endl;
	cout << "\n";
    while(open){
      cout << "======Main Menu=====" << endl;
      cout << "1. Encrypt a message" << endl;
      cout << "2. Decrypt a message" << endl;
	  cout << "3. Encrypt to a file" << endl;
	  cout << "4. Decrypt from a file" << endl;
      cout << "enter 'q' to quit" << endl;
      cin >> x;
      if(x == "1"){
		  	string message;
  		  	cout << "Enter message:" << endl;
          	cin.ignore();
		  	getline(cin, message);
		  	message = g.encrypt(alphabet, cipher, message);
		 	cout << "encrypted: " << message << endl;

      }
      else if(x == "2"){
		  	string message;
  			cout << "Enter message:" << endl;
  			cin.ignore();
  			getline(cin, message);
  			message = g.decrypt(alphabet, cipher, message);
  			cout << "decrypted: " << message << endl;
      }
	  else if(x == "3"){
		  	// string file;
			string line;
			string message;
  			cout << "Enter message:" << endl;
  			cin.ignore();
  			getline(cin, message);

			message = g.encrypt(alphabet, cipher, message);

			ofstream output;
  			output.open ("output.txt");
  			output << message;
  			output.close();

      }
	  else if(x == "4"){
		  	// string file;
			string line;
			string message;
  			cout << "Enter file name:" << endl;
  			cin.ignore();
  			getline(cin, file);
			ifstream myfile (file);
			if (myfile.is_open()){
			    while (! myfile.eof()){
			        getline(myfile,line);
			        message += line;

			    }
			    myfile.close();

			}
			message = g.decrypt(alphabet, cipher, message);
			cout << message << endl;

      }
      else if(x == "q"){
        cout << "Goodbye!" << endl;
        open = false;
      }
      else{
        cout << "Please choose a number provided" << endl;
      }
    }

    return 0;

}
