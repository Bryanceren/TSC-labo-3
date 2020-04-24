#include <fstream>

void obtenerDatos(istream &file,int nlines,int n,int mode,item* item_list){
    string line;
    file >> line;
    
    if(nlines==DOUBLELINE) 
      file >> line;
   
   for(int i=0;i<n;i++){
        switch(mode){
        case INT_FLOAT:
            int e; float r;
            file >> e >> r;
            item_list[i].setIntFloat(e,r);
            break;
        case INT_INT_INT:
            int e1,e2,e3;
            file >> e1 >> e2 >> e3;
            item_list[i].setIntIntInt(e1,e2,e3);
            break;
        }
    }
}

void leerMallayCondiciones(mesh &m){
    char filename[10];
    ifstream file;
    float A,B,Q;
    int nnodes,neltos,ndirich,nneu;

  do{
     file.open("problem.msh");
    }while(!file);

    file >> A >> B >> Q;
    file >> nnodes >> neltos >> ndirich >> nneu;

    m.setParameters(A,B,-1 * Q);
    m.setSizes(nnodes,neltos,ndirich,nneu);
    m.createData();

    obtenerDatos(file,SINGLELINE,nnodes,INT_FLOAT,m.getNodes());
    obtenerDatos(file,DOUBLELINE,neltos,INT_INT_INT,m.getElements());
    obtenerDatos(file,DOUBLELINE,ndirich,INT_FLOAT,m.getDirichlet());
    obtenerDatos(file,DOUBLELINE,nneu,INT_FLOAT,m.getNeumann());

    file.close();
}


