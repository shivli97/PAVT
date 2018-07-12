#pragma once
#include<fstream>
#include<string.h>
#include<map>
#include<string>
#include<list>
#include<vector>
#include<iomanip>
#include<stdlib.h>
#include<stack>
#include<set>
#include<algorithm>

using namespace std;
#define for1(i,a,b) for(i=a;i<b; i++)
#define ASSERTMSG(TST,MSG) ( (TST) ? (void)0 : (cerr << MSG << endl,abort()))
#define N 100

string arr1[N][N], dpr[N], matrix[N][N], str;
map <char, int> voc;
map <char, int> ::iterator fu;
bool an1[26][N];
int p4, np;

inline string concat(string a, string b)	//concatenates unique non-terminals
{
	int i;
	string r = a;
	for1(i, 0, b.length())
		if (r.find(b[i]) > r.length())
			r += b[i];
	return (r);
}

inline void deconc(string a)	//seperates right hand side of entered grammar
{
	int i;
	p4 = 0;
	while (a.length())
	{
		i = a.find("|");
		if (i>a.length())
		{
			dpr[p4++] = a;
			a = "";
		}
		else
		{
			dpr[p4++] = a.substr(0, i);
			a = a.substr(i + 1, a.length());
		}
	}
}

inline int lchomsky(string a)	//checks if LHS of entered grammar is in CNF
{
	if (a.length() == 1 && a[0] >= 'A' && a[0] <= 'Z')
		return 1;
	return 0;
}

inline int rchomsky(string a)	//checks if RHS of grammar is in CNF
{
	if (a.length() == 1 && a[0] >= 'a' && a[0] <= 'z')
		return 1;
	if (a.length() == 2 && a[0] >= 'A' && a[0] <= 'Z' && a[1] >= 'A' && a[1] <= 'Z')
		return 1;
	return 0;
}
ofstream mout_4;

/*head->body*/
struct prod_4 
{
	char head;
	string body;
};

/*Array to store grammar*/
prod_4 *arr_4 = new prod_4[N];
int siz_4;

int ar_4[10] = { 1,1,1,1,1,1,1,1,1,1 };

inline string search_prod(string p4, int l) //returns a concatenated string of variables which can produce string p4
{
	int j, k;
	string r = "";
	for1(j, 0, np)
	{
		k = 1;
		while (arr1[j][k] != "")
		{
			if (arr1[j][k] == p4)
			{
				r = concat(r, arr1[j][0]);
				an1[voc[arr1[j][0][0]]][l] = 1;
			}

			k++;
		}
	}
	return r;
}

inline string gen_comb(string a, string b, int l) //creates every combination of variables from a and b . For eg: BA * AB = {BA, BB, AA, BB}
{
	int i, j;
	string pri = a, re = "";
	for1(i, 0, a.length())
		for1(j, 0, b.length())
	{
		pri = "";
		pri = pri + a[i] + b[j];

		re = re + search_prod(pri, l);	//searches if the generated productions can be created or not
	}
	return re;
}
map<char, int> extra;
map<char, int> ::reverse_iterator it;

void remove_long()
{
	int i;
	prod_4 *temp_4 = new prod_4[N];
	//temp_4=arr_4;
	int j = 0, k = 0;
	for (i = 0; i<np; i++)
	{
		int ex = k, c1 = 0, flag = 0;
		k++;
		if (arr_4[i].body.size()>1)
			for (j = 0; j<arr_4[i].body.size(); j++)
			{  // cout<<"hi "<<i<<" "<<j<<endl;
				if (!(arr_4[i].body[j] >= 'A'&&arr_4[i].body[j] <= 'Z') && arr_4[i].body[j] != '~')
				{  // cout<<arr_4[i].body[j]<<" ";
					it = extra.rbegin();
					//cout<<it->first<<endl;
					flag = 1;
					char sym = arr_4[i].body[j];
					arr_4[i].body[j] = it->first;
					temp_4[ex] = arr_4[i];
					//k++;
					//cout<<ex<<endl;
					c1++;
					temp_4[k].head = it->first;
					temp_4[k].body.push_back(sym);
					k++;
					// itz=m.end();
					extra.erase(--(it.base()));
					// cout<<extra.size()<<" ";
					//cout<<"hi "<<i<<" "<<j<<endl;
				}
			}
		if (flag == 0)
		{
			temp_4[ex] = arr_4[i];
		}
	}

	np = k;
	arr_4 = temp_4;
	//for(i=0;i<np;i++)
	//cout<<arr_4[i].head<<" "<<arr_4[i].body<<endl;
	//cout<<"finish"<<endl;
	j = 0;
	prod_4 *temp1 = new prod_4[N];
	for (i = 0; i<np; i++)
	{
		if (arr_4[i].body.size()>2)
		{ //n1=arr_4[i].body.size())
			while (arr_4[i].body.size()>2)
			{
				it = extra.rbegin();
				// cout<<it->first<<endl;
				temp1[j].head = arr_4[i].head;
				temp1[j].body = arr_4[i].body[0];
				temp1[j].body.push_back(it->first);
				//cout<<temp1[j].head<<" "<<temp1[j].body<<endl;
				//cout<<arr_4[i].body.substr(0)<<endl;
				arr_4[i].head = it->first;
				arr_4[i].body = arr_4[i].body.substr(1);
				//cout<<temp1[j+1].head<<" "<<temp1[j+1].body<<endl;
				j++;

				extra.erase(--(it.base()));
			}
		}

		temp1[j].head = arr_4[i].head;
		temp1[j].body = arr_4[i].body;
		j++;

	}
	arr_4 = temp1;
	np = j;
	//for(i=0;i<np;i++)
	//cout<<temp1[i].head<<" "<<temp1[i].body<<endl;
	//cout<<"finish long\n";
}
bool mo_4[100];
void remove_empty()
{
	int i;
	prod_4 *temp_4 = new prod_4[N];

	int j = 0;
	// mo_4.clear();
	for (i = 0; i<np; i++)
	{
		if (arr_4[i].body[0] == '~')
		{
			mo_4[arr_4[i].head] = 1;
			//cout<<arr_4[i].head<<endl;
		}
		else
		{
			temp_4[j] = arr_4[i];
			j++;
		}
	}
	int siz_4 = np;
	while (siz_4--)
	{

		for (i = 0; i<j; i++)
		{
			int x = 0;
			for (int z = 0; z<temp_4[i].body.size(); z++)
			{
				if (mo_4[temp_4[i].body[z]] == 1)
					x++;
			}
			if (x == temp_4[i].body.size())
			{
				mo_4[temp_4[i].head] = 1;
			}
		}
	}
	prod_4 *temp1 = new prod_4[N];

	int k = 0, siz1;
	for (i = 0; i<j; i++)
	{
		if (temp_4[i].body.size() == 2)
		{// n1=2;
			temp1[k] = temp_4[i]; k++;
			if (mo_4[temp_4[i].body[0]])
			{   //n1--;
				// it=extra.begin();

				//cout<<"hi "<<temp_4[i].head<<" "<<temp_4[i].body[0]<<endl;
				string str = temp_4[i].body.substr(1);
				/*if(m.find(temp_4[i].body[0])!=m.end())
				{

				}
				else {*/
				temp1[k].head = temp_4[i].head;
				temp1[k].body = str; k++;
				// }
				//extra.erase(it);
			}
			//else
			if (mo_4[temp_4[i].body[1]])
			{
				//it=extra.begin();
				//temp_4[i].body[1]='\0';
				//cout<<"hi "<<temp_4[i].head<<" "<<temp_4[i].body<<endl;

				temp_4[i].body.erase(1);
				temp1[k] = temp_4[i]; k++;
				//extra.erase(it);
			}
			/*else
			{
			temp1[k]=temp_4[i]; k++;
			}*/
		}
		else
		{
			temp1[k] = temp_4[i]; k++;
		}
	}
	arr_4 = temp1;
	np = k;
	//for(i=0;i<np;i++)
	//cout<<temp1[i].body.size()<<" "<<temp1[i].head<<" "<<temp1[i].body<<endl;
	//cout<<"finish empty\n";
}
map<char, set<char> > d;
bool vis[150];
void remove_short()
{
	map<char, int> mi;
	map<char, int> ::iterator it1;
	int i;
	set<char> ::iterator itk;
	set<char> ::iterator itl;
	for (i = 0; i<26; i++)
		if (!extra[(char)('A' + i)])
			mi[(char)('A' + i)] = 1;
	for (it1 = mi.begin(); it1 != mi.end(); it1++)
	{
		d[it1->first].insert(it1->first);
		//cout<<it1->first<<"   ";
		int prev = 1, nx = 1;
		bool vis[100];
		memset(vis, 0, sizeof(vis));
		while (1)
		{
			for (i = 0; i<np; i++)
			{
				if (arr_4[i].body.size() == 1 && d[it1->first].find(arr_4[i].head) != d[it1->first].end() && arr_4[i].body[0] >= 'A'&&arr_4[i].body[0] <= 'Z')
				{
					d[it1->first].insert(arr_4[i].body[0]);
					prev = nx; nx++;
					//cout<<arr_4[i].body[0]<<" ";
					vis[arr_4[i].body[0]] = 1;
				}
			}
			bool flag = 0;
			for (i = 0; i<np; i++)
				if (arr_4[i].body.size() == 1 && d[it1->first].find(arr_4[i].head) != d[it1->first].end() && (arr_4[i].body[0] >= 'A'&&arr_4[i].body[0] <= 'Z') && !vis[arr_4[i].body[0]])
				{
					flag = 1; break;
				}//{ prev=nx; break; }
			if (!flag)
			{
				for (i = 0; i<np; i++)
					if (d[it1->first].find(arr_4[i].head) != d[it1->first].end() && (!(arr_4[i].body[0] >= 'A'&&arr_4[i].body[0] <= 'Z') || mo_4[arr_4[i].body[0]] || arr_4[i].body.size()>1))
					{
						prev = nx; break;
					}
				if (prev == nx) break;
			}
		}
	}
	prod_4 *temp_4 = new prod_4[N];
	int j = 0;

	int z = 0;
	temp_4 = arr_4;
	prod_4 *temp1 = new prod_4[N];
	j = 0; int cnt1 = 0, k = 0;
	set<char> ::iterator it3, it4;
	for (i = 0; i<np; i++)
	{
		if (!vis[temp_4[i].head])
		{
			vis[temp_4[i].head] = 1;
			for (it3 = d[temp_4[i].head].begin(); it3 != d[temp_4[i].head].end(); it3++)
			{
				for (j = 0; j<np; j++)
				{
					if (temp_4[j].head == *it3 && !(temp_4[j].body.size() == 1 && temp_4[j].body[0] >= 'A'&&temp_4[j].body[0] <= 'Z'))
					{
						temp1[k].head = temp_4[i].head;
						temp1[k].body = temp_4[j].body;
						//cout<<temp_4[j].body.size()<<" "<<temp1[k].head<<" "<<temp1[k].body<<endl;
						k++;
					}
				}
			}
		}
	}
	
	arr_4 = temp1;
	np = k;
}

void cyk()
{
	/*
	---------------------------------------------------------STEP I: INPUT GRAMMAR--------------------------------------------------------------------------
	*/
	/*
	No blank lines in b/w. Each production in a separate line.
	A->~ == A->epsilon
	*/
	string s;
	string a, r, pr, start;
	int pt;
	ifstream myfile("grammar.txt");
	int j, k, l, i = 0;
	for (i = 0; i<26; i++)
		extra[(char)('A' + i)] = 1;
	//for(i=0;i<26;i++)
	// extra[(char)('a'+i)]=1;
	i = 0;
	// extra.erase('e');

	while (!myfile.eof())
	{
		getline(myfile, s);
		if (i == 0)
		{
			arr_4[i].head = 'Z';
			arr_4[i].body = s[0];
			extra.erase('Z');
			i++;
		}
		arr_4[i].head = s[0];

		extra.erase(arr_4[i].head);

		int len = s.length();

		/*Allows extra line at the end*/
		// if(len>maxLenP) maxLenP = len;
		if (len == 0)
			break;
		arr_4[i].body = s.substr(3);
		int n1 = arr_4[i].body.size();

		for (int j = 0; j<n1; j++)
			extra.erase(arr_4[i].body[j]);
		//i++;
		pt = s.find("->");
		arr1[i][0] = s.substr(0, pt);
		//cout<<arr1[i][0]<<"->";
		//ASSERTMSG(lchomsky(arr1[i][0]),"\nGrammar not in Chomsky Form");
		//cout<<arr_4[i].head<<" "<<arr_4[i].body<<endl;
		s = s.substr(pt + 2, s.length());
		deconc(s);
		//cout<<p<<" ";
		for1(j, 0, p4)
		{
			arr1[i][j + 1] = dpr[j];
			//cout<<arr1[i][j+1]<<" ";
			// ASSERTMSG(rchomsky(dpr[j]),"\nGrammar not in Chomsky Form");
		}
		// cout<<endl;
		i++;
	}
	myfile.close();
	/* # Productions*/
	siz_4 = i;  np = i;
	remove_long();
	//cout<<"hi1\n";
	remove_empty();
	remove_short();
	//j=1;
	start.push_back('Z');
	for (i = 0; i<np; i++)
	{
		arr1[i][0] = arr_4[i].head;
		arr1[i][1] = arr_4[i].body;
	}
	mout_4.open("output.txt");
	mout_4 << "-------------------Grammar in CNF------------------------\n\n";
	for (i = 0; i<np; i++)
	{
		mout_4 << i + 1 << "." << " " << arr_4[i].head << "->" << arr_4[i].body << endl;
	}
	mout_4 << endl;
	string st1;

	myfile.open("details.txt");
	getline(myfile, str);
	myfile.close();
	mout_4 << "-------------------Boolean matrices----------------------\n\n";
	j = 0;

	for (i = 0; i<np; i++)
	{
		if (!voc[arr_4[i].head])
		{
			voc[arr_4[i].head] = j;
			j++;
		}
	}
	bool ans[26][100];
	memset(ans, 0, sizeof(ans));
	for1(i, 0, str.length())	//Assigns values to principal diagonal of matrix
	{
		r = "";
		st1 = "";
		st1 += str[i];

		for1(j, 0, np)
		{
			k = 1;
			while (arr1[j][k] != "")
			{
				//cout<<arr1[j][k]<<" ";
				if (arr1[j][k] == st1)
				{
					r = concat(r, arr1[j][0]);
					ans[voc[arr1[j][0][0]]][i] = 1;
				}
				k++;
			}
		}
		matrix[i][i] = r;

	}
	mout_4 << "   Substring length: 1\n\n";
	mout_4 << "   ";
	for (i = 0; i<str.length(); i++)
	{
		mout_4 << str[i] << "  ";
	}
	mout_4 << endl;
	for (fu = voc.begin(); fu != voc.end(); fu++)
	{
		mout_4 << fu->first << "  ";
		for (j = 0; j<str.length(); j++)
			mout_4 << ans[fu->second][j] << "  ";
		mout_4 << endl;
	}
	mout_4 << endl;
	int ii, kk, nin, non = 0, diff = str.length() - 1;

	
	int max1 = 0, in, on;
	for1(k, 1, str.length())	//Assigns values to upper half of the matrix
	{
		mout_4 << "Substring length: " << k + 1 << endl << endl;
		mout_4 << "   ";
		//cout<<"  ";
		for (i = 0; i<str.length(); i++)
		{
			mout_4 << str[i] << "  ";
		}//cout<<str[i]<<" ";
		 //cout<<endl;
		mout_4 << endl;
		memset(an1, 0, sizeof(an1));
		for1(j, k, str.length())
		{
			r = "";
			for1(l, j - k, j) // for
			{
				int l1 = j - k;
				pr = gen_comb(matrix[j - k][l], matrix[l + 1][j], l1);
				//cout<<pr<<endl;
				//an[voc[pr[0]-'A']][j-k]=1;
				r = concat(r, pr);
			}
			matrix[j - k][j] = r;
			int n1 = r.size();
			max1 = max(max1, n1);
		}
		for (fu = voc.begin(); fu != voc.end(); fu++)
		{
			mout_4 << fu->first << "  ";
			for (j = 0; j<str.length(); j++)
				mout_4 << an1[fu->second][j] << "  ";
			mout_4 << endl;
		}
		mout_4 << endl;
	}

	//cout<<"\nMatrix Generated :- "<<endl;
	mout_4 << endl;
	mout_4 << "-------------------2D Representation---------------------\n" << endl;
	diff = str.length();
	while (diff + 1)
	{
		if (diff<str.length())
		{
			mout_4 << diff + 1;
			if (diff + 1<10)mout_4 << "  ";
			else mout_4 << " ";
		}
		// cout<<diff+1<<" ";
		for (nin = 0; nin<str.length() - diff; nin++)
		{
			mout_4 << setw(max(5, max1 + 2)) << matrix[nin][nin + diff] << " ";
		}
		mout_4 << endl;
		//cout<<endl;
		diff--;
	}
	//mout_4<<endl;
	mout_4 << "   ";
	for (i = 0; i<str.length(); i++)
	{
		mout_4 << setw(max(5, max1 + 2)) << str[i] << " ";
	}
	mout_4 << endl;
	mout_4 << endl;

	int f = 0;
	bool check = 0;

	for1(i, 0, start.length())
		if (matrix[0][str.length() - 1].find(start[i]) <= matrix[0][str.length() - 1].length()) //Checks if last element of first row contains a Start variable
		{
			//cout<<"String can be generated\n";'
			check = 1;
			//mout_4 << "\nAccepted\n";
			break;
		}

	if (check == 0)
		mout_4 << "\nSyntax Error\n";
	else
		mout_4 << "\nAccepted\n";
	mout_4.close();

}

