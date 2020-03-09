#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
using namespace std;
struct player_recode
{
	string name;
	double score;
};

vector<string> removeDupWord(string str) 
{ 
	vector<string> words;
   string word = ""; 
   for (auto x : str) 
   { 
       if (x == ' ') 
       { 
           words.push_back( word ); 
           word = ""; 
       } 
       else
       { 
           word = word + x; 
       } 
   }  
   words.push_back(word); 
   return words;
}

int main()
{
	ifstream fin;
	string line;
	vector<player_recode> Recode;
	vector<player_recode> separate;
	vector<int> arr;
	fin.open("filename.txt");
	vector<string> words;
	string new_str="";
	if(fin.is_open())
	{
	 while(getline(fin,line))
	 {
		 new_str="";
		 words=removeDupWord(line);
		 for(size_t i=0;i < words.size()-1;i++)
		 {
			 if(i>0){
				 new_str+=" ";
				 new_str+=words[i];
			 }
			 else
			 {
		        new_str+=words[i];
			 }
		 }

	  player_recode new1;
	  new1.name=new_str;
	  new1.score=std::stod(words[words.size()-1]);
	  Recode.push_back(new1);
	 }
	}
	else
	{
	cout<<"File is not open"<<endl;
	}
	string str1,str2;
//	int m=0;
//	while(m<25)
//	{
	cout<<"Enter the Name of Player : ";
	getline(cin,new_str);
	cout<<"Enter the Score of Player : ";
	getline(cin,str1);
	player_recode new2;
	new2.name=new_str;
	new2.score=stod(str1);
	Recode.push_back(new2);
	separate.push_back(new2);
	/*cout<<"Enter n to END the add new Player y to continue"<<endl;
	getline(cin,str2);
	if(str2=="n")
	{
	break;
	}
	m++;
	}*/
	double temp=0;
	string temp1="";
	for(size_t i=0;i<Recode.size();i++)
	{		
		for(size_t j=i+1;j<Recode.size();j++)
		{
			if(Recode[i].score<Recode[j].score)
			{
				temp  =Recode[i].score;
				temp1=Recode[i].name;
				Recode[i].score=Recode[j].score;
				Recode[i].name=Recode[j].name;
				Recode[j].score=temp;
				Recode[j].name=temp1;
			}
		}
	}
	
	for(size_t i=0;i<separate.size();i++)
	{
	  for(size_t j=0;j<Recode.size();j++)
	  { 
	    if(separate[i].name==Recode[j].name  && separate[i].score==Recode[j].score)
		{
		   arr.push_back(j);
		   break;
		}

	  }
	}
	for(size_t i=0;i<Recode.size() && i<10;i++)
	{
	  cout<<Recode[i].name<< "  " << Recode[i].score<<endl;
	}
	cout<<"You are "<<arr[0]+1<<"  position in the LeaderBoard"<<endl;


system("pause");
}
