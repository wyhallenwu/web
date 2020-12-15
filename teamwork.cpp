#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int mad = 1;//出现的标志
struct word
{
	string w;//单词
	int fz;//频率
	int locate;//出现顺序
	word *next;
	word *pre;
	word() :next(NULL),pre(NULL){}
	word(const string &w_, word *pre_ = NULL, word *next_ = NULL,int fz_=1,int locate_=0) :w(w_), pre(NULL), next(NULL),fz(fz_),locate(locate_){ next = next_; pre = pre_; }
};
bool operator == (const string &n, const string &m)//==重载
{
	if (n.size() != m.size())
		return false;
	for (int i = 0; i < n.length(); i++)
	{
		if (n[i] != m[i])
			return false;
	}
	return true;
}
class Alist
{
private:
	word *head;
	int lenth = 0;
public:
	Alist();
	Alist(string *x,int lenth);
	virtual ~Alist();
	void Show() const;
	void Clear();
	void Delete(int x);
	void Add(int x,const string &data);//没用
	void Add(const string &data);
	friend ostream & operator << (ostream &out, const Alist &data);
	int Find(int fz_,int locate_);
	void Sort(int x,int y);
	void Add(int x, int y, const string &data,int z);
	friend void Load(char *filename,Alist &data);
	friend void Save(const char *filename, Alist &data);
};
Alist::Alist()//无参构造
{
	head = new word;
	head->next = head->pre = head;
	lenth = 0;
}
Alist::Alist(string *x,int lenth_):head(NULL),lenth(lenth_)
{
	if (!x)
		return;
	word *p;
	p = head = new word;
	for (int i = 0; i < lenth_; i++)
	{
		p->next = new word(x[i], p);
		p = p->next;
		p->locate = mad;
		mad++;
	}
	head->pre = p;
	p->next = head;
}
Alist::~Alist()//析构
{
	Clear();
	delete head;
}
void Alist::Add(int x,int y,const string &data,int z)//将频率增加的单词添加到适当位置
{
	if (x < 0) 
		return;
	word *p = head->next;
	if (x == 0)
	{
		word *pa = new word(data, head, p, y,z);
		head->next = pa;
		p->pre = pa;
		return;
	}
	for (int i = 1; i < x; i++)
		p = p->next;
	word *pa = new word(data, p, p->next,y,z);
	p->next->pre = pa;
	p->next = pa;
	lenth++;
}
void Alist::Sort(int x,int y)//删除原节点，插入新节点
{
	word *p = head->next;
 	for (int i = 1; i < x; i++)
		p = p->next;
	int fzz = p->fz;
	string ww = p->w;
	int madd = p->locate;
	if (x > y) {
		Delete(x);
		Add(y, fzz, ww, madd);
	}
	else
	{
		Add(y+1, fzz, ww, madd);
		Delete(x);
	}
}
void Alist::Delete(int x)//根据位置删除节点
{
	if (x < 0)
		return;
	word *p = head->next;
	for (int i = 1; i < x; i++)
		p = p->next;
	p->pre->next = p->next;
	p->next->pre = p->pre;
	delete p;
	lenth--;
}
int Alist::Find(int fz_,int locate_)//寻找节点添加的位置
{
	int count = 1;
	word *p = head->next;
	for (; p != head; p = p->next)
	{
		if (p->fz == fz_)
		{
			if (p->locate > locate_)
				return count;
			count++;
		}
		else if (p->fz < fz_) {

			return count;
		}
		else
			count++;
	}
	return -1;
}
void Alist::Clear()//清空链表
{
	while (lenth > 0)
		Delete(1);
	lenth = 0;
}
void Alist::Add(const string &data)//读入时的插入函数
{
	int count = 0;
	word *p = head->next;
	for (; p != head; p = p->next)//若前面有相同的单词
	{
		count++;//现在的位置
		if (p->w == data)
		{
			p->fz++;
			int n = Find(p->fz,p->locate);//应该插入的位置
			if (count == 1||n==-1||count==n-1)
				return;
			Sort(count, n-1);
			return;
		}
	}
	if (p == head)//插入的是新的单词
	{
		p = head->pre;
		p->next = new word(data, p, head,1,mad++);
		p = p->next;
		head->pre = p;
		lenth++;
	}
}
void Alist::Show() const
{
	int i = 1;
	word *p = head->next;
	while (p!=head)
	{
		cout << i << " ";
		cout << p->w << " " << p->fz << endl;
		p = p->next;
		i++;
	}
}
void Alist::Add(int x,const string &data)
{
	if (x < 0)
		return;
	word *p = head->next;
	for (int i = 1; i < x; i++)
		p = p->next;
	word *pa = new word(data, p, p->next);
	p->next->pre = pa;
	p->next = pa;
	lenth++;
}
ostream & operator << (ostream &out, const Alist &data)
{
	data.Show();
	return out;
}
void Load(const char *filename, Alist &data)
{
	ifstream infile(filename);
	string c;
	while (infile>>c)
		data.Add(c);
	infile.close();
}
void Save(const char *filename, Alist &data)
{
	ofstream outfile(filename);
	int i = 1;
	word *p = data.head->next;
	while (p != data.head)
	{
		outfile << i << " ";
		outfile << p->w << " " << p->fz << endl;
		p = p->next;
		i++;
	}
	outfile.close();
}
int main()
{
	Alist tst;
	Load("read.txt",tst);
	cout << tst << endl;
	Save("result.txt", tst);
	return 0;
}