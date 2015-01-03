#include <iostream>
#include <map>
#include <stdio.h>
using namespace std;

class Utility{
	
private:
	int dim;
	int* memory;
public:
	Utility(int);
	Utility(int,int*);
	void setUtility(int*);
	void printUtility();
	int get(int,int);
};
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

int main(){
	
	int t[]={1,3,2,1};
	Utility* u=new Utility(2,&t[0]);
	u->setUtility(&t[0]);
	u->printUtility();
	cout<<u->get(0,1)<<endl;
	
	return 0;
}
