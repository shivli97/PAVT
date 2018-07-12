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

using namespace std;

map<char, int> Mp_1, Mpgoto_1, Mpupper_1, Mplower_1;
map<char, int> ::iterator iter_1;
ofstream mout_1;

int n1 , ns_1, tn_1, rr_1, ctr_1;
char grammar_l_1[50], grammar_r_1[50][30], templ_1[50], tempr_1[50][30], *ptr_1, temp2_1[5], mat_1[50][50];
char productions_l_1[50], productions_r_1[50][30], ss_1, buffer_1[5], store_1[1000], st[30];
int err_1, space_1, cnt2_1, cnt3_1, cnt_1, cnt1_1;
string input_1;

//item_sets are the states of the LR automation
list<string> produc_1;
list<string> ::iterator it7_1;
static list<string> ::iterator it8_1;
/*head->body*/

struct prod_1
{
	char head;
	string body;
};

struct item_sets_1
{   //LHS and RHS indicate left and right sides of the productions. Left side is a nonterminal(single character)
	char lhs[50], rhs[50][50];
	//Symbol on which the state has a transition
	char sym;
	//No. of productions in a given state
	int n;
	//List of terminals associated with each production
	char lookahead[50][50];
}I1[100];


int compare_struct1(item_sets_1 s1, item_sets_1 s2)
{
	int t;
	if (s1.n != s2.n)
		return 0;
	if (strcmp(s1.lhs, s2.lhs) != 0)
		return 0;
	for (t = 0; t<s1.n; t++)
		if (strcmp(s1.rhs[t], s2.rhs[t]) != 0)
			return 0;
	return 1;
}
//This finds the closure of the item sets in a given state after the GOTO function
//To add more productions
void Closure1()
{
	int r, s, t, l1 = 0, rr1 = 0,temp;
	char *ptr1, read1[50][30];

	for (r = 0; r<I1[ns_1].n; r++)
	{
		ptr1 = strchr(I1[ns_1].rhs[l1], '.');
		t = ptr1 - I1[ns_1].rhs[l1];
		if (t + 1 == strlen(I1[ns_1].rhs[l1]))
		{
			l1++;
			continue;
		}
		temp = I1[ns_1].rhs[l1][t + 1];
		l1++;
		for (s = 0; s<rr1; s++)
			if (temp == read1[s][0])
				break;
		if (s == rr1)
		{
			read1[rr1][0] = temp;
			rr1++;
		}
		else
			continue;

		for (s = 0; s<n1; s++)
		{
			if (grammar_l_1[s] == temp)
			{
				I1[ns_1].rhs[I1[ns_1].n][0] = '.';
				I1[ns_1].rhs[I1[ns_1].n][1] = NULL;
				strcat(I1[ns_1].rhs[I1[ns_1].n], grammar_r_1[s]);
				I1[ns_1].lhs[I1[ns_1].n] = grammar_l_1[s];
				I1[ns_1].lhs[I1[ns_1].n + 1] = NULL;
				I1[ns_1].n++;
			}
		}
	}
}

void Goto1(int l)
{
	int t1,j,i;
	char read1[50][30], rr1 = 0, *ptr1;
	tn_1 = 0;
	for (i = 0; i<I1[l].n; i++)
	{
		temp2_1[0] = '.';
		ptr1 = strchr(I1[l].rhs[i], '.');
		if (ptr1[1] == '~')
			continue;
		t1 = ptr1 - I1[l].rhs[i];
		if (t1 + 1 == strlen(I1[l].rhs[i]))
			continue;
		temp2_1[1] = I1[l].rhs[i][t1 + 1];
		temp2_1[2] = NULL;
		for (j = 0; j<rr1; j++)
			if (strcmp(temp2_1, read1[j]) == 0)
				break;
		if (j == rr1)
		{
			strcpy(read1[rr1], temp2_1);
			read1[rr1][2] = NULL;
			rr1++;
		}
		else
			continue;
		for (j = 0; j<I1[l].n; j++)
		{
			ptr_1 = strstr(I1[l].rhs[j], temp2_1);
			if (ptr_1)
			{
				templ_1[tn_1] = I1[l].lhs[j];
				templ_1[tn_1 + 1] = NULL;
				strcpy(tempr_1[tn_1], I1[l].rhs[j]);
				tn_1++;
			}
		}
		for (j = 0; j<tn_1; j++)
		{
			ptr_1 = strchr(tempr_1[j], '.');
			int p = ptr_1 - tempr_1[j];
			tempr_1[j][p] = tempr_1[j][p + 1];
			tempr_1[j][p + 1] = '.';
			I1[ns_1].lhs[I1[ns_1].n] = templ_1[j];
			I1[ns_1].lhs[I1[ns_1].n + 1] = NULL;
			strcpy(I1[ns_1].rhs[I1[ns_1].n], tempr_1[j]);
			I1[ns_1].n++;
		}

		Closure1();
		for (j = 0; j<ns_1; j++)
		{
			if (compare_struct1(I1[ns_1], I1[j]) == 1)
			{
				I1[ns_1].lhs[0] = NULL;
				for (int k = 0; k<I1[ns_1].n; k++)
					I1[ns_1].rhs[k][0] = NULL;
				I1[ns_1].n = 0;
				mat_1[l][j] = temp2_1[1];
				break;
			}
		}
		if (j<ns_1)
		{
			tn_1 = 0;
			for (j = 0; j<50; j++)
			{
				templ_1[j] = NULL;
				tempr_1[j][0] = NULL;
			}
			continue;
		}
		mat_1[l][j] = ptr1[1];
		I1[ns_1].sym = ptr1[1];
		if (!isupper(I1[ns_1].sym))
			Mpgoto_1[I1[ns_1].sym] = ns_1;
		//Printing
		//This is the symbol on which the state has a transition(LR automation
		ns_1++;
		tn_1 = 0;
		for (j = 0; j<50; j++)
		{
			templ_1[j] = NULL;
			tempr_1[j][0] = NULL;
		}
	}
}

int ar1[10] = { 1,1,1,1,1,1,1,1,1,1 };
void parseTree1(char X, int l) 
{
	int lev = l;
	for (int i = 0; i<10; i++)
	{
		if (lev - 1 >0) {}
		else break;
		if (ar1[i] == 1) mout_1 << "| ";
		else mout_1 << "  ";
		lev--;
	}
	if (lev == 1)
		mout_1 << "|_";
	else if (lev>0)
	{
		for (int z = 0; z<lev - 1; z++)
			mout_1 << "  ";
		mout_1 << "|_";
	}
	mout_1 << X << endl;
	if (X<'A' || X>'Z')
		return;
	for (it7_1 = it8_1; it7_1 != produc_1.end(); it7_1++) {
		string p = (*it7_1);
		if (p[0] == X) {
			it8_1 = ++it7_1;
			string s = p.substr(3);
			int len = s.length();
			for (int j = 0; j<len; j++) {
				if (len - 1 == j)
					ar1[l] = 0;
				parseTree1(s[len - 1 - j], l + 1);
				ar1[l] = 1;
				if (len - 1 != j) {
					int lev = l + 1;
					for (int i = 0; i<10; i++) {
						if (lev >0) {}
						else break;
						if (ar1[i] == 1) mout_1 << "| ";
						else mout_1 << "  ";
						lev--;
					}
					mout_1 << endl;
				}
			}
			break;
		}
	}
	return;
}
int maxLenP_1;
int siz_1;
prod_1 *arr_1 = new prod_1[100];


void slr()
{
	string s;
	ifstream myfile("grammar.txt");
	int i = 0;
	arr_1[i].head = 'Z';
	i++;
	n1 = 0;
	mout_1.open("output.txt");
	maxLenP_1 = 0;
	while (!myfile.eof())
	{
		getline(myfile, s);
		arr_1[i].head = s[0];
		arr_1[0].body = arr_1[1].head;
		int len = s.length();
		/*Allows extra line at the end*/
		if (len>maxLenP_1) maxLenP_1 = len;
		if (len == 0)
			break;
		arr_1[i].body = s.substr(3);
		//body starts from position 3
		i++;
		grammar_l_1[n1] = s[0];
		int j = 3;
		while (s[j] != '\0')
			grammar_r_1[n1][j - 3] = s[j++];
		grammar_r_1[n1][j - 3] = '\0';
		//mout_1 << grammar_r_1[n1] << endl;
		n1++;
	}
	myfile.close();
	/* # Productions*/
	siz_1 = i;
		
	mout_1 << "-----------------------------AUGMENTED GRAMMAR-----------------------------\n\n";
	for (int j = 0; j<siz_1; j++)
		mout_1 << j + 1 << ". " << arr_1[j].head << "->" << arr_1[j].body << endl;
	/*-----------------------------------STEP I: CALCULATE FIRSTS----------------------------------*/
	/* SORTING OF PRODUCTIONS */
	/* 'ldash' stores productions in topologically sorted manner */
	vector< pair<char, string> > l, ldash;
	vector< pair<char, string> >::iterator it, it1,itemp;
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
	for (int i = 0; i<siz_1; i++)
	{
		string s = arr_1[i].body;
		if (s[0] == '~')
		{
			epsilon[arr_1[i].head - 'A'] = 1;
			ldash.push_back(make_pair(arr_1[i].head, s));
		}
		else if (s[0]<'A' || s[0]>'Z') {
			ldash.push_back(make_pair(arr_1[i].head, s));
		}
		else {
			l.push_back(make_pair(arr_1[i].head, s));
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
			int len = s.length(), flag1=0;
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
	map< char, list<char> > firsts;
	map< char, list<char> > ::iterator ind1, ind2;
	list<char>::iterator it2;

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
					int cnt = 0;
					ind2 = firsts.find(s[i]);
					list<char>::iterator lit;
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
	for (int i = 0; i<siz_1; i++)
	{
		string s = arr_1[i].body;
		for (int j = 0; j<s.length(); j++)
			if (s[j]<'A' || s[j]>'Z')
				term.push_back(s[j]);
	}
	term.sort();
	term.unique();
	term.remove('~');

	/* printing firsts */
	map< char, list<char> > ::iterator mit;
	mout_1 << "\n--------------------------------FIRST SETS---------------------------------\n\n";
	for (mit = firsts.begin(); mit != firsts.end(); mit++)
	{
		((*mit).second).sort();
		((*mit).second).unique();
		mout_1 << "FIRST(" << (*mit).first << ") = { ";
		list<char> ::iterator lit;
		for (lit = ((*mit).second).begin(); lit != ((*mit).second).end(); lit++)
		{
			if (lit == ((*mit).second).begin()) mout_1 << *lit;
			else mout_1 << ", " << *lit;
		}
		mout_1 << " }" << endl;
	}

	for (ti = term.begin(); ti != term.end(); ti++)
	{
		mout_1 << "FIRST(" << (*ti) << ") = { " << (*ti) << " }" << endl;
	}
	mout_1 << endl;
	mout_1.close();

	/*----------------------------------STEP II: FOLLOW----------------------------------*/
	vector< pair< string, pair<char, int> > > pairs, pdash;
	vector<pair<string, pair<char, int> > >::iterator itp, itp1;

	/*Forming pairs: A->aBc, B, ind */
	for (int i = 0; i<siz_1; i++)
	{
		/* s = 'A->aBc' */
		string s;
		s.push_back(arr_1[i].head);
		s += "->";
		s += arr_1[i].body;
		/* stores body of production */
		string t = arr_1[i].body;
		int len = t.length();
		for (int j = 0; j<len; j++)
		{
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
		if (pos == len - 1) continue;
		for (int i = pos + 1; i<len; i++)
		{
			//IF s[i] IS A NON-TERMINAL
			if (s[i]<'A' || s[i]>'Z')
			{
				pdash.push_back(*itp);
				itp = pairs.erase(itp);
				itp--;
				break;
			}
			else
			{//s[i] IS A TERMINAL
				if (epsilon[s[i] - 'A'] != 1)
				{
					pdash.push_back(*itp);
					itp = pairs.erase(itp);
					itp--;
					break;
				}
				else break;
			}
		}
	}
	mout_1.open("output.txt", ios_base::app);
	mout_1 << "-------------------------------FOLLOW SETS---------------------------------\n\n";

	while (!pairs.empty())
	{
		int sizi = pairs.size();
		for (itp = pairs.begin(); itp<pairs.end();)
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
	
	/*FOLLOW CALCULATION*/
	map<char, list<char> > follows;
	map<char, list<char> >::iterator mit1, mit2, mit3;
	list<char> t;
	t.push_back('$');
	char blah = arr_1[0].head;
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
				//mout<<s[i]<<endl;
				//IF s[i] IS A TERMINAL
				if (s[i]<'A' || s[i]>'Z')
				{
					((*mit).second).push_back(s[i]);
					//mout<<s[i]<<endl;
					break;
				}
				else
				{
					//IF s[i] IS A NON-TERMINAL
					mit1 = firsts.find(s[i]);
					list<char> ::iterator lit;
					for (lit = ((*mit1).second).begin(); lit != ((*mit1).second).end(); lit++)
						if ((*lit) != '~')
							((*mit).second).push_back(*lit);
					if (epsilon[s[i] - 'A'] == 0) break;
					else flag = 1;
				}
			}
		}

		mit2 = follows.find(A);
		if (mit2 == follows.end())
		{
			list<char> temp;
			follows.insert(make_pair(A, temp));
		}
		mit2 = follows.find(A);
		mit = follows.find(B);
		if (mit2 == mit) continue;
		if (pos == len - 1 || flag == 1)
		{
			list<char> ::iterator lit;
			for (lit = ((*mit2).second).begin(); lit != ((*mit2).second).end(); lit++)
				((*mit).second).push_back(*lit);
		}
	}
	/*PRINTING FOLLOW TO SCREEN*/
	int num = 1;
	list<char> ::iterator lit;
	for (mit = follows.begin(); mit != follows.end(); mit++)
	{
		((*mit).second).sort();
		((*mit).second).unique();
		mout_1 << "FOLLOW(" << (*mit).first << ") = { ";
		for (lit = ((*mit).second).begin(); lit != ((*mit).second).end(); lit++)
			if (lit == ((*mit).second).begin())
				mout_1 << *lit;
			else
				mout_1 << ", " << *lit;
		mout_1 << " }" << endl;
	}
	mout_1.close();

	/*----------------------------------STEP III: ITEM SETS----------------------------------*/

	int l1,temp;
	for (i = 0; i<50; i++)
	{
		I1[i].n = 0;
		I1[i].lhs[0] = NULL;
		for (int j = 0; j<50; j++)
			I1[i].rhs[j][0] = NULL;
	}

	mout_1.open("output.txt", ios_base::app);
	ss_1 = grammar_l_1[0];
	//Original starting symbol is S and the new starting symbol is Q.
	I1[0].lhs[0] = 'Z';
	char as[2];
	as[0] = '.', as[1] = ss_1, as[2] = '\0';
	strcpy(I1[0].rhs[0], as);
	I1[0].n++;
	l1 = 0;
	char read[50][30];
	rr_1 = 0;
	for (i = 0; i<n1; i++)
	{
		temp = I1[0].rhs[l1][1];
		l1++;
		int j;
		for (j = 0; j<rr_1; j++)
			if (temp == read[j][0])
				break;
		if (j == rr_1)
		{
			read[rr_1][0] = temp;
			rr_1++;
		}
		else
			continue;
		for (j = 0; j<n1; j++)
		{
			if (grammar_l_1[j] == temp)
			{
				I1[0].rhs[I1[0].n][0] = '\0';
				I1[0].rhs[I1[0].n][0] = '.';
				for (int k = 0; grammar_r_1[j][k] != '\0'; k++)
				{
					I1[0].rhs[I1[0].n][k+1]=grammar_r_1[j][k];
				}
				I1[0].lhs[I1[0].n] = grammar_l_1[j];
				I1[0].n++;
			}
		}
	}
	ns_1=1;
	//Printing I0
	mout_1 << "\n---------------------------------ITEM SETS---------------------------------\n\n";
	mout_1 << "CLOSURE({[" << I1[0].lhs[0] << "->" << I1[0].rhs[0] << "]})={";
	for (i = 0; i<I1[0].n - 1; i++)
		mout_1 << "[" << I1[0].lhs[i] << "->" << I1[0].rhs[i] << "],";
	mout_1 << "[" << I1[0].lhs[i] << "->" << I1[0].rhs[i] << "]}=";
	mout_1 << "I" << ns_1 - 1 << endl << endl;
	for (l1 = 0; l1<ns_1; l1++)
		Goto1(l1);
	//PRINTING ITEM SETS
	for (i = 0; i<ns_1; i++)
	{
		ctr_1 = 0;
		for (int j = 0; j<ns_1; j++)
		{
			if (mat_1[i][j])
				ctr_1++;
		}
		if (ctr_1)
		{
			mout_1 << "I" << i << "={";
			int k;
			for (k = 0; k<I1[i].n - 1; k++)
				mout_1 << "[" << I1[i].lhs[k] << "->" << I1[i].rhs[k] << "],";
			mout_1 << "[" << I1[i].lhs[k] << "->" << I1[i].rhs[k] << "]}" << endl;
		}
		else continue;
		for (int j = 0; j<ns_1; j++)
		{
			if (mat_1[i][j])
			{
				mout_1 << "GOTO(I" << i << "," << mat_1[i][j] << ")";
				mout_1 << "={";
				int k;
				for (k = 0; k<I1[j].n - 1; k++)
					mout_1 << "[" << I1[j].lhs[k] << "->" << I1[j].rhs[k] << "],";
				mout_1 << "[" << I1[j].lhs[k] << "->" << I1[j].rhs[k] << "]}=I" << j << endl;
			}
		}
		mout_1 << endl;
	}
	/*----------------------------------STEP IV: PARSING TABLE----------------------------------*/
	Mp_1.clear(); Mpgoto_1.clear(); Mplower_1.clear(); Mpupper_1.clear();
	mout_1 << "-----------------------------PARSING TABLE---------------------------------\n\n";
	cnt1_1 = 0; cnt_1 = 1;
	for (i = 0; i<n1; i++)
	{
		Mp_1[grammar_l_1[i]] = 1; //non-terminal
		cnt1_1++;
	}

	for (i = 0; i<n1; i++)
	{
		for (int j = 0; grammar_r_1[i][j] != '\0'; j++)
			if (Mp_1.find(grammar_r_1[i][j]) == Mp_1.end())
			{
				Mp_1[grammar_r_1[i][j]] = 0;  //terminal
				cnt_1++;
			}
	}
	Mp_1['$'] = 0;
	cnt2_1 = 0; cnt3_1 = 0;
	for (iter_1 = Mp_1.begin(); iter_1 != Mp_1.end(); iter_1++)
	{
		if (iter_1->second == 1)
			Mpupper_1[iter_1->first] = ++cnt2_1;
		else
			Mplower_1[iter_1->first] = ++cnt3_1;
	}
	mout_1 << "_______";
	for (i = 0; i<6 * (cnt2_1 + cnt3_1) + 4; i++)
		mout_1 << "_";
	mout_1 << endl<< "STATE"<< setw(4 * cnt_1) << "ACTION";
	mout_1 << setw(4 * cnt1_1) << "GOTO" << endl;
	mout_1 << "_______";
	for (i = 0; i<6 * (cnt2_1 + cnt3_1) + 4; i++)
		mout_1 << "_";
	mout_1 << "\n      |";
	for (iter_1 = Mp_1.begin(); iter_1 != Mp_1.end(); iter_1++)
		if (iter_1->second == 0)
			mout_1 << setw(6) << iter_1->first;
	mout_1 << " |";
	for (iter_1 = Mp_1.begin(); iter_1 != Mp_1.end(); iter_1++)
		if (iter_1->second == 1)
			mout_1 << setw(6) << iter_1->first;
	mout_1 << endl;
	mout_1 << "______|";
	for (i = 0; i<6 * (cnt3_1); i++)
		mout_1 << "_";
	mout_1 << "_|";
	for (i = 0; i<6 * (cnt2_1)+2; i++)
		mout_1 << "_";
	mout_1 << endl;	
	int mat1[100][100];
	for (i = 0; i<ns_1; i++)
		for (int j = 0; j<cnt2_1; j++)
			mat1[i][j] = -1;
	pair<char, int> action[100][100];
	for (i = 0; i<ns_1; i++)
		for (int j = 0; j<cnt_1; j++)
			action[i][j] = make_pair('e', 0);
	for (i = 0; i<ns_1; i++)
		for (int j = 0; j<ns_1; j++)
			if (mat_1[i][j] != '\0')
			{
				if (Mpupper_1[mat_1[i][j]] != 0)
					mat1[i][Mpupper_1[mat_1[i][j]] - 1] = j;
				else if (Mplower_1[mat_1[i][j]] != 0)
					action[i][Mplower_1[mat_1[i][j]] - 1] = make_pair('s', j);
			}
	char str[30];
	str[0] = ss_1;
	str[1] = '.';
	str[2] = '\0';
	for (i = 0; i<ns_1; i++)
	{
		for (int j = 0; j<I1[i].n; j++)
		{
			if (I1[i].lhs[j] == 'Z' && strcmp(I1[i].rhs[j], str) == 0)
			{
				action[i][Mplower_1['$'] - 1] = make_pair('a', 0);
				continue;
			}
			char *ptr1 = strchr(I1[i].rhs[j], '.');
			ptr1++;
			if (*ptr1 == '\0' || *ptr1 == '~')
			{
				for (int k = 0; k<n1; k++)  //traversing all productions
				{
					if (*ptr1 == '\0')
					{
						int ch;
						for (ch = 0; grammar_r_1[k][ch] != '\0'; ch++)
							st[ch] = grammar_r_1[k][ch];
						st[ch] = '\0';
						strcat(st, ".");
						if (grammar_l_1[k] == I1[i].lhs[j] && strcmp(st, I1[i].rhs[j]) == 0)
						{
							num = k + 1;
							break;
						}
					}
					else if (grammar_l_1[k] == I1[i].lhs[j] && grammar_r_1[k][0] == '~')
					{
						num = k + 1;
						break;
					}
				}
				mit = follows.find(I1[i].lhs[j]);
				for (lit = (*mit).second.begin(); lit != (*mit).second.end(); lit++)
					action[i][Mplower_1[(*lit)] - 1] = make_pair('r', num);
			}
		}
	}

	for (int i = 0; i<ns_1; i++)
	{
		mout_1 << setw(6) << i << "|";
		for (int j = 0; j<cnt_1; j++)
		{
			if (action[i][j].first == 'e')
				mout_1 << "      ";
			else if (action[i][j].first == 'a')
				mout_1 << "   acc";
			else
			{
				str[0] = action[i][j].first;
				str[1] = '\0';
				strcat(str, itoa(action[i][j].second, buffer_1, 10));
				mout_1 << setw(6) << str;
			}
		}
		mout_1 << setw(2) << '|';
		for (int j = 0; j<cnt2_1; j++)
			if (mat1[i][j] == -1)
				mout_1 << "      ";
			else
			{
				itoa(mat1[i][j], buffer_1, 10);
				mout_1 << setw(6) << buffer_1;
			}
		mout_1 << endl;
	}
	mout_1 << "_______";
	for (i = 0; i<6 * (cnt2_1 + cnt3_1)+4; i++)
		mout_1 << "_";
	mout_1 << endl;
	mout_1.close();

	/*---------------------------------STEP V: LR PARSING ALGO---------------------------------*/

	myfile.open("details.txt");
	getline(myfile, s);
	myfile.close();
	
	input_1 = s;
	char a, b[10];
	s += "$";
	int final_number = 0;
	stack<int> S, Stemp;
	S.push(0);
	mout_1.open("output.txt", ios_base::app);
	mout_1 << "\n--------------------------TABLE DRIVEN PARSING---------------------------\n\n";
	mout_1 << "__________________________________________________________________________\n";
	mout_1 << std::left << setw(30) << "STACK";
	mout_1 << std::left << setw(22) << "INPUT";
	mout_1 << " ACTION     PRODUCTION" << endl;
	mout_1 << "__________________________________________________________________________\n";
	int k = 0;
	while (1)
	{
		space_1 = 30;
		a = s[0];
		num = S.top();
		b[0] = action[num][Mplower_1[a] - 1].first;
		b[1] = '\0';
		int j = action[num][Mplower_1[a] - 1].second;

		while (!S.empty())
		{
			Stemp.push(S.top());
			S.pop();
		}
		while (!Stemp.empty())
		{
			mout_1 << Stemp.top() << ' ';
			itoa(Stemp.top(), buffer_1, 10);
			space_1 -= (strlen(buffer_1) + 1);
			S.push(Stemp.top());
			Stemp.pop();
		}
		while (space_1>0)
		{
			mout_1 << " ";
			space_1--;
		}
		mout_1 << std::left << setw(25) << s;
		itoa(j, temp2_1, 10);
		strcat(b, temp2_1);
		if (action[num][Mplower_1[a] - 1].first == 'a')
			mout_1 << std::right << setw(4) << "acc";
		else
			mout_1 << std::right << setw(4) << b;
		store_1[k++] = action[num][Mplower_1[a] - 1].first;
		mout_1 << "     ";
		err_1 = 0;
		if (action[num][Mplower_1[a] - 1].first == 's')
		{
			S.push(j);
			s.erase(s.begin());
		}
		else if (action[num][Mplower_1[a] - 1].first == 'r')
		{
			for (i = 0; grammar_r_1[j - 1][i] != '\0' && grammar_r_1[j - 1][i] != '~'; i++)
				S.pop();
			S.push(mat1[S.top()][Mpupper_1[grammar_l_1[j - 1]] - 1]);
			mout_1 << grammar_l_1[j - 1] << "->" << grammar_r_1[j - 1];
			productions_l_1[final_number] = grammar_l_1[j - 1];
			strcpy(productions_r_1[final_number], grammar_r_1[j - 1]);
			final_number++;
		}
		else if (action[num][Mplower_1[a] - 1].first == 'e')
		{
			mout_1 << "Error" << endl;
			err_1++;
			break;
		}
		else
		{
			mout_1 << "Accept" << endl;
			break;
		}
		mout_1 << endl;
	}
	store_1[k++] = '\0';
	mout_1 << "__________________________________________________________________________\n";
	mout_1 << endl;

	//-------------------STEP VI RIGHTMOST DERIVATION IN REVERSE ORDER AND PARSE TREE---------------------------------------------------------------
	if (!err_1)
	{
		int len, q;
		len = input_1.length();
		stack<string>temp_stack;
		string x = productions_r_1[final_number - 1];
		temp_stack.push(x);
		string y, z, u;
		for (i = final_number - 2; i >= 0; i--)
		{
			size_t found = x.find_last_of(productions_l_1[i]);
			y = x.substr(0, found);
			z = x.substr(found + 1);
			u = productions_r_1[i];
			x = y + u + z;
			temp_stack.push(x);
		}
		/*--------------------------------PARSE TREE-----------------------------------*/
		if (err_1 == 0) {
			for (int i = 0; i < 10; i++)
				ar1[i] = 1;
			string y, z;
			for (i = final_number - 1; i >= 0; i--)
			{
				y = productions_l_1[i];
				z = productions_r_1[i];
				produc_1.push_back(y + "->" + z);
			}
			it8_1 = produc_1.begin();
			mout_1 << "-------------------------------PARSE TREE---------------------------------\n\n";
			parseTree1(ss_1, 0);
		}
		mout_1 << "\n--------------------RIGHTMOST DERIVATION IN REVERSE ORDER-----------------\n\n";
		for (i = final_number - 1; i >= 0; i--)
		{
			y = temp_stack.top();
			temp_stack.pop();
			mout_1 << y << "<=";
		}
		mout_1 << ss_1 << "<=Z\n";
	}
	mout_1.close();
	for (i = 0; i<50; i++)
	{
		I1[i].n = 0;
		I1[i].lhs[0] = NULL;
		for (int j = 0; j<50; j++)
			I1[i].rhs[j][0] = NULL;
	}
}
