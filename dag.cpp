#include<bits/stdc++.h>
#ifndef DAG_INCLUDED
#define DAG_INCLUDED

using namespace std;

ofstream fout("output.txt");
class DAG_Node{
    string label;
    int lChild;
    int rChild;
    string tempLabel;
public:
    DAG_Node(){
  
    }
    DAG_Node(string _label, int l, int r){
        label = _label;
        lChild = l;
        rChild = r;
        tempLabel = "0";
    }
    
    string getLabel(){ return label; }
    int getLChild(){ return lChild; }
    int getRChild(){ return rChild; }
    string getTempLabel(){ return tempLabel; }
    
    void setLabel(string _label){ label =_label; }
    void setLChild(int _lChild){ lChild = _lChild; }
    void setRChild(int _rChild){ rChild = _rChild; }
    void setTempLabel(string ll){ tempLabel = ll;}
    
    
    bool operator==(const DAG_Node& p) const{
        return (label == p.label && lChild == p.lChild && rChild == p.rChild);
    }
    
    bool operator<(const DAG_Node& p) const{
        return (label < p.label || (label == p.label && lChild < p.lChild) || (label == p.label && lChild == p.lChild && rChild < p.rChild) ) ;
        
    }
    
    ~DAG_Node(){
        //Write Code Here
    }
};



int currIndex=1; // Current entry in dag_array will be at currIndex
DAG_Node dag_array[1000]; // Start from index 1
map<DAG_Node , int> node_table;

int constructNode(string label, int l, int r){
	
	DAG_Node d(label , l , r);
	if(node_table[d]) return node_table[d];
	else{
		node_table[d] = currIndex;
		dag_array[ currIndex ] = d;
		currIndex++ ;
		return node_table[d];
	}
	
}

void print_dag_array(){

	fout << "DAG ARRAY\n\n";
	for(int i = 1 ; i < currIndex; i++) 
		fout << i<<" --> " << dag_array[i].getLabel() << ' ' <<  dag_array[i].getLChild() << ' ' << dag_array[i].getRChild() << "\n";
	fout << "\n\n";
}

bool vis[1000];
vector< int > tac_order;
int lcount = 1;

string to_string( int x){
	string s = "";
	while(x){
		s = ((char)((x%10) + '0')) + s ; x/=10;
	}
	
	if(s.length() == 0) s = s + '0';
	return s;
}


void topological_sort(int u){
	vis[ u ] = true;
	int v1 = dag_array[u].getLChild() , v2 = dag_array[u].getRChild() ;
	if(!vis[v1]) topological_sort(v1);
	if(!vis[v2]) topological_sort(v2);
	if(dag_array[u].getLChild()){
		tac_order.push_back(u);
		dag_array[u].setTempLabel("t" + to_string(lcount));
		lcount++;
	}
}

void construct_tac(){
	for(int i = 1 ; i < currIndex; i++)
		if(!vis[i]) topological_sort(i);
		
	fout << "THREE ADDRESS CODE\n\n";

	
	for(int i = 0 ; i < tac_order.size(); i++){
		string lop = (dag_array[ dag_array[tac_order[i]].getLChild() ].getLChild() ?  dag_array[ dag_array[tac_order[i]].getLChild() ].getTempLabel() : dag_array[ dag_array[tac_order[i]].getLChild() ].getLabel() );    
		string rop = (dag_array[ dag_array[tac_order[i]].getRChild() ].getRChild() ?  dag_array[ dag_array[tac_order[i]].getRChild() ].getTempLabel() : dag_array[ dag_array[tac_order[i]].getRChild() ].getLabel() );    
		fout << dag_array[tac_order[i]].getTempLabel()<<" = " << lop << " "<< dag_array[tac_order[i]].getLabel() << " " << rop << endl; 
	}
}




#endif
