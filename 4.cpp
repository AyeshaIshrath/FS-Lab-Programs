#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<unistd.h>
#include<sys/types.h>
#include<sstream>
#include<stdlib.h>
#include<fcntl.h>
using namespace std;
vector<int> rrn;
int rsize=0;
class Studentrecord{
    string name;
    string usn;
    string branch;
    int sem;
    string buffer;
    public:
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
        int pack()
        {
          string sem1;
		string temp;
		stringstream out;
		out<<sem;
		sem1=out.str();
		temp=usn+'|'+name+'|'+branch+'|'+sem1+'$';
		cout<<temp<<endl;
		buffer=temp;
               int a=buffer.size();
               return a;
        }
        int write()
	{
		fstream fp1;
		fp1.open("data2.txt",ios::out|ios::app);
		fp1<<buffer;
        int pos=fp1.tellp();
        cout<<"pos:"<<pos<<endl;
        fp1.close();
        int len=buffer.size();
        rrn.push_back(pos-len);
        rsize++;
        cout<<"rsize:"<<rsize<<endl;
        cout<<"content rrn:"<<rrn[rsize-1];
        return pos;
	}
        void search(int recno)
        {
            fstream fp1;
            int a=rrn[recno-1];
            cout<<"urrent record position : "<<a<<endl;
            int b=rrn[recno];
            cout<<"next record position : "<<b<<endl;
            int len=b-a;
            //cout<<"length of the record : "<<endl;
            fp1.open("data2.txt",ios::in);
            fp1.seekp(a,ios::beg);
            getline(fp1,buffer,'$');
            cout<<"Student record is :"<<buffer<<endl;
           // unpack(len);
            fp1.close();
        }
        /*void unpack(int len)
        {
            string s;
            int i=0;
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
            while(i!=len)
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
	    }*/
};
int main()
{
    fstream fp1;
    int choice,rec;
    Studentrecord s;
    while(1)
    {
    cout<<"Enter your choice :\n1) Insert\n2) Search\n3) exit"<<endl;
    cin>>choice;
    switch(choice)
    {
        case 1:
        {
            string s1;
            //fp1.open("data2.txt",ios::out);
            //fp1.seekg(0,ios::beg);
            //fp1<<rsize;
            /*s1=fp1.get();
            cout<<"s1:"<<s1<<endl;*/
            /*stringstream convert(s1);
            convert>>rsize;
            cout<<"initial vlue of rsize :"<<rsize<<endl;
            fp1.close();
            fp1.open("data2.txt");
            fp1.seekp(0,ios::beg);
            fp1<<rsize;
            fp1.close();*/
            s.read();
            int len=s.pack();
            int pos=s.write();
            cout<<"back"<<endl;

            //rrn.push_back(pos-len);

            /*cout<<"rsize is:"<<rsize<<endl;
            for(int i=rsize;i>=0;i--)
                cout<<"element"<<i<<"is : "<<rrn[i]<<endl;
            rsize++;
            cout<<"value of rsize is : "<<rsize<<endl;*/
           // fp1.close();
            /*fp1.open("data2.txt");
            fp1.seekp(0,ios::beg);
            fp1<<rsize;
            fp1.close();*/
        }
        break;
        case 2:
        {
            cout<<"enter the record number to be shown"<<endl;
            cin>>rec;
            s.search(rec);
        }
        break;
        case 3:
        {
        	exit(0);
        }
        break;
        default: cout<<"invalid option chosen"<<endl;
    }
    }
    return 0;
}
