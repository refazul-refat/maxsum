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
	int degree,id,color;
	vector<int> z;
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
	degree=0;
	z.push_back(0);
	z.push_back(0);
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
	
	for(int i=0;i<(*n).messages.size();i++){
		if((*n).messages[i][0]==id){
			(*n).messages.erase((*n).messages.begin()+i,(*n).messages.begin()+i+1);
		}
	}
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
	cout<<id<<endl;
	for(int i=0;i<messages.size();i++){
		cout<<"-->From "<<messages[i][0]<<" - ";
		for(int j=1;j<messages[i].size();j++){
			cout<<messages[i][j]<<" ";
		}
		cout<<endl;
	}
}


int main(){
	
	freopen("input.txt","r",stdin);//redirects standard input
	
	int N;
	scanf("%d",&N);				//Number of variables
	set=new UtilitySet(N);		//Number of utility functions	//Should've been UtilitySet(N-1) for 0-based indexing
	Node* n=new Node[N+1];		//Node represents variable		//Should've been Node[N] for 0-based indexing
	
	//int dimension;
	//scanf("%d",&dimension);
	
	for(int count=0;count<N-1;count++){
		
		int x,y;
		scanf("%d%d",&x,&y);	//Connection exists between x and y
		
		int matrix[4];
		scanf("%d%d%d%d",&matrix[0],&matrix[1],&matrix[2],&matrix[3]);
		set->setUtility(x,y,new Utility(2,&matrix[0]));			//Setup utility between x and y
		
		n[x].degree++;
		n[y].degree++;
		
		n[x].addNeighbour(y);
		n[y].addNeighbour(x);
		
		n[x].id=x;n[y].id=y;	//Unsmart, anyway
	}
	
	int z[]={0,0};
	int highestdegree=0;
	for(int degree=1;degree<=N;degree++){
		for(int i=1;i<=N;i++){
			if(n[i].degree==degree){
				if(degree==1)
					n[i].sendMessage(&n[n[i].neighbours[0]],&z[0]);
				else
					n[i].broadCast(n);
				if(degree>highestdegree)highestdegree=degree;
			}
		}
	}
	for(int degree=highestdegree-1;degree>1;degree--){
		for(int i=1;i<=N;i++){
			if(n[i].degree==degree)
				n[i].broadCast(n);
		}
	}
	for(int i=1;i<=N;i++){
		n[i].showMessages();
		for(int j=0;j<n[i].messages.size();j++){
			n[i].z[0]+=n[i].messages[j][1];
			n[i].z[1]+=n[i].messages[j][2];
		}
		if(n[i].z[0]>n[i].z[1]){
			n[i].color=0;
			cout<<"RED"<<endl;
		}else{
			n[i].color=1;
			cout<<"BLUE"<<endl;
		}
		cout<<"-------------------------------------"<<endl;
	}
	return 0;
}
