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

		string input = argv[1];
		string ans = argv[2] ;
		fstream fin(input) , fans(ans);
		map<string,int> mp;
		string tmp_string ; 
		while( fin >> tmp_string)
		{
				// pretreat the url to unify the URL
				auto &s = tmp_string;
				transform(s.begin(),s.end(), s.begin(),::tolower);
				if( s.substr( 0 , 4 ).find("http") != string::npos)
						s.erase(0,5);
				while( s[0] == '/' || s[0] == ':'  )
						s.erase(s.begin());
				if( s.substr(0,4).find("www.") != string::npos)
						s.erase(0,4);
				if( s[s.size()-1] != '/')
						s.push_back('/');
				mp[tmp_string]++;
		}
		int last = 0x3f3f3f3f;
		int tmp_cnt;
		while( fans >> tmp_string >> tmp_cnt  )
		{
				if( !(tmp_cnt <= last ) )
						return -1;
				if( tmp_cnt != mp[tmp_string] )
						return -1;
				last = tmp_cnt;
		}
		return 0 ;
}
