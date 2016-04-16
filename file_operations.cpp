#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <fstream>
#define SIZE 26

using namespace std;
                        
struct node{
        struct node* alphabet[SIZE];
        bool isSafe;
        //int hashnum;
};

class Trie{
                struct node* root;
         public:
                Trie();
                struct node* getNode();
                bool insertString(string);
                void searchDic();
                void readFile();
                void writeFile();
        };
        
Trie::Trie()
{
        root=getNode();
}

void Trie::readFile()                           // read all the alphabets from Words.txt file and creates a Trie structure
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
                insertString(word);
        }
}

void Trie::writeFile()                  //write the new word at the end Words.txt file
{
        ofstream file;
        file.open("Words.txt", ios::app);
        
        if(!file.is_open()) 
        {       
                cout<<"File could not be opened\n";
                return;
        }
        
        string word;
        cout<<"Enter the new Word"<<endl;
        cin>>word;
        if(insertString(word));
                file<<" "<<word;
}

struct node* Trie::getNode()                    //returns a Trie structure node of type node
{
        struct node* pNode=NULL;
        pNode=(node*)malloc(sizeof(node));
        for(int i=0; i<SIZE; i++)
                pNode->alphabet[i]=NULL;
        pNode->isSafe=false;
        return pNode;
}

bool Trie::insertString(string s)               //inserts the given string in Trie structure if it is not already in there
{
        int i=0;
        struct node* pNode=root, *prev;
        while(s[i]!='\0')
        {
                int num=s[i]-'a';
                if(pNode->alphabet[num]==NULL)
                        pNode->alphabet[num]=getNode();
                prev=pNode;
                pNode=pNode->alphabet[num];
                i++;
        }    
        if(prev->isSafe==true)
        {
                cout<<s<<"  is already there in Dictionary\n";
                return false;
        }
        else
                prev->isSafe=true;
        return true;
}

void Trie::searchDic()                  //Search the Trie structure for given word
{
        int i=0;
        string s;
        cout<<"Enter the Word"<<endl;
        cin>>s;
        int flag=0;
        struct node* pNode=root, *prev;
        while(s[i]!='\0')
        {
                int num=s[i]-'a';
                if(pNode->alphabet[num]==NULL)
                {
                        flag=1;
                        break;
                }                
                prev=pNode;
                pNode=pNode->alphabet[num];
                i++;
        }
        if(!flag && prev->isSafe==true)
                cout<<"\n!!!..........The word is present in the DIctionary.........!!!\n";
        else 
                cout<<"\n!!!..........No such Word is present in the Dictionary...........!!!\n";
        return;
}

int main()
{
        Trie obj;
        int ch;
        obj.readFile();
        do{
                cout<<"\nEnter your choice as given"<<endl;
                cout<<"1. Insert new word in Dictionary\n2. Search a word in Dictionary\n(-1 to end)\n"<<endl;
                cin>>ch;
                
                switch(ch)
                {
                        case 1:obj.writeFile();
                                break;
                        case 2:obj.searchDic();
                                break;
                }
        
        }while(ch!=-1);
}
