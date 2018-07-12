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
#define N 100
#define mp make_pair

/* Formatting output: #include<iomanip> */
ofstream mout_3;
const int width = 13;
const char sep = ' ';
int maxLenP_3;

template<typename T> void format(T t) {
	mout_3 << std::left << setw(width) << setfill(sep) << t;
}
template<typename T> void format_r(T t) {
	mout_3 << std::right << setw(width) << setfill(sep) << t;
}
template<typename T> void format_VAR(const int& wi, T t) {
	mout_3 << std::left << setw(wi) << setfill(sep) << t;
}

template<typename T> void format_VAR_r(const int& wi, T t) {
	mout_3 << std::right << setw(wi) << setfill(sep) << t;
}

/*head->body*/
struct prod_3 {
	char head;
	string body;
};
//state set item
struct item
{
	int rule;
	int origin;
	int next;
};
/*Array to store grammar*/
prod_3 *arr_3 = new prod_3[N], *prodn_new = new prod_3[N];
vector<item> S[100001];
int siz_3;
bool operator==(const struct item & p, const struct item & aux)
{
	if (aux.rule != p.rule)     return false;
	if (aux.origin != p.origin)     return false;
	if (aux.next != p.next)     return false;
	return true;
}
bool check(struct item aux, int i)
{
	int rule = aux.rule;
	int origin = aux.origin;
	int next = aux.next;
	int j;
	for (j = 0; j<S[i].size(); j++)
		if (aux == S[i][j])  return false;
	return true;
}
bool null[1001] = { false };
void predictor(char symbol, int i,
	int rule, int origin, int next)
{
	int j;
	for (j = 0; j<siz_3; j++)
	{
		if (arr_3[j].head == symbol)
		{
			struct item aux = { j,i,0 };
			if (check(aux, i))  S[i].push_back(aux);
		}
		if (null[j])
		{
			struct item aux = { rule,
				origin,next + 1 };
			if (check(aux, i)) S[i].push_back(aux);
		}
	}
}
int scan(int rule, int origin, int next, int i, int cnt)
{
	struct item aux = { rule,origin,next + 1 };
	if (check(aux, i + 1))
	{
		S[i + 1].push_back(aux);
		return i + 1;
	}
	return cnt;
}
void complete(int origin, int i, char sym)
{
	int j;
	for (j = 0; j<S[origin].size(); j++)
	{
		int x = S[origin][j].rule;
		char symbol = arr_3[x].body[S[origin][j].next];
		if (symbol == sym)
		{
			struct item aux = { S[origin][j].rule,S[origin][j].origin,S[origin][j].next + 1 };
			if (check(aux, i))  S[i].push_back(aux);
		}
	}
}

bool helper(int i, bool nss[])
{
	int j;
	for (j = 0; j<arr_3[i].body.size(); j++)
	{
		if (!nss[arr_3[i].body[j] - 'A'])  return false;
	}
	return true;
}
void nullable(int siz_3, bool nss[])
{
	int i = 0;
	for (i = 0; i<siz_3; i++)
	{
		if (arr_3[i].body == "~")
			nss[arr_3[i].head - 'A'] = true;
	}
	for (i = 0; i<siz_3; i++)
	{
		if (arr_3[i].body == "~" || helper(i, nss))
			null[i] = true;
	}
}

void earley()
{
	///---------STEP I: INPUT GRAMMAR-----------

	string s, inpFile;
	//A->~ == A->epsilon;
	ifstream myfile("grammar.txt");
	int i = 1;
	maxLenP_3 = 0;
	while (!myfile.eof())
	{
		getline(myfile, s);
		arr_3[i].head = s[0];
		int len = s.length();
		/*Allows extra line at the end*/
		if (len>maxLenP_3) maxLenP_3 = len;
		if (len == 0)
			break;
		arr_3[i].body = s.substr(3);
		int leng = arr_3[i].body.size();
		arr_3[i].body[leng] = '\0';
		i++;
	}
	myfile.close();
	/* # Productions*/
	siz_3 = i;
	string extra;
	char blah = arr_3[1].head;
	arr_3[0].head = 'Z';
	string v;
	v.insert(0, 1, blah);
	arr_3[0].body = v;
	///determining null-able rules...
	bool nss[30] = { false };
	nullable(siz_3, nss);

	string inp;
	myfile.open("details.txt");
	getline(myfile, inp);
	myfile.close();
	blah = 'Z';
	for (i = 0; i<siz_3; i++)
	{
		if (arr_3[i].head == blah)
		{
			struct item aux = { i,0,0 };
			S[0].push_back(aux);
		}
	}
	int cnt = 0, j;
	int len = inp.size();
	for (i = 0; i <= cnt; i++)
	{
		for (j = 0; j<S[i].size(); j++)
		{
			int rule = S[i][j].rule;
			int origin = S[i][j].origin;
			int next = S[i][j].next;
			char symbol = arr_3[rule].body[next];
			if (symbol >= 'A'&&symbol <= 'Z')
			{
				predictor(symbol, i, rule, origin, next);
			}
			else if (symbol == '\0')
			{
				complete(origin, i, arr_3[rule].head);
			}
			else
			{
				if (inp[i] == symbol)
				{
					cnt = scan(rule, origin, next, i, cnt);
				}
			}
		}
	}
	int ans[100001];
	int k = 0;
	for (i = 0; i<S[len].size(); i++)
	{
		int next = S[len][i].next;
		int origin = S[len][i].origin;
		int rule = S[len][i].rule;
		char symbol = arr_3[rule].body[next];
		char head = arr_3[rule].head;
		if (origin == 0 && head == blah&&symbol == '\0')
			ans[k++] = rule;
	}
	
	mout_3.open("output.txt");
	mout_3 << "-----------------------------AUGMENTED GRAMMAR-----------------------------\n\n";
	for (i = 0; i<siz_3; i++)
	{
		mout_3 << i + 1 << ". " << arr_3[i].head << "->" << arr_3[i].body << endl;
	}
	mout_3 << endl;
	mout_3 << "---------------------------------ITEM SETS---------------------------------\n\n";
	for (i = 0; i <= len; i++)
	{
		if (S[i].size() == 0) break;
		mout_3 << "S[" << i << "]={";
		for (j = 0; j<S[i].size(); j++)
		{
			int rule = S[i][j].rule;
			int origin = S[i][j].origin;
			int next = S[i][j].next;
			if (j != 0)
				mout_3 << ", ";
			mout_3 << "[" << arr_3[rule].head << "->";
			string aux;
			aux = arr_3[rule].body;
			aux.insert(next, 1, '.');
			mout_3 << aux << "," << origin << "]";
			//mout_3<<"   ";
			//mout_3<<"("<<origin<<")\n";
		}
		mout_3 << "}\n";
	}
	mout_3 << "\n";
	if (k == 0)  goto label;
	mout_3 << "-----------------------------FINAL PRODUCTIONS-----------------------------\n\n";
	for (i = 0; i<k; i++)
	{
		int rule = ans[i];
		int next = arr_3[rule].body.size();
		mout_3 << arr_3[rule].head << "->";
		string aux;
		aux = arr_3[rule].body;
		aux.insert(next, 1, '.');
		mout_3 << aux << "   ";
		mout_3 << "(0)\n";
	}
label:
	mout_3 << endl;
	mout_3 << "---------------------------------RESULT------------------------------------\n";
	if (k == 0)
		mout_3 << "Syntax Error" << endl;
	else
		mout_3 << "Accept" << endl;
	mout_3.close();
}

