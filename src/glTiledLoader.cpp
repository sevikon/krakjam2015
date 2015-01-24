#include "glTiledLoader.h"
#include <iostream>
#include <fstream>
#include <iostream>     // std::cout
#include <sstream>
#include <string>
#include <vector>

using namespace std;

glTiledLoader::glTiledLoader()
{

}

void glTiledLoader::loadMap(int number){
	ostringstream ss2;
	ss2 << number;
	string str = ss2.str();
	string line;

	int N = WIDTH;
	int M = HEIGHT;

	  int** ary = new int*[N];
	  for(int i = 0; i < N; ++i)
		  ary[i] = new int[M];

  std::string a ("assets/maps/");
  std::string b (".txt");
  std::string path;
  path = a+str+b;
  ifstream myfile (path);
  std::stringstream ss;
  if (myfile.is_open())
  {
	int iterator=0,iterator2=0; 
    while ( getline (myfile,line) )
    {
		std::string s = line;
		std::string delimiter = ",";

		size_t pos = 0;
		std::string token;
		iterator2=0;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			ary[iterator][iterator2]=atoi( token.c_str() ); 
			iterator2++;

			s.erase(0, pos + delimiter.length());
		}
		iterator++;
    }
    myfile.close();


	vector<vector<int> > items;
	vec = items;

	for ( int i = 0; i < WIDTH; i++ ) {
		vec.push_back ( vector<int>() );
		for ( int j = 0; j < HEIGHT; j++ )
			vec[i].push_back (ary[i][j]);
	}

  }
  else {
	cout << "Unable to open file"; 
  }
   

}

bool glTiledLoader::isLadder(int x,int y){

	if (vec[x][y]==2){
		return true;
	}
	return false;
}

bool glTiledLoader::isWall(int x,int y){

	if (vec[x][y]==1){
		return true;
	}
	return false;
}

bool glTiledLoader::isFree(int x,int y){

	if (vec[x][y]==0){
		return true;
	}
	return false;
}

int glTiledLoader::getValue(int x,int y){

	return vec[x][y];
}