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
#include "slrpvt3.h"

using namespace std;

list<string> produc_5, produc_6;
list<string> ::iterator it7_5, it9;
static list<string> ::iterator it8_5;

/* Formatting output: #include<iomanip> */
ofstream m_3,ma;
const char sep_5 = ' ';
int maxLenP_5 = 0;

/*head->body*/
struct prod_5 {
	char head;
	string body;
};

/*Array to store grammar*/
prod_5 *arr_5 = new prod_5[100];
int size_3, width_5=13;

template<typename T> void format3(T t) {
	m_3 << std::left << setw(width_5) << setfill(sep_5) << t;
}
template<typename T> void format_r3(T t) {
	m_3 << std::right << setw(width_5) << setfill(sep_5) << t;
}
template<typename T> void format_VAR3(const int& wi, T t) {
	m_3 << std::left << setw(wi) << setfill(sep_5) << t;
}

template<typename T> void format_VAR_r3(const int& wi, T t) {
	m_3 << std::right << setw(wi) << setfill(sep_5) << t;
}

void subarray(char a[], int n, char sub[], int r, int i, int j, char temp1[50][50], int &k)
{
	if (j == r) /* current index of sub r, print sub */
	{
		int l;
		//String subarr(sub);
		//for(k = 0; k < r; k++)
		//  m_3<<sub[k];
		for (l = 0; l<r; l++)
		{
			//m_3<<"in function\n";
			temp1[k][l] = sub[l];
		}
		temp1[k][l] = '\0';
		k++;
	}
	else
	{
		if (i < n)
		{
			sub[j] = a[i];

			subarray(a, n, sub, r, i + 1, j + 1, temp1, k); /* Include current element */
			subarray(a, n, sub, r, i + 1, j, temp1, k);     /* Override the current element */
		}
	}

}
int ar_5[10] = { 1,1,1,1,1,1,1,1,1,1 };
void parseTree3(char X, int l)
{	
	int lev = l;
	for (int i = 0; i<10; i++)
	{
		if (lev - 1 >0) {}
		else break;
		if (ar_5[i] == 1) m_3 << "| ";
		else m_3 << "  ";
		lev--;
	}
	if (lev == 1)
		m_3 << "|_";
	else if (lev>0)
	{
		for (int z = 0; z<lev - 1; z++)
			m_3 << "  ";
		m_3 << "|_";
	}
	m_3 << X << endl;
	if (X<'A' || X>'Z')
		return;
	for (it7_5 = it8_5; it7_5 != produc_6.end(); it7_5++) 
	{
		string p = (*it7_5);
		if (p[0] == X) 
		{
			it8_5 = ++it7_5;
			string s = p.substr(3);
			int len = s.length();
			for (int j = 0; j<len; j++) 
			{
				if (len - 1 == j)
					ar_5[l] = 0;
				parseTree3(s[len - 1 - j], l + 1);
				ar_5[l] = 1;
				if (len - 1 != j) {
					int lev = l + 1;
					for (int i = 0; i<10; i++) {
						if (lev >0) {}
						else break;
						if (ar_5[i] == 1) m_3 << "| ";
						else m_3 << "  ";
						lev--;
					}
					m_3 << endl;
				}
			}
			break;
		}
	}
	return;
}

void pred()
{
	/*
	---------------------------------------------------------STEP I: INPUT GRAMMAR--------------------------------------------------------------------------
	*/
	string s;
	produc_5.clear();
	ifstream myfile("grammar.txt");
	int i = 0, j, nt[26];
	m_3.open("output.txt");
	for (int j = 0; j<26; j++)
	{
		nt[j] = 0;
	}
	maxLenP_5 = 0;
	while (!myfile.eof()) 
	{
		getline(myfile, s);
		arr_5[i].head = s[0];
		nt[s[0] - 'A'] = 1;
		int len = s.length();
		//Allows extra line at the end
		if (len>maxLenP_5) maxLenP_5 = len;
		if (len == 0)
			break;
		arr_5[i].body = s.substr(3);
		i++;
	}
	myfile.close();
	/* # Productions*/
	size_3 = i;
	for (j = 0; j<size_3; j++)
	{
		if ((arr_5[j].head == arr_5[j].body[0]) && (arr_5[j].body.length() == 1))
		{
			for (int x = j; x<size_3 - 1; x++)
			{
				arr_5[j].head = arr_5[j + 1].head;
				arr_5[j].body = arr_5[j + 1].body;
			}
			size_3--;
		}
	}


	for (int y = 0; y<size_3 - 1; y++)
	{
		for (int z = y + 1; z<size_3; z++)
		{
			if (arr_5[y].head == arr_5[z].head&&arr_5[y].body == arr_5[z].body)
			{
				for (int k = z; k<size_3 - 1; k++)
				{
					arr_5[k].head = arr_5[k + 1].head;
					arr_5[k].body = arr_5[k + 1].body;
				}
				size_3--;
				z--;
			}
		}
	}


	char c;
	char start = arr_5[0].head;
	int ff = 0;

	int noofprod[26];
	for (int n = 0; n<26; n++)
		noofprod[n] = 0;

	for (i = 0; i<size_3; i++)
	{
		noofprod[arr_5[i].head - 'A']++;
	}

	for (i = 0; i<size_3; i++)
	{

		for (j = 0; j <= i - 1; j += noofprod[arr_5[j].head - 'A'])
		{
			if ((arr_5[i].head != arr_5[j].head) && (arr_5[i].body[0] == arr_5[j].head))
			{
				ff = 1;
				break;
			}
		}
	}


	if (ff == 1)
	{

		//------------------------------------------------REMOVING NULL PRODUCTIONS-----------------------------------------------------
		set<char> null;
		set<char>::iterator itr;
		for (i = 0; i<size_3; i++)
		{
			if (arr_5[i].body == "~")
				null.insert(arr_5[i].head);
		}
		for (i = 0; i<size_3; i++)
		{
			int flag1 = 0;
			int length = arr_5[i].body.length();
			for (j = 0; j<length; j++)
			{
				if (null.find(arr_5[i].body[j]) == null.end())
				{
					flag1 = 1;
					break;
				}
			}

			if (flag1 == 1)
				continue;
			else
				null.insert(arr_5[i].head);
		}
		int si = size_3;

		for (i = 0; i<si; i++)
		{
			int count = 0;
			int length = arr_5[i].body.length();
			for (j = 0; j<length; j++)
			{
				if (null.find(arr_5[i].body[j]) != null.end())
				{
					count++;
				}

			}
			//mout_1<<"count= "<<count<<"for i= "<<i<<endl;


			if (count>0)
			{
				//mout_1<<"Here\n";
				char temp[50];
				strcpy(temp, arr_5[i].body.c_str());
				char temp1[50][50];
				int k = 0;
				for (int siz = 1; siz <= length; siz++)
				{
					char sub[100];
					subarray(temp, length, sub, siz, 0, 0, temp1, k);
				}
				int m, n;

				for (m = 0; m<k; m++)
				{
					int f = 0;
					int l;
					for (l = 0; temp1[m][l] != '\0'; l++) {};
					//mout_1<<"here length is "<<l<<endl;
					for (n = 0; n<l; n++)
					{
						if (null.find(temp1[m][n]) != null.end())
							continue;
						else
						{
							f = 1;
							break;
						}
					}
					if (f == 1)
					{
						for (int v = m; v<k - 1; v++)
						{

							int l1 = sizeof(temp1[v + 1]), b;
							for (b = 0; b<l1; b++)
							{
								temp1[v][b] = temp1[v + 1][b];

							}
							temp1[v][b] = '\0';
						}
						k--;
						m--;
					}
				}


				for (m = 0; m<k; m++)
				{
					int length = arr_5[i].body.length();
					string t = arr_5[i].body;
					int l;
					for (l = 0; temp1[m][l] != '\0'; l++) {};
					for (n = 0; n<l; n++)
					{
						for (j = 0; j<length; j++)
						{
							if (t[j] == temp1[m][n])
							{
								t.erase(j, 1);
								length--;
								break;
							}
						}
					}
					arr_5[size_3].head = arr_5[i].head;
					if (t[0] == '\0')
						arr_5[size_3].body = "~\0";
					else
						arr_5[size_3].body = t;
					size_3++;
				}
			}

		}
		for (i = 0; i<size_3; i++)
		{
			if (arr_5[i].body[0] == '~')
			{
				for (j = i; j<size_3 - 1; j++)
				{
					arr_5[j].head = arr_5[j + 1].head;
					arr_5[j].body = arr_5[j + 1].body;
				}
				size_3--;
				i--;
			}
		}

	}
	int n;


	for (j = 0; j<size_3; j++)
	{
		if ((arr_5[j].head == arr_5[j].body[0]) && (arr_5[j].body.length() == 1))
		{
			for (int x = j; x<size_3 - 1; x++)
			{
				arr_5[j].head = arr_5[j + 1].head;
				arr_5[j].body = arr_5[j + 1].body;
			}
			size_3--;
		}
	}

	for (i = 0; i<size_3 - 1; i++)
	{
		//noofprod[arr_5[i].head-'A']++;
		int k = i + 1;
		for (j = i + 1; j<size_3; j++)
		{
			if (arr_5[i].head == arr_5[j].head)
			{
				//noofprod[arr_5[j].head-'A']++;
				string t1 = arr_5[j].body;
				arr_5[j].head = arr_5[k].head;
				arr_5[j].body = arr_5[k].body;
				arr_5[k].head = arr_5[i].head;
				arr_5[k].body = t1;
				k++;
			}
		}
	}


	for (int y = 0; y<size_3 - 1; y++)
	{
		for (int z = y + 1; z<size_3; z++)
		{
			if (arr_5[y].head == arr_5[z].head&&arr_5[y].body == arr_5[z].body)
			{
				for (int k = z; k<size_3 - 1; k++)
				{
					arr_5[k].head = arr_5[k + 1].head;
					arr_5[k].body = arr_5[k + 1].body;
				}
				size_3--;
				z--;
			}
		}
	}

	for (n = 0; n<26; n++)
		noofprod[n] = 0;
	for (i = 0; i<size_3; i++)
	{
		noofprod[arr_5[i].head - 'A']++;
	}
	//----------------------------------------------------- LEFT RECURSION REMOVAL ---------------------------------------------------------
	for (i = 0; i<size_3; i++)
	{

		for (j = 0; j <= i - 1; j += noofprod[arr_5[j].head - 'A'])
		{
			if ((arr_5[i].head != arr_5[j].head) && (arr_5[i].body[0] == arr_5[j].head))
			{
				int l = j;
				for (n = 1; n <= noofprod[arr_5[j].head - 'A']; n++)
				{
					int m;
					for (m = size_3; m>i + 1; m--)
					{
						arr_5[m].head = arr_5[m - 1].head;
						arr_5[m].body = arr_5[m - 1].body;
					}
					size_3++;
					arr_5[m].head = arr_5[i].head;
					string t;
					t = arr_5[l].body;
					t += arr_5[i].body.substr(1);
					arr_5[m].body = t;
					l++;
					noofprod[arr_5[i].head - 'A']++;
				}
				int m;
				for (m = i; m<size_3 - 1; m++)
				{
					arr_5[m].head = arr_5[m + 1].head;
					arr_5[m].body = arr_5[m + 1].body;
				}
				size_3--;
				noofprod[arr_5[i].head - 'A']--;
			}
			
		}

		//-----------------------------------Elimination of direct left recursion-------------------------------------------------------

		if ((arr_5[i + 1].head != arr_5[i].head) || (i + 1 == size_3))
		{
			int f = 0;
			for (n = i - noofprod[arr_5[i].head - 'A'] + 1; n <= i; n++)
			{
				if (arr_5[n].body[0] == arr_5[n].head)
				{
					f = 1;
					break;
				}
			}
			if (f == 0)
				continue;
			else
			{
				char d;
				for (int l = 25; l >= 0; l--)
				{
					if (nt[l] == 0)
					{
						d = char(l + 'A');
						nt[l] = 1;
						break;
					}
				}
				for (n = i - noofprod[arr_5[i].head - 'A'] + 1; n <= i; n++)
				{
					if (arr_5[n].body[0] != arr_5[n].head)
					{
						string s;
						s += d;
						s += "\0";
						if (arr_5[n].body[0] == '~')
						{
							arr_5[n].body = s;
						}
						arr_5[n].body += s;
					}
					else if (arr_5[n].body[0] == arr_5[n].head)
					{
						string s;
						s += d;
						s += "\0";
						noofprod[arr_5[n].head - 'A']--;
						arr_5[n].head = d;
						noofprod[arr_5[n].head - 'A']++;
						string t;
						t = arr_5[n].body.substr(1);
						t += s;
						arr_5[n].body = t;
					}
				}
				int m;
				for (m = size_3; m>i + 1; m--)
				{
					arr_5[m].head = arr_5[m - 1].head;
					arr_5[m].body = arr_5[m - 1].body;
				}
				size_3++;
				arr_5[m].head = d;
				arr_5[m].body = "~\0";
				noofprod[arr_5[m].head - 'A']++;
			}
		}

	}

	for (j = 0; j<size_3; j++)
	{
		if ((arr_5[j].head == arr_5[j].body[0]) && (arr_5[j].body.length() == 1))
		{
			for (int x = j; x<size_3 - 1; x++)
			{
				arr_5[j].head = arr_5[j + 1].head;
				arr_5[j].body = arr_5[j + 1].body;
			}
			size_3--;
		}
	}
	for (int y = 0; y<size_3 - 1; y++)
	{
		for (int z = y + 1; z<size_3; z++)
		{
			if (arr_5[y].head == arr_5[z].head&&arr_5[y].body == arr_5[z].body)
			{
				for (int k = z; k<size_3 - 1; k++)
				{
					arr_5[k].head = arr_5[k + 1].head;
					arr_5[k].body = arr_5[k + 1].body;
				}
				size_3--;
				z--;
			}
		}
	}

	if (arr_5[0].head != start)
	{
		for (j = 1; j<size_3; j++)
		{
			if (arr_5[j].head == start)
			{
				char h = arr_5[j].head;
				string b = arr_5[j].body;
				arr_5[j].body = arr_5[0].body;
				arr_5[j].head = arr_5[0].head;
				arr_5[0].head = h;
				arr_5[0].body = b;
				break;
			}
		}
	}

	for (i = 0; i<size_3 - 1; i++)
	{
		//noofprod[arr_5[i].head-'A']++;
		int k = i + 1;
		for (j = i + 1; j<size_3; j++)
		{
			if (arr_5[i].head == arr_5[j].head)
			{
				//noofprod[arr_5[j].head-'A']++;
				string t1 = arr_5[j].body;
				arr_5[j].head = arr_5[k].head;
				arr_5[j].body = arr_5[k].body;
				arr_5[k].head = arr_5[i].head;
				arr_5[k].body = t1;
				k++;
			}
		}
	}
	//------------------------------------------------------LEFT FACTORING------------------------------------------------------

	for (i = 0; i<size_3 - 1; i++)
	{
		int match = 0;
		int matchlen = -1;

		for (j = i + 1; j<size_3; j++)
		{
			if (arr_5[i].head == arr_5[j].head)
			{
				match++;
				int k = 0;
				int matched = -1;
				while (arr_5[i].body[k] == arr_5[j].body[k] && arr_5[i].body[k] != '\0'&&arr_5[j].body[k] != '\0')
				{
					matched++;
					k++;
				}
				if (matched == -1)
				{
					continue;
				}
				else
				{
					if (matched == matchlen&&match>1)
					{
						char d = arr_5[i].body[matched + 1];
						arr_5[j].head = d;
						if (arr_5[j].body.substr(matched + 1) != "\0")
							arr_5[j].body = arr_5[j].body.substr(matched + 1);
						else
							arr_5[j].body = "~\0";

					}
					else
					{
						matchlen = matched;
						prod_5 temp;
						temp.head = arr_5[i].head;
						temp.body = arr_5[i].body.substr(0, matched + 1);
						for (int l = 25; l >= 0; l--)
						{
							if (nt[l] == 0)
							{
								c = char(l + 'A');
								string s;
								s += c;
								s += "\0";
								temp.body += s;
								nt[l] = 1;
								break;
							}
						}

						arr_5[size_3].head = c;
						if (arr_5[i].body.substr(matched + 1) != "\0")
							arr_5[size_3].body = arr_5[i].body.substr(matched + 1);
						else
							arr_5[size_3].body = "~\0";
						arr_5[j].head = c;
						if (arr_5[j].body.substr(matched + 1) != "\0")
							arr_5[j].body = arr_5[j].body.substr(matched + 1);
						else
							arr_5[j].body = "~\0";
						arr_5[i].body = temp.body;
						//mout_1<<"\nj    "<<arr_5[j].head<<"->"<<arr_5[j].body;
						size_3++;
					}

				}
			}
		}
	}

	for (int y = 0; y<size_3 - 1; y++)
	{
		for (int z = y + 1; z<size_3; z++)
		{
			if (arr_5[y].head == arr_5[z].head&&arr_5[y].body == arr_5[z].body)
			{
				for (int k = z; k<size_3 - 1; k++)
				{
					arr_5[k].head = arr_5[k + 1].head;
					arr_5[k].body = arr_5[k + 1].body;
				}
				size_3--;
				z--;
			}
		}
	}

	for (i = 0; i<size_3 - 1; i++)
	{
		//noofprod[arr_5[i].head-'A']++;
		int k = i + 1;
		for (j = i + 1; j<size_3; j++)
		{
			if (arr_5[i].head == arr_5[j].head)
			{
				//noofprod[arr_5[j].head-'A']++;
				string t1 = arr_5[j].body;
				arr_5[j].head = arr_5[k].head;
				arr_5[j].body = arr_5[k].body;
				arr_5[k].head = arr_5[i].head;
				arr_5[k].body = t1;
				k++;
			}
		}
	}

	if (arr_5[0].head != start)
	{
		for (j = 1; j<size_3; j++)
		{
			if (arr_5[j].head == start)
			{
				char h = arr_5[j].head;
				string b = arr_5[j].body;
				arr_5[j].body = arr_5[0].body;
				arr_5[j].head = arr_5[0].head;
				arr_5[0].head = h;
				arr_5[0].body = b;
				break;
			}
		}
	}

	for (i = 0; i<size_3 - 1; i++)
	{
		//noofprod[arr_5[i].head-'A']++;
		int k = i + 1;
		for (j = i + 1; j<size_3; j++)
		{
			if (arr_5[i].head == arr_5[j].head)
			{
				//noofprod[arr_5[j].head-'A']++;
				string t1 = arr_5[j].body;
				arr_5[j].head = arr_5[k].head;
				arr_5[j].body = arr_5[k].body;
				arr_5[k].head = arr_5[i].head;
				arr_5[k].body = t1;
				k++;
			}
		}
	}

	for (j = 0; j<size_3; j++)
	{
		if ((arr_5[j].head == arr_5[j].body[0]) && (arr_5[j].body.length() == 1))
		{
			for (int x = j; x<size_3 - 1; x++)
			{
				arr_5[j].head = arr_5[j + 1].head;
				arr_5[j].body = arr_5[j + 1].body;
			}
			size_3--;
		}
	}
	/*
	-----------------------------------------------------------STEP II: CALCULATE FIRSTS----------------------------------------------------------------------------
	*/
	/* SORTING OF PRODUCTIONS */
	/* 'ldash' stores productions in topologically sorted manner */

	
	ma.open("NewInputFile.txt");
	for (i = 0; i<size_3; i++)
		ma << arr_5[i].head << "->" << arr_5[i].body << endl;
	ma.close();
	vector< pair<char, string> > l, ldash;
	vector< pair<char, string> >::iterator it, it1, itemp;
	/*
	flags the non terminals which have a production of the form A->~
	epsilon[i] is '1' if contains ~
	*/
	stack<pair<char, string> > tempst;
	int epsilon[26];
	for (int i = 0; i<26; i++) epsilon[i] = 0;
	/*
	Productions Types-
	Type I:   A->~
	Type II:  A->aBc
	Type III: A->Bc
	*/
	for (int i = 0; i<size_3; i++) {
		string s = arr_5[i].body;
		if (s[0] == '~') 
		{
			epsilon[arr_5[i].head - 'A'] = 1;
			ldash.push_back(make_pair(arr_5[i].head, s));
		}
		else if (s[0]<'A' || s[0]>'Z') 
		{
			ldash.push_back(make_pair(arr_5[i].head, s));
		}
		else 
		{
			l.push_back(make_pair(arr_5[i].head, s));
		}
	}
	int flag;

	while (!l.empty()) 
	{
		for (it = l.begin(); it<l.end(); ) 
		{
			/*body of production*/
			if (it == l.end() - 1)
				break;
			itemp = it + 1;
			string s = (*it).second;
			int len = s.length(), flag1=0;
			for (int i = 0; i<len; i++) 
			{
				if (s[i]<'A' || s[i]>'Z') 
				{
					ldash.push_back(*it);
					it = l.erase(it);
					//it--;
					break;
				}
				/* non-terminal */
				else 
				{
					int flag = 0;
					for (it1 = l.begin(); it1<l.end(); it1++) 
					{
						if (it1 == it) continue;
						if ((*it1).first == s[i]) {
							flag = 1;
							break;
						}
					}
					/* Non-Terminal not found in 'l' */
					if (flag == 0) 
					{
						/*check for ~ in non-terminal */
						if (epsilon[s[i] - 'A'] == 0) 
						{
							ldash.push_back(*it);
							it = l.erase(it);
							flag1++;
							//it--;
							break;
						}
						else 
						{
							if (i == len - 1) 
							{
								ldash.push_back(*it);
								it = l.erase(it);
								//it--;
								flag1++;
								break;
							}
						}
					}
					else 
						break;
				}
			}
			if (flag1 == 0)
				it = itemp;
		}
		if (it == l.end() - 1)
		{
			for (it = l.begin(); it != l.end(); it++)
			{
				tempst.push(*it);
			}
			while (!tempst.empty())
			{
				ldash.push_back(tempst.top());
				tempst.pop();
			}
			break;
		}
	}
	
	/* CALCULATION OF FIRSTS */
	/* Stores FIRSTS */
	map< char, list<char> > firsts;
	map< char, list<char> > ::iterator ind1, ind2;
	for (it = ldash.begin(); it != ldash.end(); it++)
	{
		string s = (*it).second;
		//cout<<s<<endl;
		int len = s.length();
		for (i = 0; i<len; i++)
		{
			//cout<<"i="<<i<<" ";
			if (s[i]<'A' || s[i]>'Z') {
				ind1 = firsts.find((*it).first);
				if (ind1 != firsts.end()) {
					((*ind1).second).push_back(s[i]);
					break;
				}
				else {
					list<char> temp;
					temp.push_back(s[i]);
					firsts.insert(make_pair((*it).first, temp));
					break;
				}
			}
			else {
				ind1 = firsts.find((*it).first);
				if (ind1 != firsts.end()) {
					ind2 = firsts.find(s[i]);
					list<char>::iterator lit;
					for (lit = ((*ind2).second).begin(); lit != ((*ind2).second).end(); lit++) {
						((*ind1).second).push_back(*lit);
					}
				}
				else {
					list<char> temp;
					ind2 = firsts.find(s[i]);
					list<char>::iterator lit;
					for (lit = ((*ind2).second).begin(); lit != ((*ind2).second).end(); lit++) {
						temp.push_back(*lit);
					}
					firsts.insert(make_pair((*it).first, temp));
				}
				if (epsilon[s[i] - 'A'] == 0)
					break;
				else {
					epsilon[(*it).first - 'A'] = 1;
				}
			}
		}
		//cout<<i<<" "<<len;
	}

	list<char> term;
	list<char> ::iterator ti;
	for (int i = 0; i<size_3; i++) {
		string s = arr_5[i].body;
		for (int j = 0; j<s.length(); j++)
			if (s[j]<'A' || s[j]>'Z')
				term.push_back(s[j]);
	}
	term.sort();
	term.unique();
	term.remove('~');

	/* Sending FIRSTS to a .txt file */
	map< char, list<char> > ::iterator mit;

	m_3 << "----------------------------------GRAMMAR----------------------------------\n\n";
	for (j = 0; j<size_3; j++)
		m_3 << j + 1 << ". " << arr_5[j].head << "->" << arr_5[j].body << endl;
	m_3 << "\n--------------------------------FIRST SETS---------------------------------\n\n";
	for (mit = firsts.begin(); mit != firsts.end(); mit++) {
		((*mit).second).sort();
		((*mit).second).unique();
		m_3 << "FIRST(" << (*mit).first << ") = { ";
		list<char> ::iterator lit;
		for (lit = ((*mit).second).begin(); lit != ((*mit).second).end(); lit++) {
			if (lit == ((*mit).second).begin()) m_3 << *lit;
			else m_3 << ", " << *lit;
		}
		m_3 << " }" << endl;
	}
	for (ti = term.begin(); ti != term.end(); ti++) {
		m_3 << "FIRST(" << (*ti) << ") = { " << (*ti) << " }" << endl;
	}
	

	/*
	-------------------------------------------------------------STEP III: FOLLOW--------------------------------------------------------------------------
	*/
	vector< pair< string, pair<char, int> > > pairs, pdash;
	vector<pair<string, pair<char, int> > >::iterator itp, itp1;

	/*Forming pairs: A->aBc, B, ind */
	for (int i = 0; i<size_3; i++) 
	{
		/* s = 'A->aBc' */
		string s;
		s.push_back(arr_5[i].head);
		s += "->";
		s += arr_5[i].body;
		/* stores body of production */
		string t = arr_5[i].body;
		int len = t.length();
		for (int j = 0; j<len; j++) {
			if (t[j] >= 'A' && t[j] <= 'Z')
				pairs.push_back(make_pair(s, make_pair(t[j], j + 3)));
		}
	}
	
	/*SORTING OF PRODUCTION PAIRS in 'pdash' */
	for (itp = pairs.begin(); itp<pairs.end(); itp++) 
	{
		string s = (*itp).first;
		int len = s.length();
		int pos = ((*itp).second).second;
		if (pos == len - 1) 
			continue;
		for (int i = pos + 1; i<len; i++) 
		{
			if (s[i]<'A' || s[i]>'Z') 
			{
				pdash.push_back(*itp);
				itp = pairs.erase(itp);
				itp--;
				break;
			}
			else 
			{
				if (epsilon[s[i] - 'A'] != 1) 
				{
					pdash.push_back(*itp);
					itp = pairs.erase(itp);
					itp--;
					break;
				}
				else break;;
			}
		}
	}
	
	while (!pairs.empty()) 
	{
		int sizi = pairs.size();
		for (itp = pairs.begin(); itp<pairs.end(); ) 
		{
			flag = 0;
			for (itp1 = pairs.begin(); itp1<pairs.end(); itp1++) 
			{
				if (itp == itp1) continue;
				string s = (*itp).first;
				if (s[0] == ((*itp1).second).first) 
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				pdash.push_back(*itp);
				itp = pairs.erase(itp);
			}
			else
				itp++;
		}
		int sizen = pairs.size();
		if (sizen == sizi) 
		{
			itp = pairs.begin();
			pdash.push_back(*itp);
			itp = pairs.erase(itp);
		}
	}
	//m_3 << "SSM";

	/*FOLLOW CALCULATION*/
	map<char, list<char> > follows;
	map<char, list<char> >::iterator mit1, mit2, mit3;
	list<char> t;
	t.push_back('$');
	char blah = arr_5[0].head;
	follows.insert(make_pair(blah, t));

	for (itp = pdash.begin(); itp<pdash.end(); itp++) 
	{
		flag = 0;
		int pos = ((*itp).second).second;
		string s = (*itp).first;
		char A = s[0];
		char B = ((*itp).second).first;
		int len = s.length();

		mit = follows.find(B);
		if (mit == follows.end()) 
		{
			list<char> temp;
			follows.insert(make_pair(B, temp));
		}
		mit = follows.find(B);
		if (pos != len - 1) 
		{
			for (int i = pos + 1; i<len; i++) 
			{
				if (s[i]<'A' || s[i]>'Z') 
				{
					((*mit).second).push_back(s[i]);
					break;
				}
				else 
				{
					mit1 = firsts.find(s[i]);
					list<char> ::iterator lit;
					for (lit = ((*mit1).second).begin(); lit != ((*mit1).second).end(); lit++) {
						if ((*lit) != '~') {
							((*mit).second).push_back(*lit);
						}
					}
					if (epsilon[s[i] - 'A'] == 0) break;
					else flag = 1;
				}
			}
		}

		mit2 = follows.find(A);
		if (mit2 == follows.end()) {
			list<char> temp;
			follows.insert(make_pair(A, temp));
		}
		mit2 = follows.find(A);
		mit = follows.find(B);
		if (mit2 == mit) continue;
		if (pos == len - 1 || flag == 1) {
			list<char> ::iterator lit;
			for (lit = ((*mit2).second).begin(); lit != ((*mit2).second).end(); lit++) {
				((*mit).second).push_back(*lit);
			}
		}
	}
	
	
	m_3 << "\n-------------------------------FOLLOW SETS---------------------------------\n\n";
	for (mit = follows.begin(); mit != follows.end(); mit++) {
		((*mit).second).sort();
		((*mit).second).unique();
		m_3 << "FOLLOW(" << (*mit).first << ") = { ";
		list<char> ::iterator lit, lit1;
		for (lit = ((*mit).second).begin(); lit != ((*mit).second).end(); lit++) {
			if (lit == ((*mit).second).begin()) m_3 << *lit;
			else m_3 << ", " << *lit;
		}
		m_3 << " }" << endl;
	}
	m_3.close();
	/*
	------------------------------------------------------STEP IV: PREDICTIVE PARSING TABLE--------------------------------------------------------------------
	*/

	map<char, list< pair< char, string> > > table;
	map<char, list< pair< char, string> > > ::iterator t1;
	list<char> nterm;
	list<char> ::iterator lit;
	/* non-terminals */
	for (mit = follows.begin(); mit != follows.end(); mit++) {
		nterm.push_back((*mit).first);
	}
	term.push_back('$');
	term.sort();
	/* inserting nterm, term in table with empty strings */
	for (lit = nterm.begin(); lit != nterm.end(); lit++) {
		list<pair< char, string> > temp;
		list<char> ::iterator lit1;
		for (lit1 = term.begin(); lit1 != term.end(); lit1++) {
			string s;
			temp.push_back(make_pair(*lit1, s));
		}
		table.insert(make_pair(*lit, temp));
	}
	/* traverse productions */
	for (int i = 0; i<size_3; i++) {
		string s = arr_5[i].body, pr;
		pr.push_back(arr_5[i].head);
		pr += "->";
		pr += arr_5[i].body;
		int len = s.length();
		int flag = 0;
		/* flag for checking ~, to add FOLLOW*/
		if (s[0] == '~') {
			flag = 1;
		}
		else {
			for (int j = 0; j<len; j++) {
				if (s[j]<'A' || s[j]>'Z') {
					list<pair<char, string > > ::iterator litt;
					for (litt = (table[arr_5[i].head]).begin(); litt != (table[arr_5[i].head]).end(); litt++) {
						if ((*litt).first == s[j])
							(*litt).second = pr;
					}
					break;
				}
				else {
					mit = firsts.find(s[j]);
					list<char> ::iterator lit;
					for (lit = ((*mit).second).begin(); lit != ((*mit).second).end(); lit++) {
						list<pair< char, string > > ::iterator litt;
						for (litt = (table[arr_5[i].head]).begin(); litt != (table[arr_5[i].head]).end(); litt++) {
							if ((*litt).first == (*lit)) (*litt).second = pr;
						}
					}
					if (epsilon[s[j] - 'A'] == 0) break;
					else flag = 1;
				}
			}
		}
		/* FOLLOW consideration */
		if (flag == 1) {
			mit = follows.find(arr_5[i].head);
			list<char> ::iterator lit;
			for (lit = ((*mit).second).begin(); lit != ((*mit).second).end(); lit++) {
				list<pair< char, string> >::iterator litt;
				for (litt = (table[arr_5[i].head]).begin(); litt != (table[arr_5[i].head]).end(); litt++) {
					if ((*litt).first == (*lit))
						(*litt).second = pr;
				}
			}
		}
	}

	/*PRINTS PREDICTIVE PARSING TABLE*/
	m_3.open("output.txt", ios_base::app);
	m_3 << "\n------------------------------PARSING TABLE--------------------------------\n\n";
	m_3 << std::left << setw(13) << setfill(' ') << " ";
	list<char> ::iterator litt;
	for (litt = term.begin(); litt != term.end(); litt++)
		m_3 << std::left << setw(13) << setfill(' ') << (*litt);
	m_3 << endl;
	for (t1 = table.begin(); t1 != table.end(); t1++) {
		m_3 << std::left << setw(13) << setfill(' ') << (*t1).first;
		list<pair<char, string> > ::iterator lit1;
		((*t1).second).sort();
		((*t1).second).unique();
		((*t1).second).sort();
		for (lit1 = ((*t1).second).begin(); lit1 != ((*t1).second).end(); lit1++) {
			m_3 << std::left << setw(13) << setfill(' ') << (*lit1).second;
		}
		m_3 << endl;
	}
	m_3.close();

	/*
	--------------------------------------------------------------STEP V: INPUT STRING-------------------------------------------------------------------------
	*/
	myfile.open("details.txt");
	getline(myfile, s);
	myfile.close();
	string tobepars = s;

	/*
	----------------------------------------------------------STEP VI: TABLE DRIVEN PARSING--------------------------------------------------------------------
	*/
	m_3.open("output.txt", ios_base::app);
	m_3 << "\n--------------------------TABLE DRIVEN PARSING-----------------------------\n\n";
	int a = 0;
	/* stack */
	list<char> st;
	list<char>::reverse_iterator cit, cit1;
	list<string> full_st, leftmost;
	list<string>::iterator sit;
	string strr, str1;
	tobepars.push_back('$');

	/* initialize stack*/
	st.push_back('$');
	st.push_back(arr_5[0].head);

	/* creating string for current stack elements */
	for (cit = st.rbegin(); cit != st.rend(); cit++)
		strr.push_back(*cit);
	full_st.push_back(strr);

	/* matched+stack(string) goes to leftmost */
	str1 = tobepars.substr(0, a) + strr;
	leftmost.push_back(str1);
	int lucky = 7, starwars = tobepars.length() - 1;
	int store = max(starwars, lucky);
	m_3 << "_______________________________________\n";
	format_VAR3(store, "MATCHED");
	format_VAR_r3(store + store / 2, "STACK");
	format_VAR_r3(store + 3, "INPUT");
	format3("  PRODUCTION");
	m_3 << "\n";
	m_3 << "_______________________________________\n";
	format_VAR3(store, tobepars.substr(0, a));
	format_VAR_r3(store + store / 2, full_st.back());
	format_VAR_r3(store + 3, tobepars.substr(a));
	int err = 0;







	while ((tobepars[a] != '$') || (st.back() != '$')) 
	{
		char top = st.back();
		int flag = 0;
		if (top == tobepars[a]) {
			st.pop_back();
			a++;
			format3("  ---");
			m_3 << "\n";
		}
		else {
			string prod_3, str;
			t1 = table.find(top);
			list<pair<char, string> >::iterator it;
			for (it = ((*t1).second).begin(); it != ((*t1).second).end(); it++) {
				if (((*it).first) == tobepars[a]) {
					prod_3 = (*it).second;
					if (prod_3.length()>0) {
						str = prod_3.substr(3);

						flag = 1;
						st.pop_back();
						break;
					}
				}
			}
			if (flag == 1) {
				m_3 << "  ";
				format3(prod_3);
				produc_5.push_back(prod_3);
				m_3 << endl;
				for (int i = str.length() - 1; i >= 0; i--) {
					if (str[i] != '~')
						st.push_back(str[i]);
				}
			}
			else {
				err = 1;
				break;
			}
		}
		/* creating string for current stack elements */
		string s1, s2;
		for (cit = st.rbegin(); cit != st.rend(); cit++)
			s1.push_back(*cit);
		full_st.push_back(s1);
		/* prints another row of the table */
		s2 = tobepars.substr(0, a) + s1;
		leftmost.push_back(s2);
		format_VAR3(store, tobepars.substr(0, a));
		format_VAR_r3(store + store / 2, full_st.back());
		format_VAR_r3(store + 3, tobepars.substr(a));
	}

	if (err == 1)
		format3("  Syntax error");
	else
		format3("  Accept");
	m_3 << endl;

	m_3 << "_______________________________________\n";
	/*
	------------------------------------------------------STEP VII: CONSTRUCT PARSE TREE--------------------------------------------------------------------
	*/
	if (err == 0) 
	{
		for (int i = 0; i < 10; i++)
			ar_5[i] = 1;
		m_3 << "\n----------------------------PARSE TREE-----------------------------------\n\n";
		string inpFile2 = "NewInputFile";
		produc_6.clear();
		produc_6 = slr1(inpFile2, tobepars);
		it8_5 = produc_6.begin();
		parseTree3(arr_5[0].head, 0);
	}

	/*
	------------------------------------------------------STEP VIII: LEFT MOST DERIVATION------------------------------------------------------------------
	*/
	if (err == 0) {
		m_3 << "\n----------------------------LEFTMOST DERIVATION---------------------------\n\n";
		leftmost.unique();
		m_3 << arr_5[0].head;
		//m_3<<std::left<<setw(2)<<setfill(' ')<<arr_5[0].head;
		leftmost.pop_front();

		sit = leftmost.begin();
		(*sit).erase((*sit).length() - 1);
		string sss = "=>" + (*sit);
		//format(sss);
		m_3 << sss;
		//m_3<<endl;
		leftmost.pop_front();
		for (sit = leftmost.begin(); sit != leftmost.end(); sit++) {
			(*sit).erase((*sit).length() - 1);
			string s = "=>" + (*sit);
			m_3 << std::left << setw(2) << setfill(' ');
			m_3 << s;
			//format(s);
			//m_3<<endl;
		}
	}
	m_3.close();

}

