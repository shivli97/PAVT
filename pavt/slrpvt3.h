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

map<char, int> Mp_1st, Mpgoto_1st, Mpupper_1st, Mplower_1st;
map<char, int> ::iterator iter_1st;
ofstream mout_1st,mx;

int n1_1st , ns_1st, tn_1st, rr_1st, ctr_1st;
char grammar_l_1st[50], grammar_r_1st[50][30], templ_1st[50], tempr_1st[50][30], *ptr_1st, temp2_1st[5], mat_1st[50][50];
char productions_l_1st[50], productions_r_1st[50][30], ss_1st, buffer_1st[5], store_1st[1000], st_1st[30];
int err_1st, space_1st, cnt2_1st, cnt3_1st, cnt_1st, cnt1_1st;
string input_1st;

//item_sets are the states of the LR automation
list<string> produc_1st;
list<string> ::iterator it7_1st, it9_1st;
static list<string> ::iterator it8_1st;
/*head->body*/

struct prod_1st
{
	char head;
	string body;
};

struct item_sets_1st
{   //LHS and RHS indicate left and right sides of the productions. Left side is a nonterminal(single character)
	char lhs[50], rhs[50][50];
	//Symbol on which the state has a transition
	char sym;
	//No. of productions in a given state
	int n;
	//List of terminals associated with each production
	char lookahead[50][50];
}I1_st[100];


int compare_struct1(item_sets_1st s1, item_sets_1st s2)
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
void Closure3()
{
	int r, s, t, l1 = 0, rr1 = 0,temp;
	char *ptr1, read1[50][30];

	for (r = 0; r<I1_st[ns_1st].n; r++)
	{
		ptr1 = strchr(I1_st[ns_1st].rhs[l1], '.');
		t = ptr1 - I1_st[ns_1st].rhs[l1];
		if (t + 1 == strlen(I1_st[ns_1st].rhs[l1]))
		{
			l1++;
			continue;
		}
		temp = I1_st[ns_1st].rhs[l1][t + 1];
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

		for (s = 0; s<n1_1st; s++)
		{
			if (grammar_l_1st[s] == temp)
			{
				I1_st[ns_1st].rhs[I1_st[ns_1st].n][0] = '.';
				I1_st[ns_1st].rhs[I1_st[ns_1st].n][1] = NULL;
				strcat(I1_st[ns_1st].rhs[I1_st[ns_1st].n], grammar_r_1st[s]);
				I1_st[ns_1st].lhs[I1_st[ns_1st].n] = grammar_l_1st[s];
				I1_st[ns_1st].lhs[I1_st[ns_1st].n + 1] = NULL;
				I1_st[ns_1st].n++;
			}
		}
	}
}

void Goto3(int l)
{
	int t1,j,i;
	char read1[50][30], rr1 = 0, *ptr1;
	tn_1st = 0;
	for (i = 0; i<I1_st[l].n; i++)
	{
		temp2_1st[0] = '.';
		ptr1 = strchr(I1_st[l].rhs[i], '.');
		if (ptr1[1] == '~')
			continue;
		t1 = ptr1 - I1_st[l].rhs[i];
		if (t1 + 1 == strlen(I1_st[l].rhs[i]))
			continue;
		temp2_1st[1] = I1_st[l].rhs[i][t1 + 1];
		temp2_1st[2] = NULL;
		for (j = 0; j<rr1; j++)
			if (strcmp(temp2_1st, read1[j]) == 0)
				break;
		if (j == rr1)
		{
			strcpy(read1[rr1], temp2_1st);
			read1[rr1][2] = NULL;
			rr1++;
		}
		else
			continue;
		for (j = 0; j<I1_st[l].n; j++)
		{
			ptr_1st = strstr(I1_st[l].rhs[j], temp2_1st);
			if (ptr_1st)
			{
				templ_1st[tn_1st] = I1_st[l].lhs[j];
				templ_1st[tn_1st + 1] = NULL;
				strcpy(tempr_1st[tn_1st], I1_st[l].rhs[j]);
				tn_1st++;
			}
		}
		for (j = 0; j<tn_1st; j++)
		{
			ptr_1st = strchr(tempr_1st[j], '.');
			int p = ptr_1st - tempr_1st[j];
			tempr_1st[j][p] = tempr_1st[j][p + 1];
			tempr_1st[j][p + 1] = '.';
			I1_st[ns_1st].lhs[I1_st[ns_1st].n] = templ_1st[j];
			I1_st[ns_1st].lhs[I1_st[ns_1st].n + 1] = NULL;
			strcpy(I1_st[ns_1st].rhs[I1_st[ns_1st].n], tempr_1st[j]);
			I1_st[ns_1st].n++;
		}

		Closure3();
		for (j = 0; j<ns_1st; j++)
		{
			if (compare_struct1(I1_st[ns_1st], I1_st[j]) == 1)
			{
				I1_st[ns_1st].lhs[0] = NULL;
				for (int k = 0; k<I1_st[ns_1st].n; k++)
					I1_st[ns_1st].rhs[k][0] = NULL;
				I1_st[ns_1st].n = 0;
				mat_1st[l][j] = temp2_1st[1];
				break;
			}
		}
		if (j<ns_1st)
		{
			tn_1st = 0;
			for (j = 0; j<50; j++)
			{
				templ_1st[j] = NULL;
				tempr_1st[j][0] = NULL;
			}
			continue;
		}
		mat_1st[l][j] = ptr1[1];
		I1_st[ns_1st].sym = ptr1[1];
		if (!isupper(I1_st[ns_1st].sym))
			Mpgoto_1st[I1_st[ns_1st].sym] = ns_1st;
		//Printing
		//This is the symbol on which the state has a transition(LR automation
		ns_1st++;
		tn_1st = 0;
		for (j = 0; j<50; j++)
		{
			templ_1st[j] = NULL;
			tempr_1st[j][0] = NULL;
		}
	}
}
int maxLenP_1st;
int siz_1st;
prod_1st *arr_1st = new prod_1st[100];


list<string> slr1(string file_name, string details)
{
	string s;
	ifstream myfile((file_name + ".txt").c_str());
	int i = 0;
	arr_1st[i].head = 'O';
	i++;
	n1_1st = 0;
	maxLenP_1st = 0;
	while (!myfile.eof())
	{
		getline(myfile, s);
		arr_1st[i].head = s[0];
		arr_1st[0].body = arr_1st[1].head;
		int len = s.length();
		/*Allows extra line at the end*/
		if (len>maxLenP_1st) maxLenP_1st = len;
		if (len == 0)
			break;
		arr_1st[i].body = s.substr(3);
		//body starts from position 3
		i++;
		grammar_l_1st[n1_1st] = s[0];
		int j = 3;
		while (s[j] != '\0')
			grammar_r_1st[n1_1st][j - 3] = s[j++];
		grammar_r_1st[n1_1st][j - 3] = '\0';
		//mout_1st << grammar_r_1st[n1_1st] << endl;
		n1_1st++;
	}
	myfile.close();
	/* # Productions*/
	siz_1st = i;
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
	for (int i = 0; i<siz_1st; i++)
	{
		string s = arr_1st[i].body;
		if (s[0] == '~')
		{
			epsilon[arr_1st[i].head - 'A'] = 1;
			ldash.push_back(make_pair(arr_1st[i].head, s));
		}
		else if (s[0]<'A' || s[0]>'Z') {
			ldash.push_back(make_pair(arr_1st[i].head, s));
		}
		else {
			l.push_back(make_pair(arr_1st[i].head, s));
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
	for (int i = 0; i<siz_1st; i++)
	{
		string s = arr_1st[i].body;
		for (int j = 0; j<s.length(); j++)
			if (s[j]<'A' || s[j]>'Z')
				term.push_back(s[j]);
	}
	term.sort();
	term.unique();
	term.remove('~');

	/* printing firsts */
	map< char, list<char> > ::iterator mit;
	/*----------------------------------STEP II: FOLLOW----------------------------------*/
	vector< pair< string, pair<char, int> > > pairs, pdash;
	vector<pair<string, pair<char, int> > >::iterator itp, itp1;

	/*Forming pairs: A->aBc, B, ind */
	for (int i = 0; i<siz_1st; i++)
	{
		/* s = 'A->aBc' */
		string s;
		s.push_back(arr_1st[i].head);
		s += "->";
		s += arr_1st[i].body;
		/* stores body of production */
		string t = arr_1st[i].body;
		int len = t.length();
		for (int j = 0; j<len; j++)
		{
			if (t[j] >= 'A' && t[j] <= 'Z')
				pairs.push_back(make_pair(s, make_pair(t[j], j + 3)));
		}
	}

	/*SORTING OF PRODUCTION PAIRS in 'pdash' */
	for (itp = pairs.begin(); itp<pairs.end(); itp++) {
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
				else break;;
			}
		}
	}
	
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
	char blah = arr_1st[0].head;
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
	
	/*----------------------------------STEP III: ITEM SETS----------------------------------*/

	int l1,temp;
	for (i = 0; i<50; i++)
	{
		I1_st[i].n = 0;
		I1_st[i].lhs[0] = NULL;
		for (int j = 0; j<50; j++)
			I1_st[i].rhs[j][0] = NULL;
	}
	ss_1st = grammar_l_1st[0];
	//Original starting symbol is S and the new starting symbol is Q.
	I1_st[0].lhs[0] = 'O';
	char as[2];
	as[0] = '.', as[1] = ss_1st, as[2] = '\0';
	strcpy(I1_st[0].rhs[0], as);
	I1_st[0].n++;
	l1 = 0;
	char read[50][30];
	rr_1st = 0;
	for (i = 0; i<n1_1st; i++)
	{
		temp = I1_st[0].rhs[l1][1];
		l1++;
		int j;
		for (j = 0; j<rr_1st; j++)
			if (temp == read[j][0])
				break;
		if (j == rr_1st)
		{
			read[rr_1st][0] = temp;
			rr_1st++;
		}
		else
			continue;
		for (j = 0; j<n1_1st; j++)
		{
			if (grammar_l_1st[j] == temp)
			{
				I1_st[0].rhs[I1_st[0].n][0] = '\0';
				I1_st[0].rhs[I1_st[0].n][0] = '.';
				for (int k = 0; grammar_r_1st[j][k] != '\0'; k++)
				{
					I1_st[0].rhs[I1_st[0].n][k+1]=grammar_r_1st[j][k];
				}
				I1_st[0].lhs[I1_st[0].n] = grammar_l_1st[j];
				I1_st[0].n++;
			}
		}
	}
	ns_1st=1;
	//Printing I0
	for (l1 = 0; l1<ns_1st; l1++)
		Goto3(l1);

	//PRINTING ITEM SETS
	
	/*----------------------------------STEP IV: PARSING TABLE----------------------------------*/
	Mp_1st.clear(); Mpgoto_1st.clear(); Mplower_1st.clear(); Mpupper_1st.clear();
	cnt1_1st = 0; cnt_1st = 1;
	for (i = 0; i<n1_1st; i++)
	{
		Mp_1st[grammar_l_1st[i]] = 1; //non-terminal
		cnt1_1st++;
	}

	for (i = 0; i<n1_1st; i++)
	{
		for (int j = 0; grammar_r_1st[i][j] != '\0'; j++)
			if (Mp_1st.find(grammar_r_1st[i][j]) == Mp_1st.end())
			{
				Mp_1st[grammar_r_1st[i][j]] = 0;  //terminal
				cnt_1st++;
			}
	}
	Mp_1st['$'] = 0;
	cnt2_1st = 0; cnt3_1st = 0;
	for (iter_1st = Mp_1st.begin(); iter_1st != Mp_1st.end(); iter_1st++)
	{
		if (iter_1st->second == 1)
			Mpupper_1st[iter_1st->first] = ++cnt2_1st;
		else
			Mplower_1st[iter_1st->first] = ++cnt3_1st;
	}
	int mat1[100][100];
	for (i = 0; i<ns_1st; i++)
		for (int j = 0; j<cnt2_1st; j++)
			mat1[i][j] = -1;
	pair<char, int> action[100][100];
	for (i = 0; i<ns_1st; i++)
		for (int j = 0; j<cnt_1st; j++)
			action[i][j] = make_pair('e', 0);
	for (i = 0; i<ns_1st; i++)
		for (int j = 0; j<ns_1st; j++)
			if (mat_1st[i][j] != '\0')
			{
				if (Mpupper_1st[mat_1st[i][j]] != 0)
					mat1[i][Mpupper_1st[mat_1st[i][j]] - 1] = j;
				else if (Mplower_1st[mat_1st[i][j]] != 0)
					action[i][Mplower_1st[mat_1st[i][j]] - 1] = make_pair('s', j);
			}
	char str[30];
	str[0] = ss_1st;
	str[1] = '.';
	str[2] = '\0';
	for (i = 0; i<ns_1st; i++)
	{
		for (int j = 0; j<I1_st[i].n; j++)
		{
			if (I1_st[i].lhs[j] == 'O' && strcmp(I1_st[i].rhs[j], str) == 0)
			{
				action[i][Mplower_1st['$'] - 1] = make_pair('a', 0);
				continue;
			}
			char *ptr1 = strchr(I1_st[i].rhs[j], '.');
			ptr1++;
			if (*ptr1 == '\0' || *ptr1 == '~')
			{
				for (int k = 0; k<n1_1st; k++)  //traversing all productions
				{
					if (*ptr1 == '\0')
					{
						int ch;
						for (ch = 0; grammar_r_1st[k][ch] != '\0'; ch++)
							st_1st[ch] = grammar_r_1st[k][ch];
						st_1st[ch] = '\0';
						strcat(st_1st, ".");
						if (grammar_l_1st[k] == I1_st[i].lhs[j] && strcmp(st_1st, I1_st[i].rhs[j]) == 0)
						{
							num = k + 1;
							break;
						}
					}
					else if (grammar_l_1st[k] == I1_st[i].lhs[j] && grammar_r_1st[k][0] == '~')
					{
						num = k + 1;
						break;
					}
				}
				mit = follows.find(I1_st[i].lhs[j]);
				for (lit = (*mit).second.begin(); lit != (*mit).second.end(); lit++)
					action[i][Mplower_1st[(*lit)] - 1] = make_pair('r', num);
			}
		}
	}

	for (int i = 0; i<ns_1st; i++)
	{
		for (int j = 0; j<cnt_1st; j++)
		{
			if (action[i][j].first == 'e'){}
			else if (action[i][j].first == 'a'){}
			else
			{
				str[0] = action[i][j].first;
				str[1] = '\0';
				strcat(str, itoa(action[i][j].second, buffer_1st, 10));
			}
		}
		for (int j = 0; j<cnt2_1st; j++)
			if (mat1[i][j] == -1) {}
			else
			{
				itoa(mat1[i][j], buffer_1st, 10);
			}
	}
	
	/*---------------------------------STEP V: LR PARSING ALGO---------------------------------*/

	s=details;
	input_1st = s;
	char a, b[10];
	int final_number = 0;
	stack<int> S, Stemp;
	S.push(0);
	int k = 0;
	while (1)
	{
		space_1st = 30;
		a = s[0];
		num = S.top();
		b[0] = action[num][Mplower_1st[a] - 1].first;
		b[1] = '\0';
		int j = action[num][Mplower_1st[a] - 1].second;

		while (!S.empty())
		{
			Stemp.push(S.top());
			S.pop();
		}
		while (!Stemp.empty())
		{
			itoa(Stemp.top(), buffer_1st, 10);
			space_1st -= (strlen(buffer_1st) + 1);
			S.push(Stemp.top());
			Stemp.pop();
		}
		while (space_1st>0)
		{
			space_1st--;
		}
		itoa(j, temp2_1st, 10);
		strcat(b, temp2_1st);
		store_1st[k++] = action[num][Mplower_1st[a] - 1].first;
		if (action[num][Mplower_1st[a] - 1].first == 's')
		{
			S.push(j);
			s.erase(s.begin());
		}
		else if (action[num][Mplower_1st[a] - 1].first == 'r')
		{
			for (i = 0; grammar_r_1st[j - 1][i] != '\0' && grammar_r_1st[j - 1][i] != '~'; i++)
				S.pop();
			S.push(mat1[S.top()][Mpupper_1st[grammar_l_1st[j - 1]] - 1]);
			productions_l_1st[final_number] = grammar_l_1st[j - 1];
			strcpy(productions_r_1st[final_number], grammar_r_1st[j - 1]);
			final_number++;
		}
		else
		{
			break;
		}
	}
	store_1st[k++] = '\0';
	
	//-------------------STEP VI RIGHTMOST DERIVATION IN REVERSE ORDER AND PARSE TREE---------------------------------------------------------------
	/*--------------------------------PARSE TREE-----------------------------------*/
			string y, z;
			for (i = final_number - 1; i >= 0; i--)
			{
				y = productions_l_1st[i];
				z = productions_r_1st[i];
				produc_1st.push_back(y + "->" + z);
			}
	for (i = 0; i<50; i++)
	{
		I1_st[i].n = 0;
		I1_st[i].lhs[0] = NULL;
		for (int j = 0; j<50; j++)
			I1_st[i].rhs[j][0] = NULL;
	}
	
	return produc_1st;
}
