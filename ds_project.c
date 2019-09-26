#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <limits.h>
#define stack_size 1000
#define B(x) S_to_binary_(#x)

struct node
{
  char data;
  int freq;
  struct node *next;
  struct node *left;
  struct node *right;
};

void create_binfile();
int height(struct node **);
char *readFile(char *fileName);
void writeFile(char *fileName,int arrcode[],int t);
void insert(struct node** ,char );  // Inserts a node at the end of a linked list
void display(struct node *);    // Displays the nodes in a linked list
void delete_node(struct node ** ,char);    // Deletes a node with a particular character value
void search(struct node ** ,char );     //Searches for a character in the linked list
void del(struct node**);   // Deletes the nodes with 0 frequency
void sort(struct node **);  // Sorts the linked list as per the frequencies in ascending order
struct node* createTree(struct node** , struct node** ); //Creates trees
//struct node* huffman_tree()
struct node* delete_first(struct node **);    //Deletes the node at the beginning of a linked list
void push(struct node* stack[],int* ,int ,struct node**);   //Push operation on a stack
struct node* pop(struct node * stack[],int *);    //Pop operation on a stack
struct node* peek(struct node* stack[] ,int *);   //Returns the top most element in the stack
int bit_length(struct node **);   //Returns the size of the input string in bits
int power(int ,int );   // Computes x^n
int tree_len(struct node* );  // Computes the number of nodes in a tree
int findDistance(struct node *, char);   //Finds the distance of a node from root node
struct node *copy(struct node *);    //Used to make a copy of a linked list
void path(struct node* , int arrcode[],int t);   //Returns the path of a node
char* concat(const char *, const char *);   //Concatenates two strings


void main()
{

// Creating stack
struct node* stack[stack_size];
//stack=(struct node*)malloc(sizeof(struct node)*stack_size);
int top=-1;


// Creating linked list with "abcdefghijklmnopqrstuvwxyz " (27 nodes) and initializing frequency to 0
struct node* first = NULL;
char a[27] = "abcdefghijklmnopqrstuvwxyz ";
int i=0;
for(i=0;i<27;i++)
{
insert(&first,a[i]);
}
//display(first);


// Inputing a string

char s[1000] = {'\0'};
printf("Enter a string   ");
gets(s);


//extracting from the file;
/*char *s=readFile("sample.txt");
printf("%s",s);*/
// Updating frequencies of each character in the string
i = 0;
while(s[i]!='\0')
{
search(&first,s[i]);
i++;
}

//Deleting the non occuring alphabets
del(&first);

//Sorting the nodes in ascending order of their frequencies
sort(&first);

// Making a copy of the sorted linked list6
struct node * d = copy(first);

//Calculating the number of bits used to represent the input string
int freq_count = bit_length(&first);
printf("\n\n Total number of bits used to store the string = ");
printf("%d  \n\n",freq_count);  //display the number of bits used to represent the string.

display(first);




// Creating the Huffman tree

struct node* left;
struct node* right;
struct node* temp;

left = delete_first(&first);
right = delete_first(&first);
temp = createTree(&left,&right);
push(stack,&top,stack_size,&temp);

//printf("\n \n %d \n",peek(stack,&top)->freq);

//printf("\n %d \n",power(2,5));

struct node* q = first;


while(q!=NULL)
{

if(top>0)
	{
	//struct node ** arr = (struct node *)malloc(sizeof(struct node)*(top+1));
	struct node* arr[top+1];
	struct node* temp;
	i = 0;
	int dup = top;
	for(i=0;i<dup+1;i++)
		{
		arr[i] = pop(stack,&top);
		//printf("%d  ",arr[i]->freq);
		}
	//printf("\n popped \n");
	int j =0;
		struct node* tempo;
	for(j=0;j<dup;j++)
		{
			for(i=j+1;i<=dup;i++)
			{
				int min = arr[j]->freq;
				if(arr[i]->freq<min)
					{
					min = arr[i]->freq;
					tempo = arr[i];
					arr[i] = arr[j];
					arr[j] = tempo;
					}
			}
		}
	for(i = dup;i>=0;i--)
		{
		//printf("%d  ",arr[i]->freq);
		push(stack,&top,stack_size,&arr[i]);
		}
	//printf("\n pushing \n");

	if(q->freq>peek(stack,&top)->freq)
		{
			left = pop(stack,&top);

			if(q->freq>peek(stack,&top)->freq)
				{
				right = pop(stack,&top);
				temp = createTree(&left,&right);
				push(stack,&top,stack_size,&temp);
				}

			else if(q->freq==peek(stack,&top)->freq)
				{
				right = pop(stack,&top);
				temp = createTree(&left,&right);
				push(stack,&top,stack_size,&temp);
				}

			else if(q->freq<peek(stack,&top)->freq)
				{
				right = delete_first(&q);
				tempo = createTree(&left,&right);
				push(stack,&top,stack_size,&tempo);

				}

		}

	}


/*
{
left = pop(stack,&top);
right = pop(stack,&top);
if(left->freq>right->freq)
{
push(stack,&top,stack_size,&left);
push(stack,&top,stack_size,&right);
}
else
{
push(stack,&top,stack_size,&right);
push(stack,&top,stack_size,&left);

}
}
*/
	struct node *r;

	if(q->freq>=peek(stack,&top)->freq)
		{
		left = delete_first(&q);
		right = pop(stack,&top);
		temp = createTree(&left,&right);
		push(stack,&top,stack_size,&temp);
		}


	else if(q->freq<peek(stack,&top)->freq)
		{
		r = q->next;
			if(r!=NULL &&(r->freq<=peek(stack,&top)->freq))
				{
					left = delete_first(&q);
					right = delete_first(&q);
					temp = createTree(&left,&right);
					push(stack,&top,stack_size,&temp);
				}
	
			else    //just add to the existing tree
				{
					left = delete_first(&q);
					right = pop(stack,&top);
					temp = createTree(&left,&right);
					push(stack,&top,stack_size,&temp);
				}
		}

}

while(top!=0)
{
	if(top>0)
		{
			//struct node ** arr = (struct node *)malloc(sizeof(struct node)*(top+1));
			struct node* arr[top+1];
			i = 0;
			int dup = top;
			for(i=0;i<dup+1;i++)
				{
				arr[i] = pop(stack,&top);
				//printf("%d  ",arr[i]->freq);
				}
			//printf("\n");
			int j =0;
				struct node* tempo;
				for(j=0;j<dup;j++)
				{
					for(i=j+1;i<=dup;i++)
					{
						int min = arr[j]->freq;
						if(arr[i]->freq<min)
						{
						min = arr[i]->freq;
						tempo = arr[i];
						arr[i] = arr[j];
						arr[j] = tempo;
						}
					}
				}
			for(i = dup;i>=0;i--)
				{
				//printf("%d  ",arr[i]->freq);
				push(stack,&top,stack_size,&arr[i]);
				}
			//printf("\n");



		}
	left = pop(stack,&top);
	right = pop(stack,&top);
	temp = createTree(&left,&right);
	push(stack,&top,stack_size,&temp);
}

temp = pop(stack,&top);   // The root of the huffman tree
printf("\n\n\n %d \n",temp->freq);

//printf("\n\n\n %d \n",tree_len(temp));

//display(d);

int n=height(&temp);
int arrcode[n];
int t=0;

path(temp,arrcode,t);

create_binfile();


//Calculating the number of bits required to store the string using huffman encoding
int huffcount=0;

struct node* v = d;
while(v!=NULL)
{
	huffcount = huffcount+ (v->freq) * findDistance(temp,v->data);
	v= v->next;
}

printf("\n\n Total number of bits used to store the string by Huffman Coding = ");
printf("%d  \n\n",huffcount);  //display the number of bits used to represent the string using Huffman coding.


//printf("%d  \n",findDistance(temp,'y'));

//printf("%s \n",path(temp,'a'));






}    // end of main





void insert(struct node** p,char c)
{
struct node* temp = malloc(sizeof(struct node));
temp->data = c;
temp->freq = 0;
temp->next = NULL;
temp->left = NULL;
temp->right = NULL;

if (*p==NULL)  // First Node creation
*p = temp;

else
{
struct node * q = *p;
while(q->next!=NULL)
{
q = q->next;
}
q->next = temp;
}
}


void display(struct node *p)
{
struct node *q = p;
while(q->next!=NULL)
{
printf(" '%c'-> %d ", q->data,q->freq);
q = q->next;
}
printf(" '%c'->%d ",q->data,q->freq);
printf("\n \n \n");
}


void delete_node(struct node ** p,char x)
{
if(*p==NULL)
return;
else
	{
		struct node *q,*prev;
		prev =NULL;
		q = *p;
		while((q!=NULL)&&(q->data!=x))
		{
			prev = q;
			q = q->next;
		}
		if((q==NULL) && (prev!=NULL))
		{
			printf("\nNode not found \n");
		}
		else if(prev==NULL)
		{
			*p = q->next;
			free(q);
		}
		else if((q->next!=NULL)&&(q->data==x))
		{
			prev->next = q->next;
			free(q);
		}
		else if (q->data==x)
		{
			prev->next = NULL;
			free(q);
		}

	}
}

void search(struct node ** p,char x)
{
if(*p==NULL)
return;
else
	{
		struct node *q,*prev;
		prev =NULL;
		q = *p;
		while((q!=NULL)&&(q->data!=x))
		{
			prev = q;
			q = q->next;
		}
		if((q==NULL) && (prev!=NULL))
		{
			//printf("\nNode not found \n");
			return;
		}
		else if(prev==NULL)
		{
			q->freq++;
			
		}
		else if((q->next!=NULL)&&(q->data==x))
		{
			q->freq++;
		}
		else if (q->data==x)
		{
			q->freq++;
		}

	}
}


void del(struct node**p)
{
struct node* q = *p;
while(q!=NULL)
{
if(q->freq==0)
delete_node(p,q->data);
q = q->next;
}
}


void sort(struct node **p)
{
struct node*q,*r;
q = *p;
char tempc;
int tempfreq;
while(q->next!=NULL)
	{
		r = q->next;
		while(r!=NULL)
		{
			if(r->freq < q->freq)
			{
				tempc = q->data;
				q->data = r->data;
				r->data = tempc;

				tempfreq = q->freq;
				q->freq = r->freq;
				r->freq = tempfreq;
			}
		r = r->next;
		}
	q = q->next;
	}
}


struct node* createTree(struct node** left , struct node** right)
{
struct node* temp = (struct node* )malloc(sizeof(struct node));
temp->data = '*';
temp->freq = (*right)->freq + (*left)->freq;
temp->left = *left;
temp->right = *right;
return temp;
}


struct node* delete_first(struct node **p)
{
if (*p==NULL)
return NULL;
else
	{
		struct node* q = *p;
		*p = (*p)->next;
		return q;
	}
}

void push(struct node* stack[],int* t,int size,struct node** x)
  {
    //check for overflow
    if(*t==size-1)
     {
       printf("\nStack overflow\n");
       return ;
     }

    ++*t;
   stack[*t]=*x;
   //return(1);
  }


struct node* pop(struct node *stack[],int *t)
  {
   struct node* x;
   //check for underflow
   if(*t==-1)
   {
     printf("stack Underflow..\n");
     //return(-1);
   }
   x=stack[*t];
   --*t;
   return x;
  }




struct node* peek(struct node* stack[], int *t)
{
return stack[*t];
}

int power(int x,int n)
{
int i = 1;
int product =1;
while(i<=n)
{
i++;
product = product * x;

}
return product;
}

int height(struct node **p)

{
	struct node* q = *p;
int count = 0;
while(q!=NULL)
{
count++;
q = q->next;
}
int n=0;
while(count>power(2,n))
n++;
return n;
}

int bit_length(struct node **p)
{
struct node* q = *p;
int count = 0;
while(q!=NULL)
{
count++;
q = q->next;
}
int n=0;
while(count>power(2,n))
n++;
//printf("%d",n);
int freq_count=0;
q = *p;
while(q!=NULL)
{
freq_count = freq_count + n*q->freq;
//freq_count = freq_count + sizeof(char)*q->freq;
q = q->next;
}
return freq_count;

}

int tree_len(struct node* temp)
{
if(temp->left==NULL && temp->right==NULL)
{
return 0;
}
int left = 1+tree_len(temp->left);
int right = 1+tree_len(temp->right);
int result = left+right;
return result;
}




int findDistance(struct node *root, char x)
{
    // Base case
    if (root == NULL)
      return -1;
 
    // Initialize distance
    int dist = -1;
 
    // Check if x is present at root or in left
    // subtree or right subtree.
    if ((root->data == x) ||
        (dist = findDistance(root->left, x)) >= 0 ||
        (dist = findDistance(root->right, x)) >= 0)
        return dist + 1;
 
    return dist;
}

struct node *copy(struct node *start1)
{
    if(start1==NULL) return NULL;
    struct node *temp=(struct node *) malloc(sizeof(struct node));
    temp->data=start1->data;
    temp->freq = start1->freq;
    temp->left = start1->left;
    temp->right = start1->right;
    temp->next=copy(start1->next);
    return temp;
}


void path(struct node* root , int arrcode[],int t)
{

static char paths[1000];
static int count = 0;

if(root != NULL)
{
if(root->left)
	{
		arrcode[t]=0;
		path(root->left,arrcode,t+1);
	}

if(root->right)
	{
		arrcode[t]=1;
		path(root->right,arrcode,t+1);
	}

if(root->left==NULL && root->right==NULL)
	{
		printf("%c: ", root->data);
		int i;
		FILE *file = fopen("coded_string.txt", "wb");
		if (file == NULL)
        		return; //could not open file
		
		for(i=0;i<t;i++)
		{
			 //fprintf(file,"%d",arrcode[i]);
			printf("%d",arrcode[i]);
			

		}

		int j =0;
		for(j = 0; j<root->freq ; j++)
		{
			for(i=0;i<t;i++)
		{
			//fprintf(file,"%c",arrcode[i]);
			//fwrite(&arrcode[i], 1, 1, file);
			//printf("%d",arrcode[i]);
			paths[count] = arrcode[i];
			count++;
		}
		}
		
		printf("\n");	
	//fprintf(file,"%d",paths);




int k=0;

for(k=0;k<count;k++)
	{
		
		fprintf(file,"%d",paths[k]);
	}
fclose(file);
	}
	
}
}
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the null-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


//aaaaaaaaaa eeeeeeeeeeeeeeeiiiiiiiiiiiisssttttppppppppppppp


//this will never happen again in my entire life


char *readFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL; //could not open file

    code = malloc(1000);

    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
    }

    // don't forget to terminate with the null character
    code[n] = '\0';        

    return code;
}

/*void writeFile(char *fileName,int arrcode[],int t)
{
    
    
    if (file == NULL)
        return; //could not open file
	int i;
	for(i=0;i<t;i++)
	{
	
	     fprintf(file,"%d",arrcode[i]);
	}
}
*/

static inline unsigned long long S_to_binary_(const char *s)
{
    unsigned long long i = 0;
    while (*s) {
        i <<= 1;
        i += *s++ - '0';
    }
    return i;
}


void create_binfile()
{
FILE* file = fopen("sample1.txt","r");
int deci[1000];
memset(deci,'\0',sizeof(deci));
int i=0;
while(!feof(file))
{
deci[i] = (int)getc(file)-48;

//printf("%d",deci[i]);
i++;
}
printf("\n");
i--;
deci[i] = 0;
/*
int k;
for(k=0;k<i;k++)
{
printf("%d",deci[k]);
}
*/
if(i%8!=0)
{
while(i%8!=0)
{
deci[i] = 0;
	i++;
}}

int k;
for(k=0;k<i;k++)
{
printf("%d",deci[k]);
}

printf("\n");


int arr[1000];
int index=0;
int clear =0;
for(k=0;k<i;)
{
	int  num, binary_val, decimal_val = 0, base = 1, rem;	
	clear = 1;
	decimal_val = 0;
    while (clear<=8)

    {

        rem = deci[k];
		//printf("%d",rem);
        decimal_val = decimal_val + rem * base;

        base = base * 2;
		clear ++;
		k++;

    }
	arr[index]= decimal_val;
	index++;
}
for(k=0;k<index;k++)
{
printf("%d  ",arr[k]);
}

printf("\n");
fclose(file);

FILE* fp = fopen("output.bin","wb");
for(k=0;k<index;k++)
{
fprintf(fp , "%d" , arr[k]%10);
}

}




