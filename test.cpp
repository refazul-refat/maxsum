#include <iostream>
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
	
	u[X*N+Y]=*util;
}
Utility* UtilitySet::getUtility(int X,int Y){
	
	return &u[X*N+Y];
}

int main(){
	
	int N=4;					//Number of variables
	int t02[]={1,3,2,1};		//Function between x1 & x3
	int t23[]={3,4,10,1};		//Function between x3 & x4
	int t12[]={1,5,4,2};		//Function between x2 & x3
	
	UtilitySet* set=new UtilitySet(N);
	set->setUtility(0,2,new Utility(2,&t02[0]));
	set->setUtility(2,3,new Utility(2,&t23[0]));
	set->setUtility(1,2,new Utility(2,&t12[0]));
	
	set->getUtility(0,2)->printUtility();
	set->getUtility(2,3)->printUtility();
	set->getUtility(1,2)->printUtility();
	
	return 0;
}
