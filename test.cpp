#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

#define DIM 2

class Utility{
	
private:
	int dim;
	int* memory;
public:
	Utility();
	Utility(int);
	Utility(int,int*);
	void setUtility(int*);
	void printUtility();
	int get(int,int);
};
Utility::Utility(){
	
	dim=DIM;
	memory=new int[dim*dim];
}
Utility::Utility(int d){
	
	dim=d;
	memory=new int[dim*dim];
}
Utility::Utility(int d,int* p){
	
	dim=d;
	memory=new int[dim*dim];
	for(int i=0;i<dim*dim;i++){
		
		memory[i]=p[i];
	}
}
void Utility::setUtility(int* p){
	
	for(int i=0;i<dim*dim;i++){
		
		memory[i]=p[i];
	}
}
void Utility::printUtility(){
	
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			cout<<memory[i*dim+j]<<" ";
		}
		cout<<endl;
	}
}
int Utility::get(int x,int y){
	
	return memory[x*dim+y];
}

class UtilitySet{
	
private:
	int N;
	Utility* u;
public:
	UtilitySet(int);
	void setUtility(int,int,Utility*);
	Utility* getUtility(int,int);
};

UtilitySet::UtilitySet(int n){
	N=n;
	u=new Utility[N*N];
}
void UtilitySet::setUtility(int X,int Y,Utility* util){
	
	u[(X-1)*N+Y]=*util;
	int temp[]={util->get(0,0),util->get(1,0),util->get(0,1),util->get(1,1)};
	Utility* t=new Utility(2,&temp[0]);
	u[(Y-1)*N+X]=*t;
}
Utility* UtilitySet::getUtility(int X,int Y){
	
	return &u[(X-1)*N+Y];
}
UtilitySet* set;

class Node{
	
public:
	int degree,id;
	vector<int> neighbours;
	vector< vector<int> > messages;
	Node();
	bool isNeighbour(int);
	void addNeighbour(int);
	void removeNeighbour(int);
	void showNeighbours();
	void sendMessage(Node*,int*);
	void showMessages();
	void broadCast(Node*);
};
Node::Node(){
}
bool Node::isNeighbour(int n){
	for(int i=0;i<neighbours.size();i++){
		if(n==neighbours[i])
			return true;
	}
	return false;
}
void Node::addNeighbour(int n){
	if(isNeighbour(n))return;
	neighbours.push_back(n);
}
void Node::removeNeighbour(int n){
	if(!isNeighbour(n))return;
	for(int i=0;i<neighbours.size();i++){
		if(n==neighbours[i])
			neighbours.erase(neighbours.begin()+i,neighbours.begin()+i+1);
	}
}
void Node::showNeighbours(){
	for(int i=0;i<neighbours.size();i++){
		cout<<neighbours[i]<<" ";
	}
	cout<<endl;
}
void Node::sendMessage(Node* n,int* m){
	vector<int> v;
	v.push_back(id);
	
	int source=id;
	int destination=(*n).id;
	
	int a1=set->getUtility(source,destination)->get(0,0)+(*(m+0));
	int a2=set->getUtility(source,destination)->get(1,0)+(*(m+1));
	
	int b1=set->getUtility(source,destination)->get(0,1)+(*(m+0));
	int b2=set->getUtility(source,destination)->get(1,1)+(*(m+1));
	
	int a=a1>a2?a1:a2,b=b1>b2?b1:b2;v.push_back(a);v.push_back(b);
	
	(*n).messages.push_back(v);
}
void Node::broadCast(Node* root){
	for(int i=0;i<neighbours.size();i++){
		int m[]={0,0};
		for(int j=0;j<messages.size();j++){
			if(neighbours[i]==messages[j][0])continue;
			
			m[0]+=messages[j][1];
			m[1]+=messages[j][2];
		}
		sendMessage(root+(neighbours[i]),&m[0]);
	}
}
void Node::showMessages(){
	for(int i=0;i<messages.size();i++){
		cout<<"To "<<id<<" | From "<<messages[i][0]<<" - ";
		for(int j=1;j<messages[i].size();j++){
			cout<<messages[i][j]<<" ";
		}
		cout<<endl;
	}
}


int main(){
	
	int N=5;					//Number of variables
	int t13[]={1,3,2,1};		//Function between x1 & x3
	int t34[]={3,4,10,1};		//Function between x3 & x4
	int t23[]={1,5,4,2};		//Function between x2 & x3
	int t15[]={2,4,8,3};		//Function between x2 & x3
	
	set=new UtilitySet(N-1);
	set->setUtility(1,3,new Utility(2,&t13[0]));
	set->setUtility(3,4,new Utility(2,&t34[0]));
	set->setUtility(2,3,new Utility(2,&t23[0]));
	set->setUtility(1,5,new Utility(2,&t15[0]));
	
	//set->getUtility(3,1)->printUtility();
	//set->getUtility(3,4)->printUtility();
	//set->getUtility(2,3)->printUtility();
	
	Node* n=new Node[N+1];
	(*(n+1)).degree=2;
	(*(n+1)).id=1;
	(*(n+1)).addNeighbour(3);
	(*(n+1)).addNeighbour(5);
	
	(*(n+2)).degree=1;
	(*(n+2)).id=2;
	(*(n+2)).addNeighbour(3);
	
	(*(n+3)).degree=3;
	(*(n+3)).id=3;
	(*(n+3)).addNeighbour(1);
	(*(n+3)).addNeighbour(2);
	(*(n+3)).addNeighbour(4);
	
	(*(n+4)).degree=1;
	(*(n+4)).id=4;
	(*(n+4)).addNeighbour(3);
	
	(*(n+5)).degree=1;
	(*(n+5)).id=5;
	(*(n+5)).addNeighbour(1);
	
	int m5[]={0,0};
	int m2[]={0,0};
	int m4[]={0,0};
	(*(n+5)).sendMessage(n+1,&m5[0]);
	(*(n+2)).sendMessage(n+3,&m2[0]);
	(*(n+4)).sendMessage(n+3,&m4[0]);
	(*(n+3)).showMessages();
	
	(*(n+1)).broadCast(n);
	(*(n+3)).broadCast(n);
	(*(n+1)).broadCast(n);
	
	(*(n+5)).showMessages();
	(*(n+2)).showMessages();
	(*(n+4)).showMessages();
	
	cout<<endl;
	return 0;
}
