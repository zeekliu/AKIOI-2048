#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
namespace col{
	void rgb_init(){
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwInMode, dwOutMode;
		GetConsoleMode(hIn, &dwInMode);
		GetConsoleMode(hOut, &dwOutMode);
		dwInMode|=0x0200;dwOutMode|=0x0004;
		SetConsoleMode(hIn, dwInMode);
		SetConsoleMode(hOut, dwOutMode);
	}
	void rgb_set(int wr,int wg,int wb,int br,int bg,int bb){
		printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,br,bg,bb);
	}
	void rgb(int A,int B,int C){rgb_set(255,255,255,A,B,C);}
	void bk_b(){rgb_set(255,255,255,0,0,0);}
	void scr(string COL){
		string CS="color "+COL;char A[10];
		for(int i=0;i<CS.size();i++)A[i]=CS[i];
		system(A);
	}
}

#define fr(i,a,b) for(int i=a;i<b;i++)
struct numb{
	int x,c1,c2,c3;
};
int tmp1,tmp2,tmp3,mapp[4][4];
map<int,string> mp,ex;
map<string,numb> m2;char c='*';

namespace rnd{
	int zt(){
		srand(time(0));int aNs=rand(),Xx,Yy;
		aNs=rand()*rand()%rand()%35;
		int zt[15+8+3+5+3+1]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,4,2,2,2,4,4,2,2,9,9,10};
		fr(i,0,10){
			Xx=rand()*i%30;Yy=rand()*(i+1)%35;
			swap(zt[Xx],zt[Yy]);
		}
		return zt[aNs];
	}
	int pos(){
		vector<int> Ans;
		fr(i,0,4)
			fr(j,0,4)
				if(mapp[i][j]==0)Ans.push_back(i*4+j);
		if(Ans.size()==0)return -1;
		srand(time(0));int aNs=rand();
		aNs=rand()*rand()%rand()%Ans.size();
		return Ans[aNs];
	}
}

namespace prt{
	void line(int A1,int A2,int A3,int A4){
		cout<<"| ";
		col::rgb(m2[mp[A1]].c1,m2[mp[A1]].c2,m2[mp[A1]].c3);
		cout<<mp[A1];col::bk_b();cout<<" | ";
		col::rgb(m2[mp[A2]].c1,m2[mp[A2]].c2,m2[mp[A2]].c3);
		cout<<mp[A2];col::bk_b();cout<<" | ";
		col::rgb(m2[mp[A3]].c1,m2[mp[A3]].c2,m2[mp[A3]].c3);
		cout<<mp[A3];col::bk_b();cout<<" | ";
		col::rgb(m2[mp[A4]].c1,m2[mp[A4]].c2,m2[mp[A4]].c3);
		cout<<mp[A4];col::bk_b();cout<<" | "<<endl;
	}
	void zt(){
		for(int i=2;i<=8192;i*=2){
			cout<<i<<"   ";
			col::rgb(m2[mp[i]].c1,m2[mp[i]].c2,m2[mp[i]].c3);
			cout<<mp[i];col::bk_b();cout<<"   "<<ex[i]<<endl<<endl;
		}
		for(int i=9;i<=11;i++){
			cout<<i<<"   ";
			col::rgb(m2[mp[i]].c1,m2[mp[i]].c2,m2[mp[i]].c3);
			cout<<mp[i];col::bk_b();cout<<"   "<<ex[i]<<endl<<endl;
		}
	}
	void pmap(){
		cout<<" _____ _____ _____ _____"<<endl;
		prt::line(mapp[0][0],mapp[0][1],mapp[0][2],mapp[0][3]);
		cout<<" _____ _____ _____ _____"<<endl;
		prt::line(mapp[1][0],mapp[1][1],mapp[1][2],mapp[1][3]);
		cout<<" _____ _____ _____ _____"<<endl;
		prt::line(mapp[2][0],mapp[2][1],mapp[2][2],mapp[2][3]);
		cout<<" _____ _____ _____ _____"<<endl;
		prt::line(mapp[3][0],mapp[3][1],mapp[3][2],mapp[3][3]);
		cout<<" _____ _____ _____ _____"<<endl;
	}
}

namespace move{
	void up(){
		int J;
		fr(i,0,4){
			fr(j,1,4){
				J=j;
				while(J>0&&mapp[--J][i]==0)mapp[J][i]=mapp[J+1][i],mapp[J+1][i]=0;
				J++;
				if(J==0)continue;
				if(mapp[J][i]==mapp[J-1][i]&&mapp[J][i]!=11&&mapp[J][i]!=10&&mapp[J][i]!=9){
					mapp[J-1][i]*=2;
					mapp[J][i]=0;
				}
				else if(mapp[J][i]==mapp[J-1][i]){
					mapp[J-1][i]++;
					mapp[J][i]=0;
				}
				if((mapp[J][i]==9||mapp[J][i]==10||mapp[J][i]==11)&&mapp[J-1][i]>0){
					mapp[J-1][i]*=pow(2,mapp[J][i]-9);
					mapp[J][i]=0;
				}
				if((mapp[J-1][i]==9||mapp[J-1][i]==10||mapp[J-1][i]==11)&&mapp[J][i]>0){
					mapp[J-1][i]=mapp[J][i]*pow(2,mapp[J-1][i]-9);
					mapp[J][i]=0;
				}
			}
		}
		return;
	}
	void down(){
		int J;
		fr(i,0,4){
			for(int j=2;j>=0;j--){
				J=j;
				while(J<3&&mapp[++J][i]==0)mapp[J][i]=mapp[J-1][i],mapp[J-1][i]=0;
				J--;
				if(J==3)continue;
				if(mapp[J][i]==mapp[J+1][i]&&mapp[J][i]!=11&&mapp[J][i]!=10&&mapp[J][i]!=9){
					mapp[J+1][i]*=2;
					mapp[J][i]=0;
				}
				else if(mapp[J][i]==mapp[J+1][i]){
					mapp[J+1][i]++;
					mapp[J][i]=0;
				}
				if((mapp[J][i]==9||mapp[J][i]==10||mapp[J][i]==11)&&mapp[J+1][i]>0){
					mapp[J+1][i]*=pow(2,mapp[J][i]-9);
					mapp[J][i]=0;
				}
				if((mapp[J+1][i]==9||mapp[J+1][i]==10||mapp[J+1][i]==11)&&mapp[J][i]>0){
					mapp[J+1][i]=mapp[J][i]*pow(2,mapp[J+1][i]-9);
					mapp[J][i]=0;
				}
			}
		}
		return;
	}
	void right(){
		int J;
		fr(i,0,4){
			for(int j=2;j>=0;j--){
				J=j;
				while(J<3&&mapp[i][++J]==0)mapp[i][J]=mapp[i][J-1],mapp[i][J-1]=0;
				J--;
				if(J==3)continue;
				if(mapp[i][J]==mapp[i][J+1]&&mapp[i][J]!=11&&mapp[i][J]!=10&&mapp[i][J]!=9){
					mapp[i][J+1]*=2;
					mapp[i][J]=0;
				}
				else if(mapp[i][J]==mapp[i][J+1]){
					mapp[i][J+1]++;
					mapp[i][J]=0;
				}
				if((mapp[i][J]==9||mapp[i][J]==10||mapp[i][J]==11)&&mapp[i][J+1]>0){
					mapp[i][J+1]*=pow(2,mapp[i][J]-9);
					mapp[i][J]=0;
				}
				if((mapp[i][J+1]==9||mapp[i][J+1]==10||mapp[i][J+1]==11)&&mapp[i][J]>0){
					mapp[i][J+1]=mapp[i][J]*pow(2,mapp[i][J+1]-9);
					mapp[i][J]=0;
				}
			}
		} 
		return;
	}
	void left(){
		int J;
		fr(i,0,4){
			fr(j,1,4){
				J=j;
				while(J>0&&mapp[i][--J]==0)mapp[i][J]=mapp[i][J+1],mapp[i][J+1]=0;
				J++;
				if(J==0)continue;
				if(mapp[i][J]==mapp[i][J-1]&&mapp[i][J]!=11&&mapp[i][J]!=10&&mapp[i][J]!=9){
					mapp[i][J-1]*=2;
					mapp[i][J]=0;
				}
				else if(mapp[i][J]==mapp[i][J-1]){
					mapp[i][J-1]++;
					mapp[i][J]=0;
				}
				if((mapp[i][J]==9||mapp[i][J]==10||mapp[i][J]==11)&&mapp[i][J-1]>0){
					mapp[i][J-1]*=pow(2,mapp[i][J]-9);
					mapp[i][J]=0;
				}
				if((mapp[i][J-1]==9||mapp[i][J-1]==10||mapp[i][J-1]==11)&&mapp[i][J]>0){
					mapp[i][J-1]=mapp[i][J]*pow(2,mapp[i][J-1]-9);
					mapp[i][J]=0;
				}
			}
		}
		return;		
	}
}
int N,MP[10000][4][4],highest[10000];string tim[10000];
namespace history{
	void get(){
		freopen("history.txt","r",stdin);
		cin>>N;
		fr(i,0,N){
			fr(j,0,4)
				fr(k,0,4)cin>>MP[i][j][k];
			cin>>highest[i]>>tim[i];
		}
		fclose(stdin);
		freopen("CON","r",stdin);
	}
	void save(){
		ofstream out("history.txt");
		N++;
		out<<N<<endl;
		int high=0;
		fr(i,0,4){
			fr(j,0,4){
				out<<mapp[i][j]<<' ';
				high=max(high,mapp[i][j]);
			}
			out<<endl;
		}
		out<<high<<' ';
		time_t rawtime;
		struct tm *ptminfo;
		time(&rawtime);
		ptminfo = localtime(&rawtime);
		out<<ptminfo->tm_year + 1900<<'-'<<ptminfo->tm_mon + 1<<'-'<<ptminfo->tm_mday<<'-'<<ptminfo->tm_hour<<':'<< ptminfo->tm_min<<':'<< ptminfo->tm_sec<<endl;
		fr(i,0,N-1){
			fr(j,0,4){
				fr(k,0,4)out<<MP[i][j][k]<<' ';
				out<<endl;
			}
			out<<highest[i]<<' '<<tim[i]<<endl;
		}
		out.close();
	}
	void prt_m(){
		fr(i,0,N)
			cout<<i<<": best:"<<highest[i]<<" time:"<<tim[i]<<endl;
	}
	void prt(){
		prt_m();
		cout<<"input the number you want to see,input -1 to get back to the game"<<endl;
		int now;
		cin>>now;
		numb temp;
		while(now>=0){
			fr(i,0,4){
				fr(j,0,4){
					temp=m2[mp[MP[now][i][j]]];
					col::rgb(temp.c1,temp.c2,temp.c3);
					cout<<mp[MP[now][i][j]];
					col::bk_b();
					cout<<' ';
				}
				cout<<endl;
			}
			cout<<"highest:"<<highest[now]<<" time:"<<tim[now]<<endl;
			cout<<"press any key to get back to the history menu";
			while(!kbhit());
			system("cls");
			cout<<"input the number you want to see,input -1 to get back to the game"<<endl;
			history::prt_m();cin>>now;
		}
		system("cls");
	}
}

void color(string STR){
	srand(time(0));
	fr(i,0,STR.size()){
		tmp1=rand()%256;
		tmp2=rand()%256;
		tmp3=rand()%256;
		col::rgb(tmp1,tmp2,tmp3);
		cout<<STR[i];Sleep(30);
		col::bk_b();
	}
}

void p2(string S,int P,int R,int G,int B){m2[S]=numb{P,R,G,B};}
void inti(){
	fr(i,0,4)
		fr(j,0,4)mapp[i][j]=0;
	mp[0]="   ";
	mp[2]="CE ";
	ex[2]="Compile Error";
	p2("CE ",2,200,200,1);
	mp[4]="RE ";
	ex[4]="Runtime Error";
	p2("RE ",4,255,0,200);
	mp[8]="TLE";
	ex[8]="Time Limit Exceeded";
	p2("TLE",8,120,0,120);
	mp[16]="MLE";
	ex[16]="Memory Limit Exceeded";
	p2("MLE",16,150,50,150);
	mp[32]="ILE";
	ex[32]="Idleness Limit Exceeded";
	p2("ILE",32,47,255,150);
	mp[64]="OLE";
	ex[64]="Output Limit Exceeded";
	p2("OLE",64,250,38,250);
	mp[128]="UKE";
	ex[128]="UnKnown Error";
	p2("UKE",128,70,70,70);
	mp[256]="WA ";
	ex[256]="Wrong Answer";
	p2("WA ",256,255,0,0);
	mp[512]="SJE";
	ex[512]="Special Judge Error";
	p2("SJE",512,60,209,180);
	mp[1024]="PC ";
	ex[1024]="Partically Correct";
	p2("PC ",1024,230,100,57);
	mp[2048]="AC ";
	ex[2048]="ACcepted";
	p2("AC ",2048,0,230,70);
	mp[4096]="AU ";
	ex[4096]="Au";
	p2("AU ",4096,10,250,10);
	mp[8192]="AK ";
	ex[8192]="All Killed";
	p2("AK ",8192,255,140,100);
	mp[9]="###";
	ex[9]="#pragma GCC...   (×1)";
	p2("###",9,40,40,40);
	mp[10]="O2 ";
	ex[10]="#pragma GCC optimize(2)  (×2)";
	p2("O2 ",10,0,170,170);
	mp[11]="O3 ";
	ex[11]="#pragma GCC optimize(3)  (×4)";
	p2("O3 ",11,0,150,150);
}
int inti2(){
	cout<<"press wasd to move,press v to save,press m to look at status,press e to end the game,press h to look at your history"<<endl;
	int zt=rnd::zt(),pos=rnd::pos();
	if(pos==-1)return -1;
	mapp[pos/4][pos%4]=zt;prt::pmap();
	return 7;
}

int main(){
	col::rgb_init();
play:	color("Welcome to ak-ioi2048");
	cout<<endl;Sleep(100);
	color("START");Sleep(500);
	system("cls");
	inti();history::get();
	prt::zt();
	cout<<"you can look at this by pressing 'm' after the game starts"<<endl;
	Sleep(2000);
	system("cls");
	int X=inti2();bool f=0;
	while(1){
		while(!kbhit());
		c=getch();
		f=0;
		if(c=='w')move::up();
		else if(c=='s')move::down();
		else if(c=='a')move::left();
		else if(c=='d')move::right();
		else if(c=='m'){
			system("cls");
			prt::zt();
			Sleep(2000);
			system("cls"); 
			cout<<"press wasd to move,press v to save,press m to look at status,press e to end the game,press h to look at your history"<<endl;
			prt::pmap();f=1;
		}
		else if(c=='e')break;
		else if(c=='v'){
			system("cls");
			history::save();
			cout<<"saved!";
			Sleep(1000);
			system("cls");
			cout<<"press wasd to move,press v to save,press m to look at status,press e to end the game,press h to look at your history"<<endl;
			prt::pmap();f=1;
		}
		else if(c=='h'){
			system("cls");
			history::prt();
			cout<<"press wasd to move,press v to save,press m to look at status,press e to end the game,press h to look at your history"<<endl;
			prt::pmap();f=1;
		}
	  	if(!f){
			system("cls");
			X=inti2();
			if(X==-1){
				color("YOU LOSE");
				break;
			}
		}
	}
	history::save();string ANSP;
	Sleep(1000);system("cls");
	cout<<"maker:wangyangwen"<<endl<<"want to play again?(yes/no)";
	cin>>ANSP;
	if(ANSP=="yes")goto play;
	return 0;
}
