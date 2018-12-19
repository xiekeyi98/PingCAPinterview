/**********************************************************
 * Author        : xie keyi
 * Email         : xiekeyi98@snnu.edu.cn
 * Last modified : 2018-12-18 16:16
 * Filename      : main.cpp
 * Description   : 
 * *******************************************************/
#include<bits/stdc++.h>
using namespace std;


void input( const string &filename , vector<string> *data);
void solve( vector<string> *data );

int main(int argc , char **argv)
{
		if( argc <= 1 )
		{
				cerr << "Please select INPUT file" << endl ;
				exit(-1);
		}

		string 	filename = argv[1];
		auto *data = new vector<string> ; 
		// input file;
		input(filename , data);
		solve(data);
		delete data;
}


void input( const string &filename , vector<string> *data)
{
		fstream fin;
		fin.open(filename);
		if( !fin.is_open() )
		{
				cerr << "Input file open failed" << endl ;
				exit(-1);
		}
		string s;
		while( fin >> s )
		{
				// pretreat the url to unify the URL
				transform(s.begin(),s.end(), s.begin(),::tolower);
				if( s.substr( 0 , 4 ).find("http") != string::npos)
						s.erase(0,5);
				while( s[0] == '/' || s[0] == ':'  )
						s.erase(s.begin());
				if( s.substr(0,4).find("www.") != string::npos)
						s.erase(0,4);
				if( s[s.size()-1] != '/')
						s.push_back('/');
				data->push_back(s);
		}
}

void solve( vector<string> *data )
{
		auto *mp = new map<string,int>;
		// use map to mapping <url,occurrence number> 
		for( auto i : *data )
				((*mp)[i])++;
		auto *ans = new vector< pair<string,int> > ;
		// save the result and sort by occurrence number 
		for( auto i : *mp )
				ans->push_back(make_pair(i.first,i.second));
		sort( ans->begin() , ans->end() , [](const pair<string,int> &a , const pair<string,int> &b)
						{
						return a.second > b.second;
						}
			);
		delete mp ;
		// output the num 
		for( int i = 0 ; i <= 100 && i < ans->size() ; i++)
				cout << ans->at(i).first << ' ' << ans->at(i).second << endl ;
		delete ans ;
}
