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
#include<algorithm>

using namespace std;
map<char, int> Mp_2, Mpupper_2, Mplower_2;
map<char, int> ::iterator iter_2;
int f_2[100];
ofstream mout_2;
int ctr_2 ;
int m2, cnt_2, cnt1_2, cnt2_2, cnt3_2,c2;
int n2 = 0,ns_2, tn_2 , rr_2;
char grammar_l_2[50], grammar_r_2[50][30], temp_2, templ_2[50], tempr_2[50][30], *ptr_2, temp2_2[5], mat_2[50][50];
char productions_l_2[50], productions_r_2[50][30], ss_2, buffer_2[5], store_2[1000],a2,st_2[30];
int final_number_2, err_2, space_2;
string input_2;
int mo_2,var_2;

//item_sets are the states of the LR automation
list<string> produc_2	;
char *unique_look;
list<string> ::iterator it7_2;
static list<string> ::iterator it8_2;
map< char, list<char> > firsts_2;
map< char, list<char> > ::iterator ind1_2, ind2_2, ix_2;
char firsts_return_2[20];
char *help_array_2;
list<char>::iterator it2_2;
char *beta_2;
/*head->body*/
struct prod_2
{
	char head;
	string body;
};
char *removeDupsSorted(char *str)
{
	int res_ind = 1, ip_ind = 1;
	while (*(str + ip_ind))
	{
		if (*(str + ip_ind) != *(str + ip_ind - 1))
		{
			*(str + res_ind) = *(str + ip_ind);
			res_ind++;
		}
		ip_ind++;
	}
	*(str + res_ind) = '\0';

	return str;
}
char *removeDups(char *str)
{
	int n = strlen(str);
	sort(str, str + n);
	return removeDupsSorted(str);
}
struct item_sets_2
{   //LHS and RHS indicate left and right sides of the productions. Left side is a nonterminal(single character)
	char lhs[50], rhs[50][50];
	//Symbol on which the state has a transition
	char sym;
	//No. of productions in a given state
	int n;
	//List of terminals associated with each production
	char lookahead[50][50];
	//State number
	int state_no;
}I_2[100];
char *Firsts_2(string abeta, int k)
{
	int y = abeta.length();
	int flag = 0;
	c2 = 0;
	for (ix_2 = firsts_2.begin(); ix_2 != firsts_2.end(); ix_2++)
	{
		flag = 0;
		list<char> ::iterator iy;
		if (abeta[c2] == '~')
		{
			c2++;
		}
		if (c2 >= y)
			break;
		if (abeta[c2] == '$')
		{
			c2++;
			for (var_2 = 0; var_2<k; var_2++)
				if (firsts_return_2[var_2] != '$')
					continue;
				else break;
				if (var_2 == k)
					firsts_return_2[k++] = '$';
				break;
		}
		if (!isupper(abeta[c2]))
		{
			for (var_2 = 0; var_2<k; var_2++)
				if (firsts_return_2[var_2] != abeta[c2])
					continue;
				else break;
				if (var_2 == k)
					firsts_return_2[k++] = abeta[c2];
				break;
		}
		if (((*ix_2).first) == abeta[c2]) {
			for (iy = ((*ix_2).second).begin(); iy != ((*ix_2).second).end(); ++iy)
			{
				if ((*iy) == '~')
				{
					flag = 1;
					continue;
				}
				for (var_2 = 0; var_2<k; var_2++)
					if (firsts_return_2[var_2] != *(iy))
						continue;
					else break;
					if (var_2 == k)
						firsts_return_2[k++] = *(iy);

			}
			if (flag)
			{
				c2++;
				ix_2 = firsts_2.begin()--;
				if (c2 >= y)
					break;
			}
			else
			{
				break;
			}
		}
		else continue;
	}
	firsts_return_2[k] = NULL;
	return firsts_return_2;
}
int compare_struct_2(item_sets_2 s1, item_sets_2 s2)
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
int compare_look(item_sets_2 s1, item_sets_2 s2)
{
	int t;
	for (t = 0; t<s1.n; t++)
		if (strcmp(s1.lookahead[t], s2.lookahead[t]) != 0)
			return 0;
	return 1;
}
//This finds the closure of the item sets in a given state after the GOTO function
//To add more productions
void Closure_2()
{
	int r, s, t, l1 = 0, rr1 = 0;
	char *ptr1, read1[50][30];
	for (int x = 0; x<20; x++)
		firsts_return_2[x] = NULL;
	for (r = 0; r<I_2[ns_2].n; r++)
	{
		ptr1 = strchr(I_2[ns_2].rhs[l1], '.');
		t = ptr1 - I_2[ns_2].rhs[l1];
		if (t + 1 == strlen(I_2[ns_2].rhs[l1]))
		{
			l1++;
			continue;
		}
		temp_2 = I_2[ns_2].rhs[l1][t + 1];
		l1++;
		if (!isupper(temp_2))
			continue;
		if (strlen(strchr(I_2[ns_2].rhs[l1 - 1], '.'))<3)
			beta_2 = "~";
		else beta_2 = strchr(I_2[ns_2].rhs[l1 - 1], '.') + 2;
		a2 = I_2[ns_2].lookahead[l1 - 1][0];
		string betaa;
		betaa.resize(strlen(beta_2) + 1);
		for (int i = 0; beta_2[i] != '\0'; i++)
			betaa[i] = beta_2[i];
		betaa[strlen(beta_2)] = a2;
		help_array_2 = Firsts_2(betaa, 0);
		for (mo_2 = 1; mo_2<strlen(I_2[ns_2].lookahead[l1 - 1]); mo_2++)
		{
			a2 = I_2[ns_2].lookahead[l1 - 1][mo_2];
			betaa.resize(strlen(beta_2) + 1);
			for (int i = 0; beta_2[i] != '\0'; i++)
				betaa[i] = beta_2[i];
			betaa[strlen(beta_2)] = a2;
			int y = strlen(help_array_2);
			help_array_2 = Firsts_2(betaa, y);
		}
		for (s = 0; s<rr1; s++)
			if (temp_2 == read1[s][0])
				break;
		if (s == rr1)
		{
			read1[rr1][0] = temp_2;
			rr1++;
		}
		else
		{
			for (int j = 0; j<I_2[ns_2].n; j++)
			{
				if (temp_2 == I_2[ns_2].lhs[j])
				{
					strcat(I_2[ns_2].lookahead[j], help_array_2);
				}
			}
			continue;
		}
		for (s = 0; s<n2; s++)
		{
			if (grammar_l_2[s] == temp_2)
			{
				I_2[ns_2].rhs[I_2[ns_2].n][0] = '.';
				I_2[ns_2].rhs[I_2[ns_2].n][1] = NULL;
				strcat(I_2[ns_2].rhs[I_2[ns_2].n], grammar_r_2[s]);
				I_2[ns_2].lhs[I_2[ns_2].n] = grammar_l_2[s];
				I_2[ns_2].lhs[I_2[ns_2].n + 1] = NULL;
				strcpy(I_2[ns_2].lookahead[I_2[ns_2].n], help_array_2);
				I_2[ns_2].n++;
			}
		}
	}
}

void Goto_2(int l)
{
	int t1,j;
	char read1[50][30], rr1 = 0, *ptr1;
	m2 = 0;
	for (int i = 0; i<I_2[l].n; i++)
	{
		temp2_2[0] = '.';
		ptr1 = strchr(I_2[l].rhs[i], '.');
		if (ptr1[1] == '~')
			continue;
		t1 = ptr1 - I_2[l].rhs[i];
		if (t1 + 1 == strlen(I_2[l].rhs[i]))
			continue;
		temp2_2[1] = I_2[l].rhs[i][t1 + 1];
		temp2_2[2] = NULL;
		for (j = 0; j<rr1; j++)
			if (strcmp(temp2_2, read1[j]) == 0)
				break;
		if (j == rr1)
		{
			strcpy(read1[rr1], temp2_2);
			read1[rr1][2] = NULL;
			rr1++;
		}
		else
			continue;
		tn_2 = 0;
		for (j = 0; j<I_2[l].n; j++)
		{
			ptr_2 = strstr(I_2[l].rhs[j], temp2_2);
			if (ptr_2)
			{
				templ_2[tn_2] = I_2[l].lhs[j];
				templ_2[tn_2 + 1] = NULL;
				strcpy(tempr_2[tn_2], I_2[l].rhs[j]);
				strcpy(I_2[ns_2].lookahead[tn_2], I_2[l].lookahead[j]);
				tn_2++;
			}
		}
		for (j = 0; j<tn_2; j++)
		{
			ptr_2 = strchr(tempr_2[j], '.');
			int p = ptr_2 - tempr_2[j];
			tempr_2[j][p] = tempr_2[j][p + 1];
			tempr_2[j][p + 1] = '.';
			I_2[ns_2].lhs[I_2[ns_2].n] = templ_2[j];
			I_2[ns_2].lhs[I_2[ns_2].n + 1] = NULL;
			strcpy(I_2[ns_2].rhs[I_2[ns_2].n], tempr_2[j]);
			I_2[ns_2].n++;
		}
		Closure_2();
		for (j = 0; j<ns_2; j++)
		{
			if (compare_struct_2(I_2[ns_2], I_2[j]) == 1)
			{
				for (int k = 0; k<I_2[ns_2].n; k++)
				{
					I_2[ns_2].rhs[k][0] = NULL;
					if (compare_look(I_2[j], I_2[ns_2]) == 0)
						strcat(I_2[j].lookahead[k], I_2[ns_2].lookahead[k]);
				}
				I_2[ns_2].lhs[0] = NULL;
				I_2[ns_2].n = 0;
				for (int k = 0; k<I_2[ns_2].n; k++)
					I_2[ns_2].lookahead[k][0] = NULL;
				mat_2[l][j] = temp2_2[1];
				break;
			}
		}
		if (j<ns_2)
		{
			tn_2 = 0;
			for (j = 0; j<50; j++)
			{
				templ_2[j] = NULL;
				tempr_2[j][0] = NULL;
				firsts_return_2[j] = NULL;
			}
			continue;
		}
		if (ptr1[1])
			mat_2[l][j] = ptr1[1];
		I_2[ns_2].sym = ptr1[1];
		//Printing
		//This is the symbol on which the state has a transition(LR automation
		ns_2++;
		tn_2 = 0;
		for (j = 0; j<50; j++)
		{
			templ_2[j] = NULL;
			tempr_2[j][0] = NULL;
			firsts_return_2[j] = NULL;
		}
	}
}

int ar_2[10] = { 1,1,1,1,1,1,1,1,1,1 };
void parseTree_2(char X, int l) {
	int lev = l;
	for (int i = 0; i<10; i++) {
		if (lev - 1 >0) {}
		else break;
		if (ar_2[i] == 1) mout_2 << "| ";
		else mout_2 << "  ";
		lev--;
	}
	if (lev == 1)
		mout_2 << "|_";
	else if (lev>0)
	{
		for (int z = 0; z<lev - 1; z++)
			mout_2 << "  ";
		mout_2 << "|_";
	}
	mout_2 << X << endl;
	if (X<'A' || X>'Z')
		return;
	for (it7_2 = it8_2; it7_2 != produc_2.end(); it7_2++) {
		string p = (*it7_2);
		if (p[0] == X) {
			it8_2 = ++it7_2;
			string s = p.substr(3);
			int len = s.length();
			for (int j = 0; j<len; j++) {
				if (len - 1 == j)
					ar_2[l] = 0;
				parseTree_2(s[len - 1 - j], l + 1);
				ar_2[l] = 1;
				if (len - 1 != j) {
					int lev = l + 1;
					for (int i = 0; i<10; i++) {
						if (lev >0) {}
						else break;
						if (ar_2[i] == 1) mout_2 << "| ";
						else mout_2 << "  ";
						lev--;
					}
					mout_2 << endl;
				}
			}
			break;
		}
	}
	return;
}

int maxLenP_2 = 0;
int siz_2;
prod_2 *arr_2 = new prod_2[100];
void lalr()
{
	string s, inpFile;
	ifstream myfile("grammar.txt");
	int i = 0;
	arr_2[i].head = 'Z';
	i++;
	n2 = 0;
	while (!myfile.eof())
	{
		getline(myfile, s);
		arr_2[i].head = s[0];
		arr_2[0].body = arr_2[1].head;
		int len = s.length();
		/*Allows extra line at the end*/
		if (len>maxLenP_2) maxLenP_2 = len;
		if (len == 0)
			break;
		arr_2[i].body = s.substr(3);
		//body starts from position 3
		i++;
		grammar_l_2[n2] = s[0];
		int j = 3;
		while (s[j] != '\0')
			grammar_r_2[n2][j - 3] = s[j++];
		grammar_r_2[n2][j - 3] = '\0';
		n2++;
	}
	myfile.close();
	/* # Productions*/
	siz_2 = i;

	mout_2.open("output.txt", ios_base::out);
	mout_2 << "-----------------------------AUGMENTED GRAMMAR-----------------------------\n\n";
	for (int j = 0; j<siz_2; j++)
		mout_2 << j + 1 << ". " << arr_2[j].head << "->" << arr_2[j].body << endl;

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
	for (int i = 0; i<siz_2; i++)
	{
		string s = arr_2[i].body;
		if (s[0] == '~')
		{
			epsilon[arr_2[i].head - 'A'] = 1;
			ldash.push_back(make_pair(arr_2[i].head, s));
		}
		else if (s[0]<'A' || s[0]>'Z') {
			ldash.push_back(make_pair(arr_2[i].head, s));
		}
		else {
			l.push_back(make_pair(arr_2[i].head, s));
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
	firsts_2.clear();

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
				ind1_2 = firsts_2.find((*it).first);
				if (ind1_2 != firsts_2.end())
				{
					((*ind1_2).second).push_back(s[i]);
					break;
				}
				else
				{
					list<char> temp;
					temp.push_back(s[i]);
					firsts_2.insert(make_pair((*it).first, temp));
					break;
				}
			}
			/* non-terminal */
			else
			{
				ind1_2 = firsts_2.find((*it).first);
				if (ind1_2 != firsts_2.end())
				{
					ind2_2 = firsts_2.find(s[i]);
					list<char>::iterator lit;
					cnt_2 = 0;
					for (lit = ((*ind2_2).second).begin(); lit != ((*ind2_2).second).end(); lit++)
					{
						cnt_2++;
					}

					for (lit = ((*ind2_2).second).begin(); cnt_2>0; lit++, cnt_2--)
					{
						((*ind1_2).second).push_back(*lit);
					}
				}
				else
				{
					list<char> temp;
					ind2_2 = firsts_2.find(s[i]);
					list<char>::iterator lit;
					for (lit = ((*ind2_2).second).begin(); lit != ((*ind2_2).second).end(); lit++)
					{
						temp.push_back(*lit);
					}
					firsts_2.insert(make_pair((*it).first, temp));
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
	for (int i = 0; i<siz_2; i++)
	{
		string s = arr_2[i].body;
		for (int j = 0; j<s.length(); j++)
			if (s[j]<'A' || s[j]>'Z')
				term.push_back(s[j]);
	}
	term.sort();
	term.unique();
	term.remove('~');

	/* printing firsts */
	map< char, list<char> > ::iterator mit;
	mout_2 << "\n--------------------------------FIRST SETS---------------------------------\n\n";
	for (mit = firsts_2.begin(); mit != firsts_2.end(); mit++)
	{
		((*mit).second).sort();
		((*mit).second).unique();
		mout_2 << "FIRST(" << (*mit).first << ") = { ";
		list<char> ::iterator lit;
		for (lit = ((*mit).second).begin(); lit != ((*mit).second).end(); lit++)
		{
			if (lit == ((*mit).second).begin()) mout_2 << *lit;
			else mout_2 << ", " << *lit;
		}
		mout_2 << " }" << endl;
	}

	for (ti = term.begin(); ti != term.end(); ti++)
	{
		mout_2 << "FIRST(" << (*ti) << ") = { " << (*ti) << " }" << endl;
	}
	mout_2.close();
/*----------------------------------STEP III: ITEM SETS----------------------------------*/

	int l1;
	for (i = 0; i<50; i++)
	{
		I_2[i].n = 0;
		I_2[i].lhs[0] = NULL;
		I_2[i].rhs[0][0] = NULL;
		I_2[i].lookahead[0][0] = NULL;
	}

	mout_2.open("output.txt", ios_base::app);
	ss_2 = grammar_l_2[0];
	//Original starting symbol is S and the new starting symbol is Q.
	I_2[0].lhs[0] = 'Z';
	char as[2];
	as[0] = '.', as[1] = ss_2, as[2] = '\0';
	strcpy(I_2[0].rhs[0], as);
	I_2[0].n++;
	l1 = 0;
	strcpy(I_2[0].lookahead[0], "$");
	char read[50][30];
	for (int x = 0; x<20; x++)
		firsts_return_2[x] = NULL;
	int j, k,rr_2=0;
	for (i = 0; i<n2; i++)
	{
		temp_2 = I_2[0].rhs[l1][1];
		l1++;
		if (!isupper(temp_2))
			continue;
		if (strlen(strchr(I_2[0].rhs[l1 - 1], '.'))<3)
			beta_2 = "~";
		else beta_2 = strchr(I_2[0].rhs[l1 - 1], '.') + 2;
		a2 = I_2[0].lookahead[l1 - 1][0];
		string betaa;
		betaa.resize(strlen(beta_2) + 1);
		for (int i = 0; beta_2[i] != '\0'; i++)
			betaa[i] = beta_2[i];
		betaa[strlen(beta_2)] = a2;
		help_array_2 = Firsts_2(betaa, 0);
		for (mo_2 = 1; mo_2<strlen(I_2[0].lookahead[l1 - 1]); mo_2++)
		{

			a2 = I_2[0].lookahead[l1 - 1][mo_2];
			string betaa;
			betaa.resize(strlen(beta_2) + 1);
			for (int i = 0; beta_2[i] != '\0'; i++)
				betaa[i] = beta_2[i];
			betaa[strlen(beta_2)] = a2;
			int y = strlen(help_array_2);
			help_array_2 = Firsts_2(betaa, y);

		}
		for (j = 0; j<rr_2; j++)
			if (temp_2 == read[j][0])
				break;
		if (j == rr_2)
		{
			read[rr_2][0] = temp_2;
			rr_2++;
		}
		else
		{
			for (j = 0; j<I_2[0].n; j++)
			{
				if (temp_2 == I_2[0].lhs[j])
				{
					strcat(I_2[0].lookahead[j], help_array_2);
				}
			}
			continue;
		}
		for (j = 0; j<n2; j++)
		{
			if (grammar_l_2[j] == temp_2)
			{
				strcpy(I_2[0].lookahead[I_2[0].n], help_array_2);
				I_2[0].rhs[I_2[0].n][0] = '.';
				for (int k = 0; grammar_r_2[j][k] != '\0'; k++)
				{
					I_2[0].rhs[I_2[0].n][k + 1] = grammar_r_2[j][k];
				}
				I_2[0].lhs[I_2[0].n] = grammar_l_2[j];
				I_2[0].n++;
			}
		}
	}
	ns_2=1;
	for (l1 = 0; l1<ns_2; l1++)
		Goto_2(l1);
	for (l1 = 0; l1<ns_2; l1++)
		Goto_2(l1);
	for (i = 0; i<ns_2; i++)
	{
		for (j = 0; j<I_2[i].n; j++)
		{
			unique_look = removeDups(I_2[i].lookahead[j]);
			strcpy(I_2[i].lookahead[j], unique_look);
		}
	}
	mout_2 << "\n---------------------------------ITEM SETS---------------------------------\n\n";
	//Printing Item Sets
	mout_2 << "CLOSURE({[" << I_2[0].lhs[0] << "->" << I_2[0].rhs[0] << ",$]})={";
	for (i = 0; i<I_2[0].n - 1; i++)
	{
		mout_2 << "[" << I_2[0].lhs[i] << "->" << I_2[0].rhs[i] << ",";
		for (mo_2 = 0; mo_2<strlen(I_2[0].lookahead[i]); mo_2++)
		{
			mout_2 << I_2[0].lookahead[i][mo_2];
			if (mo_2 != strlen(I_2[0].lookahead[i]) - 1)
				mout_2 << "/";
		}
		mout_2 << "],";
	}
	mout_2 << "[" << I_2[0].lhs[i] << "->" << I_2[0].rhs[i] << ",";
	for (mo_2 = 0; mo_2<strlen(I_2[0].lookahead[i]); mo_2++)
	{
		mout_2 << I_2[0].lookahead[i][mo_2];
		if (mo_2 != strlen(I_2[0].lookahead[i]) - 1)
			mout_2 << "/";
	}
	mout_2 << "]}=";
	mout_2 << "I0" << endl << endl;
	for (i = 0; i<ns_2; i++)
	{
		ctr_2 = 0;
		for (j = 0; j<ns_2; j++)
		{
			if (mat_2[i][j] != NULL)
				ctr_2++;
		}
		if (ctr_2)
		{
			mout_2 << "I" << i << "={";
			for (k = 0; k<I_2[i].n - 1; k++)
			{
				mout_2 << "[" << I_2[i].lhs[k] << "->" << I_2[i].rhs[k] << ",";
				for (mo_2 = 0; mo_2<strlen(I_2[i].lookahead[k]); mo_2++)
				{
					mout_2 << I_2[i].lookahead[k][mo_2];
					if (mo_2 != strlen(I_2[i].lookahead[k]) - 1)
						mout_2 << "/";
				}
				mout_2 << "],";
			}
			mout_2 << "[" << I_2[i].lhs[k] << "->" << I_2[i].rhs[k] << ",";
			for (mo_2 = 0; mo_2<strlen(I_2[i].lookahead[k]); mo_2++)
			{
				mout_2 << I_2[i].lookahead[k][mo_2];
				if (mo_2 != strlen(I_2[i].lookahead[k]) - 1)
					mout_2 << "/";
			}
			mout_2 << "]}" << endl;
		}
		else continue;
		for (j = 0; j<ns_2; j++)
		{
			if (mat_2[i][j])
			{
				mout_2 << "GOTO(I" << i << "," << mat_2[i][j] << ")";
				mout_2 << "={";
				for (k = 0; k<I_2[j].n - 1; k++)
				{
					mout_2 << "[" << I_2[j].lhs[k] << "->" << I_2[j].rhs[k] << ",";
					for (mo_2 = 0; mo_2<strlen(I_2[j].lookahead[k]); mo_2++)
					{
						mout_2 << I_2[j].lookahead[k][mo_2];
						if (mo_2 != strlen(I_2[j].lookahead[k]) - 1)
							mout_2 << "/";
					}
					mout_2 << "],";
				}
				mout_2 << "[" << I_2[j].lhs[k] << "->" << I_2[j].rhs[k] << ",";
				for (mo_2 = 0; mo_2<strlen(I_2[j].lookahead[k]); mo_2++)
				{
					mout_2 << I_2[j].lookahead[k][mo_2];
					if (mo_2 != strlen(I_2[j].lookahead[k]) - 1)
						mout_2 << "/";
				}
				mout_2 << "]}=I" << j << endl;
			}
		}
		mout_2 << endl;
	}

	/*----------------------------------STEP IV: PARSING TABLE----------------------------------*/
	Mp_2.clear();
	Mplower_2.clear();
	Mpupper_2.clear();
	mout_2 << "-----------------------------PARSING TABLE---------------------------------\n\n";
	cnt1_2 = 0; cnt_2 = 1;
	for (i = 0; i<n2; i++)
	{
		Mp_2[grammar_l_2[i]] = 1; //non-terminal
		cnt1_2++;
	}

	for (i = 0; i<n2; i++)
	{
		for (j = 0; grammar_r_2[i][j] != '\0'; j++)
			if (Mp_2.find(grammar_r_2[i][j]) == Mp_2.end())
			{
				Mp_2[grammar_r_2[i][j]] = 0;  //terminal
				cnt_2++;
			}
	}
	Mp_2['$'] = 0;
	cnt2_2 = 0; cnt3_2 = 0;
	for (iter_2 = Mp_2.begin(); iter_2 != Mp_2.end(); iter_2++)
	{
		if (iter_2->second == 1)
			Mpupper_2[iter_2->first] = ++cnt2_2;
		else
			Mplower_2[iter_2->first] = ++cnt3_2;
	}
	mout_2 << "_______";
	for (i = 0; i<6 * (cnt2_2 + cnt3_2) + 4; i++)
		mout_2 << "_";
	mout_2 << endl;
	mout_2 << "STATE";
	mout_2 << setw(4 * cnt_2) << "ACTION";
	mout_2 << setw(4 * cnt1_2) << "GOTO" << endl;
	mout_2 << "_______";
	for (i = 0; i<6 * (cnt2_2 + cnt3_2) + 4; i++)
		mout_2 << "_";
	mout_2 << "\n      |";
	for (iter_2 = Mp_2.begin(); iter_2 != Mp_2.end(); iter_2++)
		if (iter_2->second == 0)
			mout_2 << setw(6) << iter_2->first;
	mout_2 << " |";
	for (iter_2 = Mp_2.begin(); iter_2 != Mp_2.end(); iter_2++)
		if (iter_2->second == 1)
			mout_2 << setw(6) << iter_2->first;
	mout_2 << endl;
	mout_2 << "______|";
	for (i = 0; i<6 * (cnt3_2); i++)
		mout_2 << "_";
	mout_2 << "_|";
	for (i = 0; i<6 * (cnt2_2)+2; i++)
		mout_2 << "_";
	mout_2 << endl;

	int mat1[100][100];
	for (i = 0; i<ns_2; i++)
		for (j = 0; j<cnt2_2; j++)
			mat1[i][j] = -1;
	pair<char, int> action[100][100];
	for (i = 0; i<ns_2; i++)
		for (j = 0; j<cnt_2; j++)
			action[i][j] = make_pair('e', 0);

	for (i = 0; i<ns_2; i++)
		for (j = 0; j<ns_2; j++)
			if (mat_2[i][j] != '\0')
			{
				if (Mpupper_2[mat_2[i][j]] != 0)
					mat1[i][Mpupper_2[mat_2[i][j]] - 1] = j;
				else if (Mplower_2[mat_2[i][j]] != 0)
					action[i][Mplower_2[mat_2[i][j]] - 1] = make_pair('s', j);
			}

	char str[30];
	str[0] = ss_2;
	str[1] = '.';
	str[2] = '\0';
	int num = 1;
	for (i = 0; i<ns_2; i++)
	{
		for (j = 0; j<I_2[i].n; j++)
		{
			if (I_2[i].lhs[j] == 'Z' && I_2[i].rhs[j][0]==ss_2 && I_2[i].rhs[j][1]=='.' && I_2[i].rhs[j][2] == '\0')
			{
				action[i][Mplower_2['$'] - 1] = make_pair('a', 0);
				continue;
			}
			char *ptr1 = strchr(I_2[i].rhs[j], '.');
			ptr1++;
			if (*ptr1 == '\0' || *ptr1 == '~')   //reduction
			{
				for (k = 0; k<n2; k++)  //traversing all productions
				{
					
					if (*ptr1 == '\0')
					{
						int ch;
						for (ch = 0; grammar_r_2[k][ch] != '\0'; ch++)
							st_2[ch] = grammar_r_2[k][ch];
						st_2[ch] = '\0';
						//strcpy(st, grammar_r_2[k]);
						strcat(st_2, ".");
						if (grammar_l_2[k] == I_2[i].lhs[j] && strcmp(st_2, I_2[i].rhs[j]) == 0)
						{
							num = k + 1;
							break;
						}
					}
					else if (grammar_l_2[k] == I_2[i].lhs[j] && grammar_r_2[k][0] == '~')
					{
						num = k + 1;
						break;
					}
				}
				for (k = 0; k<strlen(I_2[i].lookahead[j]); k++)
					action[i][Mplower_2[I_2[i].lookahead[j][k]] - 1] = make_pair('r', num);
			}
		}
	}

	for (int i = 0; i<ns_2; i++)
	{
		mout_2 << setw(6) << i << "|";
		for (int j = 0; j<cnt_2; j++)
		{
			if (action[i][j].first == 'e')
				mout_2 << "      ";
			else if (action[i][j].first == 'a')
				mout_2 << "   acc";
			else
			{
				str[0] = action[i][j].first;
				str[1] = '\0';
				strcat(str, itoa(action[i][j].second, buffer_2, 10));
				mout_2 << setw(6) << str;
			}
		}
		mout_2 << setw(2) << '|';
		for (int j = 0; j<cnt2_2; j++)
			if (mat1[i][j] == -1)
				mout_2 << "      ";
			else
			{
				itoa(mat1[i][j], buffer_2, 10);
				mout_2 << setw(6) << buffer_2;
			}
		mout_2 << endl;
	}
	mout_2 << "_______";
	for (i = 0; i<6 * (cnt2_2 + cnt3_2) + 4; i++)
		mout_2 << "_";
	mout_2 << endl;
	mout_2.close();

	/*---------------------------------STEP V: LR PARSING ALGO---------------------------------*/

	myfile.open("details.txt");
	getline(myfile, s);
	myfile.close();
	input_2 = s;
	char a2, b[10];
	s += "$";
	final_number_2 = 0;
	stack<int> S, Stemp;
	S.push(0);
	mout_2.open("output.txt", ios_base::app);
	mout_2 << "\n--------------------------TABLE DRIVEN PARSING---------------------------\n\n";
	mout_2 << "__________________________________________________________________________\n";
	mout_2 << std::left << setw(30) << "STACK";
	mout_2 << std::left << setw(22) << "INPUT";
	mout_2 << " ACTION     PRODUCTION" << endl;
	mout_2 << "__________________________________________________________________________\n";
	k = 0;

	while (1)
	{
		space_2 = 30;
		a2 = s[0];
		num = S.top();
		b[0] = action[num][Mplower_2[a2] - 1].first;
		b[1] = '\0';
		j = action[num][Mplower_2[a2] - 1].second;

		while (!S.empty())
		{
			Stemp.push(S.top());
			S.pop();
		}
		while (!Stemp.empty())
		{
			mout_2 << Stemp.top() << ' ';
			itoa(Stemp.top(), buffer_2, 10);
			space_2 -= (strlen(buffer_2) + 1);
			S.push(Stemp.top());
			Stemp.pop();
		}
		while (space_2>0)
		{
			mout_2 << " ";
			space_2--;
		}
		mout_2 << std::left << setw(25) << s;
		itoa(j, temp2_2, 10);
		strcat(b, temp2_2);
		if (action[num][Mplower_2[a2] - 1].first == 'a')
			mout_2 << std::right << setw(4) << "acc";
		else
			mout_2 << std::right << setw(4) << b;
		store_2[k++] = action[num][Mplower_2[a2] - 1].first;
		mout_2 << "     ";
		err_2 = 0;
		if (action[num][Mplower_2[a2] - 1].first == 's')
		{
			S.push(j);
			s.erase(s.begin());
		}
		else if (action[num][Mplower_2[a2] - 1].first == 'r')
		{
			for (i = 0; grammar_r_2[j - 1][i] != '\0' && grammar_r_2[j - 1][i] != '~'; i++)
				S.pop();
			S.push(mat1[S.top()][Mpupper_2[grammar_l_2[j - 1]] - 1]);
			mout_2 << grammar_l_2[j - 1] << "->" << grammar_r_2[j - 1];
			productions_l_2[final_number_2] = grammar_l_2[j - 1];
			strcpy(productions_r_2[final_number_2], grammar_r_2[j - 1]);
			final_number_2++;
		}
		else if (action[num][Mplower_2[a2] - 1].first == 'e')
		{
			mout_2 << "Error" << endl;
			err_2++;
			break;
		}
		else
		{
			mout_2 << "Accept" << endl;
			break;
		}
		mout_2 << endl;
	}
	store_2[k++] = '\0';
	mout_2 << "__________________________________________________________________________\n";
	mout_2 << endl;


	//-------------------STEP VI RIGHTMOST DERIVATION IN REVERSE ORDER AND PARSE TREE---------------------------------------------------------------
	if (!err_2)
	{
		int len, q;
		len = input_2.length();
		stack<string>temp_stack;
		string x = productions_r_2[final_number_2 - 1];
		temp_stack.push(x);
		string y, z, u;
		for (i = final_number_2 - 2; i >= 0; i--)
		{
			size_t found = x.find_last_of(productions_l_2[i]);
			f_2[final_number_2 - 2 - i + 1] = found;
			y = x.substr(0, found);
			z = x.substr(found + 1);
			u = productions_r_2[i];
			x = y + u + z;
			temp_stack.push(x);
		}
		/*--------------------------------PARSE TREE-----------------------------------*/
		if (err_2 == 0)
		{
			for (int i = 0; i < 10; i++)
				ar_2[i] = 1;
			string y, z;
			for (i = final_number_2 - 1; i >= 0; i--)
			{
				y = productions_l_2[i];
				z = productions_r_2[i];
				produc_2.push_back(y + "->" + z);
			}
			it8_2 = produc_2.begin();
			mout_2 << "-------------------------------PARSE TREE---------------------------------\n\n";
			parseTree_2(ss_2, 0);
		}
		mout_2 << "\n--------------------RIGHTMOST DERIVATION IN REVERSE ORDER-----------------\n\n";
		for (i = final_number_2 - 1; i >= 0; i--)
		{
			y = temp_stack.top();
			temp_stack.pop();
			mout_2 << y << "<=";
		}
		mout_2 << ss_2 << "<=Z\n";
	}
	mout_2.close();
}

