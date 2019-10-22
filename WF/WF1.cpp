#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<fstream>
using namespace std;

struct word{
    char name[30];
    int num;
    struct word *next;
};

void readfile(struct word*&head)
{
    FILE *fp;
    if((fp=fopen("J:/text.txt","r"))==NULL)
    { 
        printf("无法打开此文件!\n");
        exit(0);
    }
    char ch,temp[30];
    struct word *p;
    while(!feof(fp))
    {
        int i=0;
        ch=fgetc(fp);
        temp[0]=' '; 
        while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||temp[0]==' ')
        {
            if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
            {
                temp[i]=ch;
                i++;
            }
            ch=fgetc(fp);
            if(feof(fp)) break;
        }
        temp[i]='\0';
        p=head->next;
        while(p)
        {
            if(!_stricmp(temp,p->name)) 
            { 
                p->num++;break;
            } 
            p=p->next;
        }
        if(!p&&temp[0]!='\0')
        {
                p=new word;
                strcpy(p->name,temp);
                p->num=1;
                p->next=head->next;
                head->next=p;
        }
    }
}

void sort(struct word*&head,int N)
{    
    struct word *q;
    int a[N],i;
    for(i=0;i<N;i++)
        a[i]=0;
    printf("文章中出现频率最高的%d个单词如下:\n",N);
    for(i=0;i<N;i++)
    { 
        q=head;
        while(q!=NULL)
        { 
            if(q->num>a[i])
                a[i]=q->num;
            else
                q=q->next;
        } 
        q=head;
        while(q!=NULL)
        { 
            if(a[i]==q->num)
            { 
                q->num=0;
                printf("出现频率:%d\t",a[i]);
                puts(q->name);
                break;
            } 
            else 
                q=q->next;
        }
    }
}

int main()
{
    struct word *head;
    int n;
	printf("请输入查询几个出现频率最高的单词：");
    scanf("%d",&n);
    head=new word;
    head->next=NULL;
    readfile(head);
    sort(head,n);
}

