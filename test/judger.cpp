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
		ifstream fin,fans;
		fin.open(input);
		fans.open(ans);
		map<string,int> mp;
		string tmp_string ; 
		while( fin >> tmp_string)
		{
				// pretreat the url to unify the URL
				transform(tmp_string.begin(),tmp_string.end(), tmp_string.begin(),::tolower);
				if( tmp_string.substr( 0 , 4 ).find("http") != string::npos)
						tmp_string.erase(0,5);
				while( tmp_string[0] == '/' || tmp_string[0] == ':'  )
						tmp_string.erase(tmp_string.begin());
				if( tmp_string.substr(0,4).find("www.") != string::npos)
						tmp_string.erase(0,4);
				if( tmp_string[tmp_string.size()-1] != '/')
						tmp_string.push_back('/');
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
