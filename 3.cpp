#include<sys/types.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include <iostream>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define max 100
using namespace std;
class Student {
	string name;
	string usn;
	string branch;
	int sem;
	string buffer;
        int fdsize; //is used to keep track of the size of the record which will be modified
public :
	void read()
	{
		cin.clear();
		cin.ignore(255,'\n');
		cout<<"enter the name :"<<endl;
		getline(cin,name);
		cout<<"enter the usn :"<<endl;
		cin>>usn;
		cin.clear();
		cin.ignore(255,'\n');
		cout<<"enter the branch :"<<endl;
		getline(cin,branch);
		cout<<"enter the semester :"<<endl;
		cin>>sem;
		cin.clear();
		cin.ignore(255,'\n');
		cout<<endl;
	}
	void show()
	{
		cout<<"Name is :"<<name<<endl;
		cout<<"usn is :"<<usn<<endl;
		cout<<"branch is :"<<branch<<endl;
		cout<<"semester is :"<<sem<<endl<<endl;
	}
	void pack()
	{
		string sem1;
		string temp;
		stringstream out;
		out<<sem;
		sem1=out.str();
		temp=usn+'|'+name+'|'+branch+'|'+sem1+'$';
		cout<<temp<<endl;
		buffer=temp;
	}
	void write()
	{
		fstream fp1;
		fp1.open("data.txt",ios::out|ios::app);
		fp1<<buffer;
		fp1<<endl;
		fp1.close();
	}
	int search(string key)
	{
		fstream fp1;
		string rcvusn;
		fp1.open("data.txt",ios::in);
		while(!fp1.eof())
		{
			getline(fp1,buffer);
			cout<<"record read :"<<buffer<<endl;
			int pos=fp1.tellp();
                        fdsize=buffer.size();
                        cout<<"file record size: "<<fdsize<<endl;
			cout<<"position in file : "<<pos<<endl;
			rcvusn=unpack();
		if(usn==key)
		{
			return pos;
			cout<<"success"<<endl;
		}
		else
		{
			cout<<"not found"<<endl;
		}
		}
		return -1;
	}
	string unpack()
	{
		string s;

			int i=0;
			cout<<endl<<endl;
			usn.erase();
			while(buffer[i]!='|')
			{
				usn+=buffer[i];
				i++;
			}
			i++;
			name.erase();
			while(buffer[i]!='|')
			{
				name+=buffer[i];
				i++;
			}
			i++;
			branch.erase();
			while(buffer[i]!='|')
			{
				branch+=buffer[i];
				i++;
			}
			i++;
			sem=0;
			while(buffer[i]!='$')
			{
				s=buffer[i];
				stringstream convert(s);
				convert>>sem;
				i++;
			}
			cout<<"usn is :"<<usn<<endl;
			cout<<"name is :"<<name<<endl;
			cout<<"branch is :"<<branch<<endl;
			cout<<"sem is :"<<sem<<endl;
			return usn;
	}
	void modify(string key)
	{
		fstream fp1;
		/*cout<<"enter the filename to be modified"<<endl;
		char fln[10];
		cin>>fln;*/
		int choice;
		int pos1=search(key);
		if (pos1 < 0) {
			return;
		}

		cout<<"record modification pos :"<<pos1<<endl;
		cout<<"enter the field to be modified :\n1.Name\n2.USN\n3.branch\n4.sem"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:
			{
				cout<<"Enter the new name :";
				cin>>name;
				cout<<endl;
				pack();
			}
			break;
		case 2:
			{
				cout<<"Enter the new USN :";
				cin>>usn;
				cout<<endl;
				pack();

			}
			break;
		case 3:
			{
				cout<<"Enter the new branch :";
				cin>>branch;
				cout<<endl;
				pack();

			}
			break;
		case 4:
			{
				cout<<"Enter the new sem :";
				cin>>sem;
				cout<<endl;
				pack();
			}
			break;
		default: cout<<"Enter a valid choice"<<endl;
		}
		pos1=pos1-(fdsize+1);
		cout<<"value of pos1:"<<pos1<<endl;
		fp1.open("data.txt");
		fp1.seekp(pos1,ios::beg);
		fp1<<buffer;
		fp1<<endl;
		fp1.close();
	}
//abcd
};

int main() {
	int choice,i=0;
	Student s1;
	while(1)
	{
		cout<<"enter your choice :\n1> insert\n2>search\n3>delete\n4>modify\n5>exit\n----"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:
			{
				while(1)
				{
				s1.read();
				cout<<endl<<"data recorded"<<endl;
				s1.show();
				s1.pack();
				s1.write();
				cout<<"to exit from insert mode press 0 else press any other number to continue"<<endl;
				int a;
				cin>>a;
				if(a==0)
					break;
				}
			}
			break;
		case 2:
			{
				string usn;
				cout<<"enter the usn to search :";
				cin>>usn;
				i=s1.search(usn);
			}
			break;
		case 4:
			{
				string usn;
				cout<<"enter the usn to be modified :";
				cin>>usn;
				s1.modify(usn);
			}
			break;
		case 5:
			{
					exit(0);
			}
			break;
		default :
			{
				cout<<"enter a valid option"<<endl;
			}
		}
	}
	return 0;
}
