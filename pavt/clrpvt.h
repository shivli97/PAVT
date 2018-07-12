#pragma once
#include<fstream>
#include<string.h>
#include<map>
#include<string>
#include<list>
#include<vector>
#include<iomanip>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<stack>

#define N 100
using namespace std;
int f[100], help[100];
ofstream mout;
int m, cnt, cnt1, cnt2, cnt3, ctr;
int i, j, k, n, o, p, ns, tn , rr, x;
char grammar_l[50], grammar_r[50][30], temp, templ[50], tempr[50][30], *ptr, temp2[5], mat[50][50];
char productions_l[50], productions_r[50][30], ss, buffer[5], store[1000],st_1[30];
int final_number, err, space;
int mo, var;
string input;
map<char, int> Mp, Mpupper, Mplower;
map<char, int> ::iterator iter;

list<string> produc;
int c;
list<string> ::iterator it7;
static list<string> ::iterator it8;
map< char, list<char> > firsts;
map< char, list<char> > ::iterator ind1, ind2, ix;
char firsts_return[20];
char *help_array;
list<char>::iterator it2;
char a, *alpha, B, *beta;

struct prod
{
	char head;
	string body;
};

struct item_sets
{   //LHS and RHS indicate left and right sides of the productions. Left side is a nonterminal(single character)
	char lhs[50], rhs[50][50];
	//Symbol on which the state has a transition
	char sym;
	//No. of productions in a given state
	int n;
	//List of terminals associated with each production
	char lookahead[50][50];
}I[100];

char *Firsts(string abeta, int k)
{
	int y = abeta.length();
	int flag = 0;
	c = 0;
	for (ix = firsts.begin(); ix != firsts.end(); ix++)
	{
		flag = 0;
		list<char> ::iterator iy;
		if (abeta[c] == '~')
		{
			c++;
		}
		if (c >= y)
			break;
		if (abeta[c] == '$')
		{
			c++;
			for (var = 0; var<k; var++)
				if (firsts_return[var] != '$')
					continue;
				else break;
				if (var == k)
					firsts_return[k++] = '$';
				break;
		}
		if (!isupper(abeta[c]))
		{
			for (var = 0; var<k; var++)
				if (firsts_return[var] != abeta[c])
					continue;
				else break;
				if (var == k)
					firsts_return[k++] = abeta[c];
				break;
		}
		if (((*ix).first) == abeta[c]) {
			for (iy = ((*ix).second).begin(); iy != ((*ix).second).end(); ++iy)
			{
				if ((*iy) == '~')
				{
					flag = 1;
					continue;
				}
				for (var = 0; var<k; var++)
					if (firsts_return[var] != *(iy))
						continue;
					else break;
					if (var == k)
						firsts_return[k++] = *(iy);

			}
			if (flag)
			{
				c++;
				ix = firsts.begin()--;
				if (c >= y)
					break;
			}
			else
			{
				break;
			}
		}
		else continue;
	}
	firsts_return[k] = NULL;
	return firsts_return;
}
int compare_struct(item_sets s1, item_sets s2)
{
	int t;
	if (s1.n != s2.n)
		return 0;
	if (strcmp(s1.lhs, s2.lhs) != 0)
		return 0;
	for (t = 0; t<s1.n; t++)
		if (strcmp(s1.rhs[t], s2.rhs[t]) != 0)
			return 0;
	for (t = 0; t<s1.n; t++)
		if (strcmp(s1.lookahead[t], s2.lookahead[t]) != 0)
			return 0;
	return 1;
}

//This finds the closure of the item sets in a given state after the GOTO function
//To add more productions
void Closure()
{
	int r, s, t, l1 = 0, rr1 = 0;
	char *ptr1, read1[50][30];
	for (x = 0; x<20; x++)
		firsts_return[x] = NULL;
	for (r = 0; r<I[ns].n; r++)
	{
		ptr1 = strchr(I[ns].rhs[l1], '.');
		t = ptr1 - I[ns].rhs[l1];
		if (t + 1 == strlen(I[ns].rhs[l1]))
		{
			l1++;
			continue;
		}
		temp = I[ns].rhs[l1][t + 1];
		l1++;
		if (!isupper(temp))
			continue;
		if (strlen(strchr(I[ns].rhs[l1 - 1], '.'))<3)
			beta = "~";
		else beta = strchr(I[ns].rhs[l1 - 1], '.') + 2;
		a = I[ns].lookahead[l1 - 1][0];
		string betaa;
		betaa.resize(strlen(beta) + 1);
		for (int i = 0; beta[i] != '\0'; i++)
			betaa[i] = beta[i];
		betaa[strlen(beta)] = a;
		help_array = Firsts(betaa, 0);
		for (mo = 1; mo<strlen(I[ns].lookahead[l1 - 1]); mo++)
		{
			a = I[ns].lookahead[l1 - 1][mo];
			betaa.resize(strlen(beta) + 1);
			for (int i = 0; beta[i] != '\0'; i++)
				betaa[i] = beta[i];
			betaa[strlen(beta)] = a;
			int y = strlen(help_array);
			help_array = Firsts(betaa, y);
		}
		for (s = 0; s<rr1; s++)
			if (temp == read1[s][0])
				break;
		if (s == rr1)
		{
			read1[rr1][0] = temp;
			rr1++;
		}
		else
		{
			for (j = 0; j<I[ns].n; j++)
			{
				if (temp == I[ns].lhs[j])
				{
					strcat(I[ns].lookahead[j], help_array);
				}
			}
			continue;
		}
		for (s = 0; s<n; s++)
		{
			if (grammar_l[s] == temp)
			{
				I[ns].rhs[I[ns].n][0] = '.';
				I[ns].rhs[I[ns].n][1] = NULL;
				strcat(I[ns].rhs[I[ns].n], grammar_r[s]);
				I[ns].lhs[I[ns].n] = grammar_l[s];
				I[ns].lhs[I[ns].n + 1] = NULL;
				strcpy(I[ns].lookahead[I[ns].n], help_array);
				I[ns].n++;
			}
		}
	}
}

void Goto(int l)
{
	int t1;
	char read1[50][30], rr1 = 0, *ptr1;
	tn = 0;
	for (i = 0; i<I[l].n; i++)
	{
		temp2[0] = '.';
		ptr1 = strchr(I[l].rhs[i], '.');
		if (ptr1[1] == '~')
			continue;
		t1 = ptr1 - I[l].rhs[i];
		if (t1 + 1 == strlen(I[l].rhs[i]))
			continue;
		temp2[1] = I[l].rhs[i][t1 + 1];
		temp2[2] = NULL;
		for (j = 0; j<rr1; j++)
			if (strcmp(temp2, read1[j]) == 0)
				break;
		if (j == rr1)
		{
			strcpy(read1[rr1], temp2);
			read1[rr1][2] = NULL;
			rr1++;
		}
		else
			continue;
		for (j = 0; j<I[l].n; j++)
		{
			ptr = strstr(I[l].rhs[j], temp2);
			if (ptr)
			{
				templ[tn] = I[l].lhs[j];
				templ[tn + 1] = NULL;
				strcpy(tempr[tn], I[l].rhs[j]);
				strcpy(I[ns].lookahead[tn], I[l].lookahead[j]);
				tn++;
			}
		}
		for (j = 0; j<tn; j++)
		{
			ptr = strchr(tempr[j], '.');
			p = ptr - tempr[j];
			tempr[j][p] = tempr[j][p + 1];
			tempr[j][p + 1] = '.';
			I[ns].lhs[I[ns].n] = templ[j];
			I[ns].lhs[I[ns].n + 1] = NULL;
			strcpy(I[ns].rhs[I[ns].n], tempr[j]);
			I[ns].n++;
		}
		Closure();
		for (j = 0; j<ns; j++)
		{
			if (compare_struct(I[ns], I[j]) == 1)
			{
				I[ns].lhs[0] = NULL;
				for (k = 0; k<I[ns].n; k++)
					I[ns].rhs[k][0] = NULL;
				I[ns].n = 0;
				for (k = 0; k<I[ns].n; k++)
					I[ns].lookahead[k][0] = NULL;
				if (temp2[1])
					mat[l][j] = temp2[1];
				break;
			}
		}
		if (j<ns)
		{
			tn = 0;
			for (j = 0; j<50; j++)
			{
				templ[j] = NULL;
				tempr[j][0] = NULL;
				firsts_return[j] = NULL;
			}
			continue;
		}
		if (ptr1[1])
			mat[l][j] = ptr1[1];
		I[ns].sym = ptr1[1];

		//Printing
		//This is the symbol on which the state has a transition(LR automation
		ns++;
		tn = 0;
		for (j = 0; j<50; j++)
		{
			templ[j] = NULL;
			tempr[j][0] = NULL;
			firsts_return[j] = NULL;
		}
	}
}

int ar[10] = { 1,1,1,1,1,1,1,1,1,1 };
void parseTree(char X, int l) {
	int lev = l;
	for (int i = 0; i<10; i++) {
		if (lev - 1 >0) {}
		else break;
		if (ar[i] == 1) mout << "| ";
		else mout << "  ";
		lev--;
	}
	if (lev == 1)
		mout << "|_";
	mout << X << endl;
	if (X<'A' || X>'Z')
		return;
	for (it7 = it8; it7 != produc.end(); it7++) {
		string p = (*it7);
		if (p[0] == X) {
			it8 = ++it7;
			string s = p.substr(3);
			int len = s.length();
			for (int j = 0; j<len; j++) {
				if (len - 1 == j)
					ar[l] = 0;
				parseTree(s[len - 1 - j], l + 1);
				ar[l] = 1;
				if (len - 1 != j) {
					int lev = l + 1;
					for (int i = 0; i<10; i++) {
						if (lev >0) {}
						else break;
						if (ar[i] == 1) mout << "| ";
						else mout << "  ";
						lev--;
					}
					mout << endl;
				}
			}
			break;
		}
	}
	return;
}

int maxLenP;
int siz;
prod *arr = new prod[N];


void clr()
{
	string s;
	ifstream myfile("grammar.txt");
	int i = 0;
	arr[i].head = 'Z';
	i++;
	n = 0;
	mout.open("output.txt");
	maxLenP = 0;
	while (!myfile.eof())
	{
		getline(myfile, s);
		arr[i].head = s[0];
		arr[0].body = arr[1].head;
		int len = s.length();
		/*Allows extra line at the end*/
		if (len>maxLenP) maxLenP = len;
		if (len == 0)
			break;
		arr[i].body = s.substr(3);
		//body starts from position 3
		i++;
		grammar_l[n] = s[0];
		int j = 3;
		while (s[j] != '\0')
			grammar_r[n][j - 3] = s[j++];
		grammar_r[n][j - 3] = '\0';
		n++;
	}
	myfile.close();
	/* # Productions*/
	siz = i;
	mout << "-----------------------------AUGMENTED GRAMMAR-----------------------------\n\n";
	for (j = 0; j<siz; j++)
		mout << j + 1 << ". " << arr[j].head << "->" << arr[j].body << endl;

	/*-----------------------------------STEP I: CALCULATE FIRSTS----------------------------------*/
	/* SORTING OF PRODUCTIONS */
	/* 'ldash' stores productions in topologically sorted manner */
	vector< pair<char, string> > l, ldash;
	vector< pair<char, string> >::iterator it, it1,itemp;
	stack<pair<char, string> > tempst;
	/*
	flags the non terminals which have a production of the form A->~
	epsilon[i] is '1' if contains ~
	*/
	int epsilon[26];
	for (int i = 0; i<26; i++) epsilon[i] = 0;
	/*
	Productions Types-
	Type I:   A->~
	Type II:  A->aBc
	Type III: A->Bc
	*/
	for (int i = 0; i<siz; i++)
	{
		string s = arr[i].body;
		if (s[0] == '~')
		{
			epsilon[arr[i].head - 'A'] = 1;
			ldash.push_back(make_pair(arr[i].head, s));
		}
		else if (s[0]<'A' || s[0]>'Z') {
			ldash.push_back(make_pair(arr[i].head, s));
		}
		else {
			l.push_back(make_pair(arr[i].head, s));
		}
	}

	int flag;
	while (!l.empty())
	{
		for (it = l.begin(); it<l.end(); )
		{
			if (it == l.end() - 1)
				break;
			itemp = it + 1;
			string s = (*it).second; //s is body of production
			int len = s.length(), flag1 = 0;
			for (int i = 0; i<len; i++)
			{
				/* terminal check */
				if (s[i]<'A' || s[i]>'Z')
				{
					ldash.push_back(*it);
					it = l.erase(it);
					//it--;
					break;
				}
				else  /* non-terminal */
				{
					int flag = 0;
					for (it1 = l.begin(); it1<l.end(); it1++)
					{
						if (it1 == it) continue;
						if ((*it1).first == s[i])
						{
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
								flag1++;
								//it--;
								break;
							}
						}

					}// END OF IF(FLAG==0)
					else
					{
						break;  //=> FLAG=1
					}
				}//END OF IF STATEMENT FOR NON TERMINAL
			}//END OF FOR(i=0;i<len;i++)
			if (flag1 == 0)
				it = itemp;
		}//END OF FOR
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
	firsts.clear();
	for (it = ldash.begin(); it != ldash.end(); it++)
	{
		/* body of production */
		string s = (*it).second;
		int len = s.length();
		for (int i = 0; i<len; i++)
		{
			/* terminal check */
			if (s[i]<'A' || s[i]>'Z')
			{
				/*search for head in map. If already exits add to the list of firsts else create a
				new entry for the map*/
				ind1 = firsts.find((*it).first);
				if (ind1 != firsts.end())
				{
					((*ind1).second).push_back(s[i]);
					break;
				}
				else
				{
					list<char> temp;
					temp.push_back(s[i]);
					firsts.insert(make_pair((*it).first, temp));
					break;
				}
			}
			/* non-terminal */
			else
			{
				ind1 = firsts.find((*it).first);
				if (ind1 != firsts.end())
				{
					ind2 = firsts.find(s[i]);
					list<char>::iterator lit;
					int cnt = 0;
					for (lit = ((*ind2).second).begin(); lit != ((*ind2).second).end(); lit++)
					{
						cnt++;
					}

					for (lit = ((*ind2).second).begin(); cnt>0; lit++, cnt--)
					{
						((*ind1).second).push_back(*lit);
					}
				}
				else
				{
					list<char> temp;
					ind2 = firsts.find(s[i]);
					list<char>::iterator lit;
					for (lit = ((*ind2).second).begin(); lit != ((*ind2).second).end(); lit++)
					{
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
	}
	/* terminals */
	list<char> term;
	list<char> ::iterator ti;
	for (int i = 0; i<siz; i++)
	{
		string s = arr[i].body;
		for (int j = 0; j<s.length(); j++)
			if (s[j]<'A' || s[j]>'Z')
				term.push_back(s[j]);
	}
	term.sort();
	term.unique();
	term.remove('~');

	/* printing firsts */
	map< char, list<char> > ::iterator mit;
	mout << "\n--------------------------------FIRST SETS---------------------------------\n\n";
	for (mit = firsts.begin(); mit != firsts.end(); mit++)
	{
		((*mit).second).sort();
		((*mit).second).unique();
		mout << "FIRST(" << (*mit).first << ") = { ";
		list<char> ::iterator lit;
		for (lit = ((*mit).second).begin(); lit != ((*mit).second).end(); lit++)
		{
			if (lit == ((*mit).second).begin()) mout << *lit;
			else mout << ", " << *lit;
		}
		mout << " }" << endl;
	}

	for (ti = term.begin(); ti != term.end(); ti++)
	{
		mout << "FIRST(" << (*ti) << ") = { " << (*ti) << " }" << endl;
	}

	mout.close();

	/*----------------------------------STEP III: ITEM SETS----------------------------------*/

	for (i = 0; i<50; i++)
	{
		I[i].n = 0;
		I[i].lhs[0] = NULL;
		I[i].rhs[0][0] = NULL;
		I[i].lookahead[0][0] = NULL;
	}

	mout.open("output.txt", ios_base::app);
	ss = grammar_l[0];
	//Original starting symbol is S and the new starting symbol is Z.
	I[0].lhs[0] = 'Z';
	char as[2];
	as[0] = '.', as[1] = ss, as[2] = '\0';

	//strcpy(I[0].rhs[0], as);
	int ch;
	for (ch = 0; as[ch] != '\0'; ch++)
		I[0].rhs[0][ch] = as[ch];
	I[0].rhs[0][ch] = '\0';
	I[0].n++;
	int l1 = 0;
	rr = 0;
	strcpy(I[0].lookahead[0], "$");
	char read[50][30];
	for (x = 0; x<20; x++)
		firsts_return[x] = NULL;
	for (i = 0; i<n; i++)
	{
		temp = I[0].rhs[l1][1];
		l1++;
		if (!isupper(temp))
			continue;
		if (strlen(strchr(I[0].rhs[l1 - 1], '.'))<3)
			beta = "~";
		else beta = strchr(I[0].rhs[l1 - 1], '.') + 2;
		a = I[0].lookahead[l1 - 1][0];
		string betaa;
		betaa.resize(strlen(beta) + 1);
		for (int i = 0; beta[i] != '\0'; i++)
			betaa[i] = beta[i];
		betaa[strlen(beta)] = a;
		help_array = Firsts(betaa, 0);
		for (mo = 1; mo<strlen(I[0].lookahead[l1 - 1]); mo++)
		{
			a = I[0].lookahead[l1 - 1][mo];
			string betaa;
			betaa.resize(strlen(beta) + 1);
			for (int i = 0; beta[i] != '\0'; i++)
				betaa[i] = beta[i];
			betaa[strlen(beta)] = a;
			int y = strlen(help_array);
			help_array = Firsts(betaa, y);
		}
		for (j = 0; j<rr; j++)
			if (temp == read[j][0])
				break;
		if (j == rr)
		{
			read[rr][0] = temp;
			rr++;
		}
		else
		{
			for (j = 0; j<I[0].n; j++)
			{
				if (temp == I[0].lhs[j])
				{
					strcat(I[0].lookahead[j], help_array);
				}
			}
			continue;
		}
		for (j = 0; j<n; j++)
		{
			if (grammar_l[j] == temp)
			{
				int ch;
				for (ch = 0; help_array[ch] != '\0'; ch++)
					I[0].lookahead[I[0].n][ch]= help_array[ch];
				I[0].lookahead[I[0].n][ch] = '\0';
				I[0].rhs[I[0].n][0] = '.';
				for (int k = 0; grammar_r[j][k] != '\0'; k++)
				{
					I[0].rhs[I[0].n][k + 1] = grammar_r[j][k];
				}
				I[0].lhs[I[0].n] = grammar_l[j];
				I[0].n++;
			}
		}
	}
	ns=1;
	for (l1 = 0; l1<ns; l1++)
		Goto(l1);
	mout << "\n---------------------------------ITEM SETS---------------------------------\n\n";
	//Printing Item Sets
	mout << "CLOSURE({[" << I[0].lhs[0] << "->" << I[0].rhs[0] << ",$]})={";
	for (i = 0; i<I[0].n - 1; i++)
	{
		mout << "[" << I[0].lhs[i] << "->" << I[0].rhs[i] << ",";
		for (mo = 0; mo<strlen(I[0].lookahead[i]); mo++)
		{
			mout << I[0].lookahead[i][mo];
			if (mo != strlen(I[0].lookahead[i]) - 1)
				mout << "/";
		}
		mout << "]";
	}
	mout << "[" << I[0].lhs[i] << "->" << I[0].rhs[i] << ",";
	for (mo = 0; mo<strlen(I[0].lookahead[i]); mo++)
	{
		mout << I[0].lookahead[i][mo];
		if (mo != strlen(I[0].lookahead[i]) - 1)
			mout << "/";
	}
	mout << "]}=";
	mout << "I0" << endl << endl;
	for (i = 0; i<ns; i++)
	{
		ctr = 0;
		for (j = 0; j<ns; j++)
		{
			if (mat[i][j])
				ctr++;
		}
		if (ctr)
		{
			mout << "I" << i << "={";
			for (k = 0; k<I[i].n - 1; k++)
			{
				mout << "[" << I[i].lhs[k] << "->" << I[i].rhs[k] << ",";
				for (mo = 0; mo<strlen(I[i].lookahead[k]); mo++)
				{
					mout << I[i].lookahead[k][mo];
					if (mo != strlen(I[i].lookahead[k]) - 1)
						mout << "/";
				}
				mout << "]";
			}
			mout << "[" << I[i].lhs[k] << "->" << I[i].rhs[k] << ",";
			for (mo = 0; mo<strlen(I[i].lookahead[k]); mo++)
			{
				mout << I[i].lookahead[k][mo];
				if (mo != strlen(I[i].lookahead[k]) - 1)
					mout << "/";
			}
			mout << "]}" << endl;
		}
		else continue;
		for (j = 0; j<ns; j++)
		{
			if (mat[i][j])
			{
				mout << "GOTO(I" << i << "," << mat[i][j] << ")";
				mout << "={";
				for (k = 0; k<I[j].n - 1; k++)
				{
					mout << "[" << I[j].lhs[k] << "->" << I[j].rhs[k] << ",";
					for (mo = 0; mo<strlen(I[j].lookahead[k]); mo++)
					{
						mout << I[j].lookahead[k][mo];
						if (mo != strlen(I[j].lookahead[k]) - 1)
							mout << "/";
					}
					mout << "]";
				}
				mout << "[" << I[j].lhs[k] << "->" << I[j].rhs[k] << ",";
				for (mo = 0; mo<strlen(I[j].lookahead[k]); mo++)
				{
					mout << I[j].lookahead[k][mo];
					if (mo != strlen(I[j].lookahead[k]) - 1)
						mout << "/";
				}
				mout << "]}=I" << j << endl;
			}
		}
		mout << endl;
	}
	/*----------------------------------STEP IV: PARSING TABLE----------------------------------*/
	Mp.clear();
	Mplower.clear();
	Mpupper.clear();
	mout << "-----------------------------PARSING TABLE---------------------------------\n\n";
	cnt1 = 0; cnt = 1;
	for (i = 0; i<n; i++)
	{
		Mp[grammar_l[i]] = 1; //non-terminal
		cnt1++;
	}

	for (i = 0; i<n; i++)
	{
		for (j = 0; grammar_r[i][j] != '\0'; j++)
			if (Mp.find(grammar_r[i][j]) == Mp.end())
			{
				Mp[grammar_r[i][j]] = 0;  //terminal
				cnt++;
			}
	}
	Mp['$'] = 0;
	cnt2 = 0; cnt3 = 0;
	for (iter = Mp.begin(); iter != Mp.end(); iter++)
	{
		if (iter->second == 1)
			Mpupper[iter->first] = ++cnt2;
		else
			Mplower[iter->first] = ++cnt3;
	}
	mout << "_______";
	for (i = 0; i<6 * (cnt2 + cnt3) + 4; i++)
		mout << "_";
	mout << endl;
	mout << "STATE";
	mout << setw(4 * cnt) << "ACTION";
	mout << setw(4 * cnt1) << "GOTO" << endl;
	mout << "_______";
	for (i = 0; i<6 * (cnt2 + cnt3) + 4; i++)
		mout << "_";
	mout << "\n      |";
	for (iter = Mp.begin(); iter != Mp.end(); iter++)
		if (iter->second == 0)
			mout << setw(6) << iter->first;
	mout << " |";
	for (iter = Mp.begin(); iter != Mp.end(); iter++)
		if (iter->second == 1)
			mout << setw(6) << iter->first;
	mout << endl;
	mout << "______|";
	for (i = 0; i<6 * (cnt3); i++)
		mout << "_";
	mout << "_|";
	for (i = 0; i<6 * (cnt2)+2; i++)
		mout << "_";
	mout << endl;

	int mat1[100][100];
	for (i = 0; i<ns; i++)
		for (j = 0; j<cnt2; j++)
			mat1[i][j] = -1;
	pair<char, int> action[100][100];
	for (i = 0; i<ns; i++)
		for (j = 0; j<cnt; j++)
			action[i][j] = make_pair('e', 0);

	for (i = 0; i<ns; i++)
		for (j = 0; j<ns; j++)
			if (mat[i][j] != '\0')
			{
				if (Mpupper[mat[i][j]] != 0)
					mat1[i][Mpupper[mat[i][j]] - 1] = j;
				else if (Mplower[mat[i][j]] != 0)
					action[i][Mplower[mat[i][j]] - 1] = make_pair('s', j);
			}

	char str[30];
	str[0] = ss;
	str[1] = '.';
	str[2] = '\0';
	int num = 1;
	for (i = 0; i<ns; i++)
	{
		for (j = 0; j<I[i].n; j++)
		{
			if (I[i].lhs[j] == 'Z' && strcmp(I[i].rhs[j], str) == 0)
			{
				action[i][Mplower['$'] - 1] = make_pair('a', 0);
				continue;
			}
			char *ptr1 = strchr(I[i].rhs[j], '.');
			ptr1++;
			if (*ptr1 == '\0' || *ptr1 == '~')   //reduction
			{
				for (k = 0; k<n; k++)  //traversing all productions
				{

					if (*ptr1 == '\0')
					{
						int ch;
						for (ch = 0; grammar_r[k][ch] != '\0'; ch++)
							st_1[ch] = grammar_r[k][ch];
						st_1[ch] = '\0';
						strcat(st_1, ".");
						if (grammar_l[k] == I[i].lhs[j] && strcmp(st_1, I[i].rhs[j]) == 0)
						{
							num = k + 1;
							break;
						}
					}
					else if (grammar_l[k] == I[i].lhs[j] && grammar_r[k][0] == '~')
					{
						num = k + 1;
						break;
					}
				}
				for (k = 0; k<strlen(I[i].lookahead[j]); k++)
					action[i][Mplower[I[i].lookahead[j][k]] - 1] = make_pair('r', num);
			}
		}
	}

	for (int i = 0; i<ns; i++)
	{
		mout << setw(6) << i << "|";
		for (int j = 0; j<cnt; j++)
		{
			if (action[i][j].first == 'e')
				mout << "      ";
			else if (action[i][j].first == 'a')
				mout << "   acc";
			else
			{
				str[0] = action[i][j].first;
				str[1] = '\0';
				strcat(str, itoa(action[i][j].second, buffer, 10));
				mout << setw(6) << str;
			}
		}
		mout << setw(2) << '|';
		for (int j = 0; j<cnt2; j++)
			if (mat1[i][j] == -1)
				mout << "      ";
			else
			{
				itoa(mat1[i][j], buffer, 10);
				mout << setw(6) << buffer;
			}
		mout << endl;
	}
	mout << "_______";
	for (i = 0; i<6 * (cnt2 + cnt3) + 4; i++)
		mout << "_";
	mout << endl;
	mout.close();

	/*---------------------------------STEP V: LR PARSING ALGO---------------------------------*/

	myfile.open("details.txt");
	getline(myfile,s);
	myfile.close();
	input = s;
	char a, b[10];
	s += "$";
	final_number = 0;
	stack<int> S, Stemp;
	S.push(0);
	mout.open("output.txt", ios_base::app);
	mout << "\n--------------------------TABLE DRIVEN PARSING---------------------------\n\n";
	mout << "__________________________________________________________________________\n";
	mout << std::left << setw(30) << "STACK";
	mout << std::left << setw(22) << "INPUT";
	mout << " ACTION     PRODUCTION" << endl;
	mout << "__________________________________________________________________________\n";
	k = 0;
	while (1)
	{
		space = 30;
		a = s[0];
		num = S.top();
		b[0] = action[num][Mplower[a] - 1].first;
		b[1] = '\0';
		j = action[num][Mplower[a] - 1].second;

		while (!S.empty())
		{
			Stemp.push(S.top());
			S.pop();
		}
		while (!Stemp.empty())
		{
			mout << Stemp.top() << ' ';
			itoa(Stemp.top(), buffer, 10);
			space -= (strlen(buffer) + 1);
			S.push(Stemp.top());
			Stemp.pop();
		}
		while (space>0)
		{
			mout << " ";
			space--;
		}
		mout << std::left << setw(25) << s;
		itoa(j, temp2, 10);
		strcat(b, temp2);
		if (action[num][Mplower[a] - 1].first == 'a')
			mout << std::right << setw(4) << "acc";
		else
			mout << std::right << setw(4) << b;
		store[k++] = action[num][Mplower[a] - 1].first;
		mout << "     ";
		err = 0;
		if (action[num][Mplower[a] - 1].first == 's')
		{
			S.push(j);
			s.erase(s.begin());
		}
		else if (action[num][Mplower[a] - 1].first == 'r')
		{
			for (i = 0; grammar_r[j - 1][i] != '\0' && grammar_r[j - 1][i] != '~'; i++)
				S.pop();
			S.push(mat1[S.top()][Mpupper[grammar_l[j - 1]] - 1]);
			mout << grammar_l[j - 1] << "->" << grammar_r[j - 1];
			productions_l[final_number] = grammar_l[j - 1];
			strcpy(productions_r[final_number], grammar_r[j - 1]);
			final_number++;
		}
		else if (action[num][Mplower[a] - 1].first == 'e')
		{
			mout << "Error" << endl;
			err++;
			break;
		}
		else
		{
			mout << "Accept" << endl;
			break;
		}
		mout << endl;
	}
	store[k++] = '\0';
	mout << "__________________________________________________________________________\n";
	mout << endl;

	//-------------------STEP VI RIGHTMOST DERIVATION IN REVERSE ORDER AND PARSE TREE---------------------------------------------------------------
	if (!err)
	{
		int len, q;
		len = input.length();
		stack<string>temp_stack;
		string x = productions_r[final_number - 1];
		temp_stack.push(x);
		string y, z, u;
		for (i = final_number - 2; i >= 0; i--)
		{
			size_t found = x.find_last_of(productions_l[i]);
			f[final_number - 2 - i + 1] = found;
			y = x.substr(0, found);
			z = x.substr(found + 1);
			u = productions_r[i];
			x = y + u + z;
			temp_stack.push(x);
		}
		/*--------------------------------PARSE TREE-----------------------------------*/
		if (err == 0)
		{
			for (int i = 0; i < 10; i++)
				ar[i] = 1;
			string y, z;
			for (i = final_number - 1; i >= 0; i--)
			{
				y = productions_l[i];
				z = productions_r[i];
				produc.push_back(y + "->" + z);
			}
			it8 = produc.begin();
			mout << "-------------------------------PARSE TREE---------------------------------\n\n";
			parseTree(ss, 0);
		}
		mout << "\n--------------------RIGHTMOST DERIVATION IN REVERSE ORDER-----------------\n\n";
		for (i = final_number - 1; i >= 0; i--)
		{
			y = temp_stack.top();
			temp_stack.pop();
			mout << y << "<=";
		}
		mout << ss << "<=Z\n";
	}
	mout.close();
}
