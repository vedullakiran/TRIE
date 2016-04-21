#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#define f first
#define s second
#define pb push_back
#define SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

using namespace std;

struct node{
        struct node* alphabet[SIZE];
        bool isSafe;
};

class Trie{
	protected:
                struct node* root;
         public:
                Trie()
                {
                	cout<<"In the Trei Class\n";
                	root=getNode();
                }
                struct node* getNode();
                void insert_trie(string);
                bool search_trie(string);
};
        
struct node* Trie::getNode()                    //returns a Trie structure node of type node
{
        struct node* pNode=NULL;
        pNode=(node*)malloc(sizeof(node));
        if(pNode)
        {
        	for(int i=0; i<SIZE; i++)
                	pNode->alphabet[i]=NULL;
        	pNode->isSafe=false;
        }
        return pNode;
}


void Trie::insert_trie(string s)
{
	int i=0;
	node* pNode=root;
	for(i=0; s[i]!='\0'; i++)
	{
		int num=s[i]-'a';
		if(pNode->alphabet[num]==NULL)
			pNode->alphabet[num]=getNode();
		pNode=pNode->alphabet[num];
	}
	pNode->isSafe=true;
}


bool Trie::search_trie(string s)                  //Search the Trie structure for given word
{
	int i=0;
	node* pNode=root;
	for(i=0; s[i]!='\0'; i++)
	{
		int num=s[i]-'a';
		if(pNode->alphabet[num]==NULL)
			return false;
		pNode=pNode->alphabet[num];
	}
	return (pNode && pNode->isSafe);
}

class find_permutations{
     		vector<pair<char, int> > v;
     	protected:
		set<string> distinct_string;
	public:	
		void swap(string &, int, int);
		void find_all_permutations(string, int);
		void create_string(int);
		void write_into_file();
		void accept_table();
		bool search_naive();
		void Naive();
};

void find_permutations::accept_table()
{
	int n=0;
	pair<char, int> temp;
	cout<<"Enter the character and its count in Array or '#' for exit\n";
	while(1)
	{
		cin>>temp.f;
		if(temp.f=='#')
			break;
		cin>>temp.s;
		n+=temp.s;
		v.pb(temp);
	}
	create_string(n);
	
}

void find_permutations::swap(string &s, int i, int k)
{
	char temp=s[i];
	s[i]=s[k];
	s[k]=temp;
}

void find_permutations::find_all_permutations(string s, int l)
{
	if(s.length()==l)
	{
		if(distinct_string.find(s)==distinct_string.end())
			distinct_string.insert(s);	
		return;
	}
	for(int i=l; i<s.length(); i++)
	{
		swap(s, i, l);
		find_all_permutations(s, l+1);
		swap(s, i, l);		
	}
}


void find_permutations::create_string(int n)
{
	char* s=(char *)malloc(n*sizeof(char));
	int k=0;
	for(int i=0; i<v.size(); i++)
	{
		while(v[i].s--)
			s[k++]=v[i].f;
	}
	s[k]='\0';
	string str(s);
	find_all_permutations(str, 0);
}

void find_permutations::write_into_file()
{
	set<string>::iterator it;
	fstream fout("uniquewords.txt",ios::out);
	//fout.open("uniquewords.txt");
	for(it=distinct_string.begin(); it!=distinct_string.end(); ++it)
		fout<<*it<<endl;
	fout.close();
}

class file_operations: public Trie, public find_permutations{
	public:
		file_operations() : Trie(){};
		void create_trie();
		void other_operations();
		void trie_search();
		void bruteforce_search();
		bool search_naive(string);
		void Naive();
};

bool file_operations::search_naive(string s)
{
	ifstream file;
	file.open("Words.txt");
	string word;
	while(!file.eof())
	{
		file>>word;
		if(word.compare(s)==0)
			return true;
	}
	file.close();
	return false;
}

void file_operations::other_operations()
{
	accept_table();
	write_into_file();
}

void file_operations::create_trie()                           // read all the alphabets from Words.txt file and creates a Trie structure
{
        ifstream file;
        file.open("Words.txt");
        if(!file.is_open()) 
        {       
                cout<<"File could not be opened\n";
                return;
        }
        
        while(!file.eof())
        {
                string word;
                file>>word;
                insert_trie(word);
        }
        file.close();
}

void file_operations::trie_search()
{
	ifstream fin;
	fin.open("uniquewords.txt");
	string word;
	int count=0;
	while(!fin.eof())
	{
		fin>>word;
		if(search_trie(word))
			count++;
	}
	cout<<"Numbers of Matched\n";
	cout<<count<<endl;
	fin.close();
}

void file_operations::Naive()
{
	ifstream fin;
	fin.open("uniquewords.txt");
	int count=0;
	string word;
	while(!fin.eof())
	{
		fin>>word;
		if(search_naive(word))
			count++;
	}
	remove("uniquewords.txt");
	cout<<"Numbers of Matched\n";
	cout<<count<<endl;
}

int main()
{
	file_operations F;
	F.create_trie();
	F.other_operations();
	clock_t t=clock();
	F.trie_search();
	cout<<(double)(clock()-t)<<endl;
	cout<<"Want to know the time with Naive method(Y/N)\n";
	char ch;
	cin>>ch;
	if(!(ch=='y' || ch=='Y'))
		return 0;
	
	t=clock();
	F.Naive();
	cout<<(double)(clock()-t)<<endl;
	
}


