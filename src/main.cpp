/**********************************************************
 * Author        : xie keyi
 * Email         : xiekeyi98@snnu.edu.cn
 * Last modified : 2018-12-19 21:39
 * Filename      : main.cpp * Description   : 
 * *******************************************************/
#include<bits/stdc++.h>
using namespace std;


int input( const string &filename);
void output( const int max_size ) ;

int main(int argc , char **argv)
{
		if( argc <= 1 )
		{
				cerr << "Please select INPUT file" << endl ;
				exit(-1);
		}

		string 	filename = argv[1];
		system("rm --force  tmp/*");
		system("mkdir -p tmp");
		// input file;
		int max_file = 	input(filename);
		output(max_file);
		system("rm -rf tmp/");
}

unsigned long long has( const string &s )
{
		const unsigned long long BASE = 1000000000ull + 7ull;
		unsigned long long ans = 0 ; 
		for( int i = 0 ; i < s.size() ; i++)
				ans = ans * BASE + s[i];
		return ans;
}

int input( const string &filename)
{
		int res = 0 ; 
		ifstream fin;
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
				int has_s = has(s) % 500;
				res = max( res , has_s);
				ofstream tmpout;
				tmpout.open(string("./tmp/tmp") + to_string(has_s) + string(".in") , ios::app );
				tmpout << s;
		}
		return res; 
}

void output( const int max_size ) 
{
		string output_name = "./tmp/tmp.in" ; // save all the counts 
		for( int i = 0 ; i <= max_size; i++)
		{
				string input_name = string("./tmp/tmp") + to_string(i) + string(".in") ;
				ifstream fin(input_name);
				if( !fin.is_open() )
						continue;
				string s ;
				map<string,int> mp;
				while( fin >> s )
						mp[s]++;
				ofstream fout(output_name , ios::app);
				for( auto i : mp )
						fout << i.first << ' ' << i.second << endl ;
		}
}

void solve()
{
		ifstream fin("./tmp/tmp.in");
		string s ;
		int cnt ;
		priority_queue< pair<int,string> , vector< pair<int,string> > , greater< pair<int,string> > > pq;
		while( fin >> s >> cnt )
		{
				pq.push(make_pair(cnt,s) );
				while( pq.size() > 100 )
						pq.pop();
		}

		vector<pair<string,int>> ans ;
		while( !pq.empty() )
		{
				ans.push_back( make_pair( pq.top().second , pq.top().first ) ) ;
				pq.pop();
		}
		reverse(ans.begin(),ans.end());
		for( auto i : ans )
				cout << i.first << ' ' << i.second  << endl ;
}
						

