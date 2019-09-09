
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <ctype.h> 
#include <string>
#include <errno.h> 
#include<bits/stdc++.h>
#include<map>
#include <fcntl.h>

using namespace std;
string str1;
char *argv[10];
char *f_ali[10];
 map<string,string>m;
 char *argvpipe[256];
int count_pipes=0;
const int size=256;

char*a[10];
char *b[10];
char *c[10];
char *f[10];

//char *argv[10];
#define BUFFSIZE 100


struct trieNode{
   struct trieNode* child[size];
   bool isEnd;
};

struct trieNode * newNode(){
  struct trieNode *temp=new trieNode;
  temp->isEnd=false;
  for(int i=0;i<size;i++){
    temp->child[i]=NULL;
  }

  return temp;
}

void insert(struct trieNode *root,string data){

  struct trieNode *temp=root;
  int length=data.length();
  for(int i=0;i<length;i++){
    int index=data[i];

    if(temp->child[index]==NULL){
      temp->child[index]=newNode();
    }

    temp=temp->child[index];
  }

   temp->isEnd=true;
}

struct trieNode* search(struct trieNode *root,string data ){

  struct trieNode *temp=root;
  int length=data.length();
  for(int i=0;i<length;i++){
    int index=data[i];

    if(temp->child[index]==NULL)
      return temp;
    else{
      temp=temp->child[index];
      continue;
    }
  }
    
  return( temp);
    
}

void display(char *p,struct trieNode *root,int level,string k)
{
  int j;
  if(root->isEnd){
    p[level]='\0';
    string str1=p;
    string result=k+str1;
    cout<<result<<endl;
  }


  for(j=0;j<size;j++){
    if(root->child[j]){
      p[level]=j;
      display(p,root->child[j],level+1,k);
    }
    else{
      continue;
    }
  }


  
}
int j=0;
char ans[20];
int level=0;

void display_t(string p,struct trieNode *root){
  // cout<<p[j];

  // if(p[j]==NULL){
  //   display(ans,root,level);
    
  // }
  // for(int i=0;i<size;i++){
  //   if(root->child[p[j]]!=NULL){
  //     j++;
  //     display_t(p,root->child[p[j]]);
  //   }

  struct trieNode* temp=search(root,p);
  display(ans,temp,level,p);
}


int count_the_insertions;
void removeDupWord(char str[]) 
{ 
     
    char *token = strtok(str, " ");;
    argv[0]=token;
    count_the_insertions++;
    int i=1;
    while (token != NULL) 
    { 
        
        token = strtok(NULL, " ");
        argv[i]=token;
        
        i++;
        count_the_insertions++;
        
    }

    argv[i]=NULL;
} 

void removeDupWord_map(char str[]) 
{ 
     
    char *token = strtok(str," ");;
    f_ali[0]=token;
    int i=1;
    while (token != NULL) 
    { 
        
        token = strtok(NULL, "=");
        f_ali[i]=token;
        i++;
        
    } 
    f_ali[i]=NULL;
}

void removeWord_append(char str[]) 
{ 
     
    char *token = strtok(str,">>");;
    argv[0]=token;
    int i=1;
    while (token != NULL) 
    { 
        
        token = strtok(NULL, ">>");
        argv[i]=token;
        
        i++;
        
    } 
} 

void removeWord_copy(char str[]) 
{ 
     
    char *token = strtok(str,">");;
    argv[0]=token;
    int i=1;
    while (token != NULL) 
    { 
        
        token = strtok(NULL, ">");
        argv[i]=token;
        
        i++;
        
    } 
}

void removeDupWord_pipe(char str[]) 
{ 
    char *token = strtok(str, "|");;
    argv[0]=token;
    int i=1;
    while (token != NULL) 
    { 
        
        token = strtok(NULL, "|");
        count_pipes++;
        argv[i]=token;
        
        i++;
        
    } 
} 

void removeDupWordspace0(char str[]){

  char *token = strtok(str, " ");

    a[0]=token;
    int i=1;
    while (token != NULL) 
    { 
        
        token = strtok(NULL, " ");
        a[i]=token;
        
        i++;
        
    } 

    a[i]=NULL;


}

void removeDupWordspace1(char str[]){

    char *token = strtok(str, " ");

    b[0]=token;
    int i=1;
    while (token != NULL) 
    { 
        
        token = strtok(NULL, " ");
        b[i]=token;
        
        i++;
        
    } 

    b[i]=NULL;


}

void removeDupWordspace2(char str[]){

    char *token = strtok(str, " ");

    c[0]=token;
    int i=1;
    while (token != NULL) 
    { 
        
        token = strtok(NULL, " ");
        c[i]=token;
        
        i++;
        
    } 

    c[i]=NULL;


}

void removeDupWordspace3(char str[]){

    char *token = strtok(str, " ");

    f[0]=token;
    int i=1;
    while (token != NULL) 
    { 
        
        token = strtok(NULL, " ");
        f[i]=token;
        
        i++;
        
    } 

    f[i]=NULL;


}

 void pipeline(char ***command)
{
  pid_t pid_h;
  int file_descriptor_dis=0; 
  int fd_h[2];       

  while (*command!=NULL){
    pipe(fd_h);       
    if ((pid_h = fork())==-1) {
      cout<<" your fork failed";
      exit(1);
    }
    else if (pid_h==0) {
      dup2(file_descriptor_dis,0);
      close(fd_h[0]);
      if (*(command+1)!=NULL) {
        dup2(fd_h[1],1);
      }
      execvp((*command)[0],*command);
      exit(1);
    }
    else {
      wait(NULL);    
      close(fd_h[1]);
      file_descriptor_dis=fd_h[0];
      command++; 
    }
  }
}

int main()
{
  printf(">");
  struct trieNode *root = newNode();
  while(getline(cin,str1)){



    insert(root,str1);

    char *tr=(char *)calloc(str1.length() + 1, sizeof(char));;
    strcpy(tr,str1.c_str());
    removeDupWord(tr);


     
     string p="h";
     string history="history";
     string record_start="record start";
     //cout<<argv[1];
     if(strcmp(p.c_str(),argv[0])==0){
      string str=argv[1];
      display_t(str,root);
      printf("\n");
      printf(">"); 
        }

      char all[20];
      if(strcmp(history.c_str(),argv[0])==0){
        string str="->";
        display(ans,root,level,str);
        printf("\n");
      printf(">"); 
      }
      string str10="cd";
      string str11="~";
      if(strcmp(str10.c_str(),argv[0])==0 ){
        if(strcmp(str11.c_str(),argv[1])==0){
          chdir("/home");
        }
        else{
          string str2=argv[1];
          chdir(argv[1]);
        }

      }
      string str100="$$";
      string str101="$?";
      if(strcmp(str100.c_str(),argv[0])==0 ){
        perror("prev");
      }
    else{


    char *d=(char *)calloc(str1.length() + 1, sizeof(char));;
    strcpy(d,str1.c_str());
    removeDupWord_map(d);


    char *e=(char *)calloc(str1.length() + 1, sizeof(char));;
    strcpy(e,str1.c_str());



    for(auto it=str1.begin();it!=str1.end();++it){

        if(*it == '='){
          string ali="alias";
          removeDupWord_map(e);
         if(strcmp(f_ali[0],ali.c_str())==0){
         string new_name=f_ali[1];
         string functional_name=f_ali[2];
         m.insert({new_name,functional_name});
        break;
         printf("\n");
         printf(">");
          
             }
          }
      if(*it== '>'&&*(it+1)=='>'){

            int pid = fork ();
          if (pid <0) {
           printf ("fork has failed ");
            exit(1);
            }

          if (pid == 0) {

            char buffer[BUFFSIZE];
            ssize_t ret_in;

            char *p=(char *)calloc(str1.length() + 1, sizeof(char));;
            strcpy(p,str1.c_str());
            removeWord_append(p);

            int source_fd1=open(argv[0],O_RDONLY);
            //cout<<argv[0];
            int dest_fd2=open(argv[1],O_CREAT| O_WRONLY|O_APPEND);
            //cout<<argv[1];



            while((ret_in = read (source_fd1, &buffer, BUFFSIZE)) > 0){
            write (dest_fd2, &buffer, (ssize_t) ret_in);
            }

            close(source_fd1);
            close(dest_fd2);

             exit (1);
            }

             wait(NULL);
             printf("\n");
             printf(">");
           }

           if(*it== '>'&&*(it+1)!='>'){

            int pid = fork ();
          if (pid <0) {
           printf ("fork has failed ");
            exit(1);
            }

          if (pid == 0) {

            char buffer[BUFFSIZE];
            ssize_t ret_in;

            char *p=(char *)calloc(str1.length() + 1, sizeof(char));;
            strcpy(p,str1.c_str());
            removeWord_copy(p);

            int source_fd1=open(argv[0],O_RDONLY);
            //cout<<argv[0];
            int dest_fd2=open(argv[1],O_CREAT| O_WRONLY);
            //cout<<argv[1];

            dup2(source_fd1,0);

            dup2(dest_fd2,1);

            //close(source_fd1);
            //close(dest_fd2);


             exit (1);
            }

             wait(NULL);
             printf("\n");
             printf(">");
           }



    if(*it=='|'){

      char *p=(char *)calloc(str1.length() + 1, sizeof(char));
      strcpy(p,str1.c_str());
      removeDupWord_pipe(p);
      removeDupWordspace0(argv[0]);
      removeDupWordspace1(argv[1]);
      removeDupWordspace2(argv[2]);
      removeDupWordspace3(argv[3]);
      if(count_pipes-1==3){
     char **cmd[] = {a, b, c,f,NULL };
     pipeline(cmd);
     }
     if(count_pipes-1==2){
     char **cmd[] = {a, b, c,NULL};
     pipeline(cmd);}
    if(count_pipes-1==1){
    char **cmd[] = {a, b,NULL};
    pipeline(cmd);
    }
    printf("\n");
    printf(">");
  }
}

       
      if(m.find(str1)!=m.end()){

        int pid = fork ();

        if (pid == 0) {
        string str2=m[str1];
        char *p=(char *)calloc(str2.length() + 1, sizeof(char));;
        strcpy(p,str2.c_str());
        removeDupWord(p);

        execvp(argv[0],argv);
        //printf("exec failed");
        exit (1);
        }
        wait(NULL);
        printf("\n");
        printf(">");
      }

      else{
        int pid=fork();

        char *p=(char *)calloc(str1.length() + 1, sizeof(char));;
          strcpy(p,str1.c_str());
          removeDupWord(p);

          
          for(auto it=str1.begin();it!=str1.end();it++){
          if(*it=='&'){
              *it=NULL;
            char *p=(char *)calloc(str1.length() + 1, sizeof(char));;
          strcpy(p,str1.c_str());
          removeDupWord(p);

            if(pid==0){
              execvp(argv[0],argv);

            }
          }
        }

        if(pid ==0){



        execvp(argv[0],argv);
        //printf("exec failed");
        exit (1);
        }
        wait(NULL);


         printf("\n");
        printf(">");
        }



}
}

return 0;
}