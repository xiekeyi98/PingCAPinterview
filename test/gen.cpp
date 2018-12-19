#include<bits/stdc++.h>
using namespace std ;


int main( int argc , char **argv )
{
		string num = argv[1];
		
		long long RequestSize = atoi(num.c_str()) * 1024 * 1024;;
		cout << "Generating " << num << "Mb data" << endl ;
		long long now_size = 0 ;

		srand(time(NULL));
		string head = "https://www.pingcap.com/";
		while( now_size <= RequestSize )
		{
				string t ;
				for( int i = 1 ; i <= rand() % 50 ; i++)
						t += char ( rand() % 26 + 'a');
				cout << head + t << endl ;
				now_size += head.size() + t.size() ;
		}
		return 0 ; 
}




