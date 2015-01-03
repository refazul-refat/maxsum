#include <iostream>
#include <map>
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
	int total;
	Utility* u;
public:
	UtilitySet(int);
	void setUtility(int,Utility*);
	Utility* getUtility(int);
};

UtilitySet::UtilitySet(int t){
	
	total=t;
	u=new Utility[total];
}
void UtilitySet::setUtility(int index,Utility* util){
	
	u[index]=*util;
}
Utility* UtilitySet::getUtility(int index){
	
	return &u[index];
}

int main(){
	
	int t[]={1,3,2,1};
	Utility* u=new Utility(2,&t[0]);
	u->setUtility(&t[0]);
	u->printUtility();
	cout<<u->get(0,1)<<endl;
	
	UtilitySet* set=new UtilitySet(3);
	set->setUtility(0,u);
	
	Utility* ut=set->getUtility(0);
	ut->printUtility();
	
	return 0;
}
