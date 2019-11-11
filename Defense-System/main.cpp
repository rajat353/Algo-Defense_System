#include<conio.h>
#include<windows.h>
#include <bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<math.h>
#include<vector>
#include<algorithm>
#include<queue>
#include<string.h>
#include<queue>
#include<stdlib.h>

#define num_zones 10
using namespace std;
class base
{
    public:
    string name;
    float lat;
    float lon;
    int troops;
};

class bases
{
public:
    string name;
    float lat;
    float lon;
    int troops;
};

class zones
{
public:
    int num_bases,num_troops;
    int lstart,lend;
    vector<bases*>b_list;
    zones()
    {
        num_bases=0;
        num_troops=0;
    }
};

class seg_node
{
    public:
    int val;
    int lfr,rfr;
    seg_node*left;
    seg_node*right;
    seg_node(int l,int r,int vl=0)
    {
        val=vl;
        left=NULL;
        right=NULL;
        lfr=l;
        rfr=r;
    }
};

seg_node* create(zones a[],int low,int high)
{
    if(low==high)
    {
        seg_node*temp1=new seg_node(low,high,a[low].num_troops);
        return temp1;
    }
    seg_node*temp=new seg_node(low,high);
    int mid=(low+high)/2;
    temp->left=create(a,low,mid);
    temp->right=create(a,mid+1,high);
    temp->val=temp->left->val+temp->right->val;
    return temp;

}

int query(seg_node*st,int ql,int qh)
{
    if(st==NULL)
        return 0;
    if(qh<st->lfr||ql>st->rfr)
        return 0;
    else if(st->lfr>=ql&&st->rfr<=qh)
        return st->val;
    else
    {
        return query(st->left,ql,qh)+query(st->right,ql,qh);
    }
}

void update(seg_node*temp,int index,int new_val)//not used yet
{
    if(temp==NULL)return;
    int mid=(temp->lfr+temp->rfr)/2;
    if(temp->lfr==temp->rfr&&temp->lfr==index)
    {
        temp->val=new_val;
        return;
    }
    else if(index>mid)
    {
        update(temp->right,index,new_val);;
    }
    else
    {
        update(temp->left,index,new_val);
    }
    temp->val=temp->left->val+temp->right->val;
    //temp->val=(temp->left==NULL?0:temp->left->val)+(temp->right==NULL?0:temp->right->val);
}

void show_bases(bases b[],int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<b[i].name<<" "<<b[i].lat<<" "<<b[i].lon<<" "<<b[i].troops<<"\n";
    }
}
void show_zones(zones z[])
{
    for(int i=0;i<num_zones;i++)
    {
        cout<<"\nZone "<<(i+1)<<"\n";
        for(int j=0;j<z[i].num_bases;j++)
        {
            cout<<(z[i].b_list[j])->name<<" "<<(z[i].b_list[j])->lat<<" "<<(z[i].b_list[j])->lon<<" "<<(z[i].b_list[j])->troops<<"\n";
        }
    }
    cout<<"\n\n";
}
zones* getzones()
{
    ifstream bs;
    bs.open("latData.txt");
    int num_base;
    bs>>num_base;
    bases *b=new bases[num_base];
    for(int i=0;i<num_base;i++)//getting bases
    {
        bs>>b[i].name>>b[i].lat>>b[i].lon>>b[i].troops;
    }
    bs.close();
    //show_bases(b,num_base);
    //zones , presently 10 change later
    zones *z=new zones[num_zones];
    for(int i=0;i<num_zones;i++)//latitudes ranging from 0 to 100
    {
        z[i].lstart=(i*10);
        z[i].lend=(i+1)*10;
    }
    //b=base_sort_lat(b,num_base);
    int k=0;//traversing the zones array ..
    for(int i=0;i<num_base;i++)// O(num_base) complexity
    {
        while(b[i].lat>z[k].lend)//bases in ascending order of latitudes
            k++;
        z[k].num_bases++;
        z[k].num_troops+=b[i].troops;
        z[k].b_list.push_back(b+i);
    }
    //show_zones(z);
    return z;
}

void zone_query(zones *z)
{

}

void transport_needed()
{
   ;
}

int max1(int a,int b)
{
    return (a>b?a:b);
}

void enemy_bases_to_capture()
{
    ;
}

int get_path(int **a,int n,int s,int d)
{
    int qu[n],path[n];
    int f,b,frst,pc,min1;
    pc=f=b=0;
    qu[0]=s;
    frst=-1;
    min1=100000000;
    bool fnd=false;
    bool visited[n];
    for(int ii=0;ii<n;ii++)
        visited[ii]=false;
    visited[s]=true;
    while(f<=b)
    {
        frst=qu[f++];
        for(int i=0;i<n;i++)
        {
            if(!visited[i]&&a[frst][i]>0)
            {
                qu[++b]=i;
                path[i]=frst;
                pc=i;
                visited[i]=true;
                if(i==d)
                {
                    fnd=true;
                    break;
                }
            }
        }
        if(fnd)
            break;
    }
    if(!fnd)
        return 0;
    else
    {
        int pc1=pc;
        while(pc1!=s)
        {
            if(a[path[pc1]][pc1]<min1)
                min1=a[path[pc1]][pc1];
            pc1=path[pc1];
        }
        while(pc!=s)
        {
            a[path[pc]][pc]-=min1;
            a[pc][path[pc]]+=min1;
            pc=path[pc];
        }
        return min1;
    }
}

int max_flow(int **a,int n,int s,int d)
{
    int mflow=0;
    int t=get_path(a,n,s,d);
    while(t)
    {
        mflow+=t;
        t=get_path(a,n,s,d);
    }
    return mflow;
}


void bytes_transfer()//ford fulkerson : network connectivity through OPTICAL FIBRES
{
   ;
}

void all_bases_shortest_path()//create an adjacency matrix for the bases file known as : bases2d.txt
{
  ;
}

void missile_interception_system()
{
   ;
}

base* loadBases(int *numBase)
{
    base *b;
    fstream mainFile;
    mainFile.open("bases.txt",ios::in);
    mainFile>>*numBase;
    b=new base[*numBase];
    for(int i=0;i<*numBase;i++)
    {
        mainFile>>b[i].name>>b[i].lat>>b[i].lon>>b[i].troops;
    }
    mainFile.close();
    return b;
}
float** makeGraph(base *b,int numBase)
{
    float **graph=new float*[numBase];
    for(int i=0;i<numBase;i++)
        graph[i]=new float[numBase];
    for(int i=0;i<numBase;i++)
    {
        graph[i][i]=0;
    }
    for(int i=0;i<numBase;i++)
    {
        for(int j=i+1;j<numBase;j++)
        {
            graph[j][i]=sqrt((b[i].lat - b[j].lat)*(b[i].lat - b[j].lat)+(b[i].lon - b[j].lon)*(b[i].lon - b[j].lon));
            graph[i][j]=graph[j][i];
        }
    }
    return graph;
}


void merges(base *b, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    base L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = b[l + i];
    for (j = 0; j < n2; j++)
        R[j] = b[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].lat <= R[j].lat)
        {
            b[k] = L[i];
            i++;
        }
        else
        {
            b[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        b[k] = L[i];
        i++;
        k++;
    }


    while (j < n2)
    {
        b[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(base *b, int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSort(b, l, m);
        mergeSort(b, m+1, r);

        merges(b, l, m, r);
    }
}


void sortLat(base *b,int numBase)
{
    mergeSort(b,0,numBase-1);
    fstream latFile;
    latFile.open("latData.txt",ios::out);
    latFile<<numBase<<"\n";
    for(int i=0;i<numBase;i++)
    {
        latFile<<b[i].name<<"\t"<<b[i].lat<<"\t"<<b[i].lon<<"\t"<<b[i].troops<<"\n";
    }
    latFile.close();
}



void display(float **g,int numBase)
{
    for(int i=0;i<numBase;i++)
    {
        for(int j=0;j<numBase;j++)
        {
            cout<<g[i][j]<<"\t";
        }
        cout<<"\n";
    }
}

 struct edge
{
   int start;
   int end;
   float length;
};

bool compare(edge a,edge b)
{
   return a.length<b.length;
}

int root(int a,int parent[],int n)
{
   while(parent[a]!=a)
   {
      parent[a]=parent[parent[a]];
      a=parent[a];
   }
 return a;
}

void findmst(float **graph,int n,base *bases)
{
 ;
 }
bool isConnected(int **g,int n)
{
    queue<int> q;
    int v[n];
    for(int i=0;i<n;i++)
    {
        v[i]=0;
    }
    v[0]=1;
    q.push(0);
    while(!q.empty())
    {
        int x=q.front();
        if(g[x][n-1])
            {
                return true;
            }
        for(int i=0;i<n-1;i++)
            {
                if(g[x][i] && !v[i])
                {
                    q.push(i);
                    v[i]=1;
                }
            }
        q.pop();
    }
    return false;
}
bool removeCity(int **g,int n,int c,vector<int> ch,int *minn,vector<int> &checks)
{
    if(!isConnected(g,n))
        {
            if(c<(*minn))
            {
                *minn=c;
                checks=ch;
            }
            return true;
        }
    for(int k=1;k<n-1;k++)
    {
        if(find(ch.begin(),ch.end(),k)!=ch.end())
            {
                continue;
            }
        int r[n],co[n];
        for(int i=0;i<n;i++)
        {
            r[i]=g[k][i];
            co[i]=g[i][k];
            g[k][i]=0;
            g[i][k]=0;
        }
        ch.push_back(k);
        removeCity(g,n,c+1,ch,minn,checks);
        for(int i=0;i<n;i++)
        {
            g[k][i]=r[i];
            g[i][k]=co[i];
        }
        ch.pop_back();
    }
    return false;
}
int **loadGraph2(int &num,string **bases)
{
    int **g;
    fstream enemy;
    enemy.open("ebases.txt",ios::in);
    enemy>>num;
    g=new int*[num];
    for(int i=0;i<num;i++)
    {
        g[i]=new int[num];
    }
    (*bases)=new string[num];
    for(int i=0;i<num;i++)
    {
    enemy>>(*bases)[i];
    }
for(int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {
            enemy>>g[i][j];
        }
    }
    enemy.close();
    return g;
}
void getBestDiv(int **g,int num,string *names)
{
  ;
}

struct tsp
{
int start;
int limit;
int **arr;
int *visited;
int n;
vector<int> temp;
vector<int> final1;
};

bool func(int a,int cost,int count,tsp &tool)
{
   tool.temp.push_back(a);
   if(count==tool.n)
   {
       if(tool.arr[a][tool.start] && cost+tool.arr[a][tool.start]<tool.limit)
       {
          tool.limit=cost+tool.arr[a][tool.start];
          tool.final1.clear();
          tool.final1.assign(tool.temp.begin(),tool.temp.end());
       }
      return true;
   }

   tool.visited[a]=1;

   for(int i=0;i<tool.n;i++)
   {
      if(tool.arr[a][i]>0 && tool.visited[i]!=1 && cost+tool.arr[a][i]<=tool.limit)
      {
         func(i,cost+tool.arr[a][i],count+1,tool);
      }
   }
  tool.visited[a]=0;
   tool.temp.pop_back();
return true;
}

void travel(int **graph,int n,string *bases)
{
   tsp auxi;

   auxi.arr=graph;
   auxi.n=n;
   auxi.limit=INT_MAX;

   for(int i=0;i<n;i++)
   {
    auxi.visited=new int[auxi.n];
    auxi.start=i;
    auxi.temp.clear();
    func(auxi.start,0,1,auxi);
   }

   cout<<" PATH:: ";

   for(int i=0;i<auxi.final1.size();i++)
   {
      cout<<bases[auxi.final1[i]]<<" -> ";
   }
   cout<<"\n\n TOTAL DISTANCE:: "<<auxi.limit;
}



void outFile(float **g,int n)
{
  ;
}
int string_match_rk(string pat,string txt)
{
    int freq=0;
    int q=101;//some prime
    int d=256;
    int M=pat.length();
    int N=txt.length();
    int i,j;
    int p=0;
    int t=0;
    int h=1;
    for(i=0;i<M-1;i++)
        h=(h*d)%q;
    for(i=0;i<M;i++)
    {
        p=(d*p+pat[i])%q;
        t=(d*t+txt[i])%q;
    }
    for(i=0;i<=N-M;i++)
    {
        if(p==t)
        {
            for(j=0;j<M;j++)
            {
                if(txt[i+j]!=pat[j])
                    break;
            }
            if(j==M)
            {
                cout<<"Threat word \""<<pat<<"\" found at index: "<<i<<endl;
                freq++;
            }
        }
        if(i<N-M)
        {
            t=(d*(t-txt[i]*h)+txt[i+M])%q;
            if(t<0)
              t=(t+q);
        }
    }
    return freq;
}

void check_for_threats()
{
    ifstream fp,lt;
    fp.open("trigger_words.txt");
    lt.open("threat_letter.txt");
    int num;
    fp>>num;
    string twords[num];
    int tcount=0;
    string letter="";
    for(int i=0;i<num;i++)
        fp>>twords[i];
    while(!lt.eof())
    {
        string temp;
        lt>>temp;
        letter+=' ';
        letter+=temp;
    }
    int freq=0;
    for(int i=0;i<num;i++)
    {
        freq+=string_match_rk(twords[i],letter);
    }
    cout<<"The number of threat words are : "<<freq;
}


void gotoxy(int x,int y)
{

    for(int i=0;i<y;i++)
    {
     cout<<"\n";
    }
    for(int i=0;i<x;i++)
    {
     cout<<" ";
    }
}

char* typepass()
{

  ;
}

void initialize()
{
    system("cls");

  for(int i=0;i<2;i++)
  {
    gotoxy(25,10);
    cout<<"LOGGING-IN SECURELY     /-";
    Sleep(700);
    system("cls");


    gotoxy(25,10);
    cout<<"LOGGING-IN SECURELY    -\\ ";
    Sleep(700);
    system("cls");
  }

  for(int i=0;i<2;i++)
  {
    gotoxy(25,10);
    cout<<"LOADING DATABASE     /-";
    Sleep(700);
    system("cls");


    gotoxy(25,10);
    cout<<"LOADING DATABASE    -\\ ";
    Sleep(700);
    system("cls");
  }

}
struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;
    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare1 {

    bool operator()(MinHeapNode* l, MinHeapNode* r)

    {
        return (l->freq > r->freq);
    }
};

void printCodes(struct MinHeapNode* root, string str,vector<pair<char,string> > &table2)
{

    if (!root)
        return;

    if (root->data != '$')
    {
        cout << root->data << ": " << str << "\n";
        table2.push_back(make_pair(root->data,str));
    }
    printCodes(root->left, str + "0",table2);
    printCodes(root->right, str + "1",table2);
}


void HuffmanCodes(vector<pair<char,int> > table,vector<pair<char,string> > &table2)
{
    struct MinHeapNode *left, *right, *top;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare1> minHeap;

    for (int i = 0; i < table.size(); ++i)
        minHeap.push(new MinHeapNode(table[i].first, table[i].second));
    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    printCodes(minHeap.top(), "",table2);
}

void compHuff()
{
    fstream getText;
    getText.open("message.txt",ios::in);
    string text;
    getText>>text;
    while(!getText.eof())
        {
            string x;
            getText>>x;
            text+='^';
            text+=x;
        }
    int freq[128];
    vector<pair<char,int> > table;
    vector<pair<char,string> > table2;
    for(int i=0;i<128;i++)
        {
            freq[i]=0;
        }
    for(int i=0;i<text.size();i++)
        {
            freq[text[i]]++;
        }
    for(int i=0;i<128;i++)
        {
            if(freq[i])
            {
                table.push_back(make_pair(i,freq[i]));
            }
        }
    getText.close();

    HuffmanCodes(table,table2);
    fstream emess;
    int bitMes=0;
    emess.open("encMes.txt",ios::out);
    emess<<table2.size()<<"\n";
    for(int i=0;i<table2.size();i++)
    {
        emess<<table2[i].first<<"\t"<<table2[i].second<<"\n";
    }
    getText.open("message.txt",ios::in);
    for(int j=0;j<text.size();j++)
    {
        for(int i=0;i<table2.size();i++)
        {
            if(text[j]==table2[i].first)
            {
                emess<<table2[i].second;
                bitMes+=table2[i].second.size();
            }
        }
    }
    getText.close();
    emess.close();
    cout<<"Size of Message to be transmitted : "<<text.size()<<" bytes\n";
    cout<<"Size of the compressed message sent : "<<bitMes/8+1<<" bytes\n";
    cout<<"Sending the encrypting Message...\n...\n...\n";
}

void decomHuff()
{
    cout<<"Decoding!!!\n\n";
    cout<<"Decoded Message:\n";
    vector<pair<char,string> > table;
    fstream emess;
    emess.open("encMes.txt",ios::in);
    int n;
    emess>>n;
    for(int i=0;i<n;i++)
    {
        char x;
        string y;
        emess>>x>>y;
        table.push_back(make_pair(x,y));
    }
    string encM,temp="";
    emess>>encM;
    for(int i=0;i<encM.size();i++)
    {
        temp+=encM[i];
        for(int j=0;j<n;j++)
        {
            if(temp==table[j].second)
            {
                if(table[j].first=='^')
                    cout<<" ";
                else
                    cout<<table[j].first;
                temp="";
            }
        }
    }
    emess.close();
}

void menu()
{

    int numBase;
    base *bases1;
    int **egraph;
    int numEB;
    string *ebaseNames;
    float **graph;
    bases1=loadBases(&numBase);
    graph=makeGraph(bases1,numBase);
    //display(graph,numBase);
    //outFile(graph,numBase);
    egraph=loadGraph2(numEB,&ebaseNames);
    sortLat(bases1,numBase);
    zones *z=getzones();
    while(true){

   int choice;
    cout<<"\nWelcome to Indian Military Defense System!\n\n";
    cout<<"1. MISSILE INTERCEPTION SYSTEM \n";
    cout<<"2. PARALYSE ENEMY BASE NETWORK\n";
    cout<<"3. OPTIMAL ROUTE OF ATTACK  \n";
    cout<<"4. AVAILABLE MANPOWER IN THE ZONES  \n";
    cout<<"5. EFFIECIENT VEHICLES UTILISATION  \n";
    cout<<"6. IMPORTANT ENEMY BASES TO CAPTURE \n";
    cout<<"7. OPTICAL FIBER NETWORK CONNECTIVITY \n";
    cout<<"8. MINIMUM DISTANCE BETWEEN TWO BASES  \n";
    cout<<"9. MINIMUM INFRASTRUCTURE NEEDED IN CASE OF EMERGENCY \n";
    cout<<"10.MESSAGE INTERCEPTION \n";
    cout<<"11.ENCODE A MESSAGE \n";
    cout<<"12.DECODE A MESSAGE \n\n\n";
    cout<<"ENTER YOUR CHOICE :: ";
    cin>>choice;

    switch(choice)
    {
       case 1:    missile_interception_system();
                  break;
       case 2:   getBestDiv(egraph,numEB,ebaseNames);
                  break;
       case 3:    travel(egraph,numEB,ebaseNames);
                  break;
       case 4:    zone_query(z);
                  break;
       case 5:    transport_needed();
                  break;
       case 6:    enemy_bases_to_capture();
                  break;
       case 7:    bytes_transfer();
                  break;
       case 8:    all_bases_shortest_path();
                  break;
       case 9:    findmst(graph,numBase,bases1);
                  break;
       case 10:   check_for_threats();
                  break;
       case 11:   compHuff();
                  break;
        case 12:  decomHuff();
                  break;
        default : return;
      }
    }

}

int main()
{
    initialize();
   menu();
   return 0;
}
