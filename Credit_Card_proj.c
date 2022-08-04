/* In this code I have made AVL Tree to obtain data in a sorted order of card
number And for Searching purpose I have made Hashtable .*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
struct node
{
  char dob[12];
  char add[100];
  unsigned long long card_no;
  struct node* left;     //for tree's left direction
  struct node* right;   // for tree'sright direction
  int height;           //for balancing of AVL tree
  char name[80];
  char ID_NO[50];
  char exp_date[12];
  char iss_date[12];
  char cvv[3];
};
typedef struct node node;
node* hash_table[4250]; //load density of the hash table is 0.470
int size=0;          // as total data set size is 2000 and hashtabe size is 4250   
int max(int a,int b)
{
    if(a>=b)
      return a;
    else
      return b;
}
int height(node* root)
{
   if(root==NULL)
      return 0;
   return root->height; 
}
node* rightRotate(node*y)
{
    node*x=y->left;
    node*T2=x->right;
    x->right=y;
    y->left=T2;
    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;
   return x;
}
node* leftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;
    y->left=x;
    x->right=T2;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}
int do_balance(node*root)
{
    if(root==NULL)
       return 0;
    return height(root->left)-height(root->right);
}
node*insert(node*root,node*block)
{
  if(root==NULL)
    return block;
  if(root->card_no > block->card_no)
    root->left=insert(root->left,block);
  else if(root->card_no < block->card_no)
    root->right=insert(root->right,block);
  else 
    return root;
  
  root->height=1+max(height(root->left),height(root->right));
  int balance = do_balance(root);
  if(balance >1 && block->card_no < root->left->card_no)
      return rightRotate(root);
  if(balance <-1 && block->card_no > root->right->card_no)
      return leftRotate(root);
  if(balance > 1 && block->card_no > root->left->card_no)
    {
        root->left=leftRotate(root->left);
       return rightRotate(root); 
    }
  if(balance < -1 && block->card_no < root->right->card_no)
    {
       root->right=rightRotate(root->right);
       return leftRotate(root);
    }
    return root;
}
int k=1;
void display(node*root)
{
   if(root!=NULL)
   {
      display(root->left);
      printf("------Details of cutstomer %d-------\n",k);
      printf("card no=%llu\n",root->card_no);
      printf("Name=%s\n",root->name);
      printf("adress=%s\n",root->add);
      printf("date of birth=%s\n",root->dob);
      printf("Identity number=%s\n",root->ID_NO);
      printf("Card issue date=%s\n",root->iss_date);
      printf("Card expiry date=%s\n",root->exp_date);
      printf("CVV=%s\n",root->cvv);
      k++;
      display(root->right);
   }
}
node* allocate()
{
    node* add=malloc(sizeof(node));
    return add;
}
int hash_code(unsigned long long card_no)
{

   return card_no % 4250;
}
void insert_hash(unsigned long long card_no,node*block)
{
    if(size==4250)
    {
       printf("hash size full");
       exit(1);
    }
    else
    {
       int i=hash_code(card_no);
       while(hash_table[i]!=NULL)
       {
            i=(i+1)%4250;
       }
       hash_table[i]=block;
    }
}
void search(unsigned long long card_no)
{
    int h=hash_code(card_no);
     int i=h;
    while(hash_table[i]!=NULL)
    {
       if(hash_table[i]->card_no==card_no)
       {
            printf("\n");
            printf("details found!!\n");
            printf("--------------------------------------\n");
            printf("card no=%llu\n",hash_table[i]->card_no);
            printf("Name=%s\n",hash_table[i]->name);
            printf("adress=%s\n",hash_table[i]->add);
            printf("date of birth=%s\n",hash_table[i]->dob);
            printf("Identity number=%s\n",hash_table[i]->ID_NO);
            printf("Card issue date=%s\n",hash_table[i]->iss_date);
            printf("Card expiry date=%s\n",hash_table[i]->exp_date);
            printf("CVV=%s\n",hash_table[i]->cvv);  
            return;
       }
       i=(i+1)%4250;
       if(i==h)
       {
           printf("No record found\n");
           return;
       }
    }
  printf("No record found\n");
}
int main(int argc,char *argv[])
{
  char buff[256];
  char temp[150];
  ssize_t readbytes;
  int fd1,i,j=0,pos=0,idx=0;
  node*root=NULL;

  for(int i=0;i<4250;i++)
     hash_table[i]=NULL;

  if((fd1=open("manish_dataset.txt",O_CREAT | O_RDONLY, S_IRWXU)) < 0)
  {
           fprintf(stderr,"Error in File Opening!!\n");
           exit(1);
  }
  node*block;
  while((readbytes=read(fd1,buff,sizeof(buff)))>0)
  {

        for(i=0;i<readbytes;i++)
        {
          if(pos==0 && buff[i]==' ')
          {
             continue;
          } 
          else if(buff[i]==58 || buff[i]=='\n')
           { 	
                if(pos==0)
           	 {
              	      block=allocate();
                      block->left=NULL;
                      block->right=NULL;
                      block->height=0;
                      strcpy(block->name,temp);
                      memset(temp,0,sizeof(temp));
                      pos++;
                      j=0; 
                 }
                 else if(pos==1)
                 {
                      strcpy(block->dob,temp);
                      memset(temp,0,sizeof(temp));
                      pos++;
                      j=0;
                 }
                 else if(pos==2)
                 {
                      strcpy(block->add,temp);
                      memset(temp,0,sizeof(temp));
                      pos++;
                      j=0;
                 }
                 else if(pos==3)
                 {
                      block->card_no=atoll(temp);
                      memset(temp,0,sizeof(temp));
                      pos++;
                      j=0;
                 }
                 else if(pos==4)
                 {
                      strcpy(block->iss_date,temp);
                      memset(temp,0,sizeof(temp));
                      pos++;
                      j=0;
                 }
                 else if(pos==5)
                 {
                      strcpy(block->exp_date,temp);
                      memset(temp,0,sizeof(temp));
                      pos++;
                      j=0;
                 }
                 else if(pos==6)
                 {
                      strcpy(block->ID_NO,temp);
                      memset(temp,0,sizeof(temp));
                      pos++;
                      j=0;
                 }
                 else if(pos==7)
                 {
                      strcpy(block->cvv,temp);
                      memset(temp,0,sizeof(temp));
                      pos=0;
                      j=0;
                      root=insert(root,block);
                      insert_hash(block->card_no,block);
                 }
            }
        else
         {
            temp[j]=buff[i];
            j++;
         }
                
      }
    memset(buff,0,sizeof(buff)); 
  }
   int ch=1;
   unsigned long long res;
   int choice;
 
      printf("Enter 1: to print details of all the customer in sorted order of card number\n");
      scanf("%d",&choice);
      if(choice==1)
      display(root);      
      printf("Enter 2: to search the record of any customer by providing cardnumber\n");
      scanf("%d",&choice);    
      if(choice==2)
      {
       abv: printf("Enter card number whose details you want\n");
            scanf("%llu",&res);
            search(res);
            printf("If Want to search more card numbers press 0 or press any other key to exit\n");
            scanf("%d",&ch);
            if(ch==0)
            goto abv;
      }
   return 0;
}

