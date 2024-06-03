/*
해싱과 연결리스트를 사용하용하여 구현한다.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct node
{
	char name[30];
	char phone[20];
	char memo[50];
	struct node * link;
}Link_node;

Link_node *arr[25];//각 배열의 번호는 name의 첫번째 글자에 해당하고 24번째 index는 name이 공백인 경우다.

void enter_name(Link_node*p)//공백 포함 이름을 입력받음
{
	char c;
	int i=0;
	while((c=getchar())!='\n')
		p->name[i++]=c;
	p->name[i]='\0';
}
void enter_phone(Link_node *p)//공백 포함 번호를 입력받음
{
	char c;
	int i=0;
	while((c=getchar())!='\n')
		p->phone[i++]=c;
	p->phone[i]='\0';
}
void enter_memo(Link_node*p)//공백 포함 메모를 입력받음
{
	char c;
	int i=0;
	while((c=getchar())!='\n')
		p->memo[i++]=c;
	p->memo[i]='\0';
}


void create_node(Link_node*p)
{
	p->link=NULL;
}

void insertion(Link_node*p)
{
	int n;
	Link_node*q;

	if(p->name[0]=='\0')
	{
		q=arr[24];//q라는 구조체 포인터 변수에 arr[24]가 가리키는 노드를 저장
		arr[24]=p;/*이제 arr[24]가 p를 가리키도록 함*/
		p->link=q;/*p가 처음에 arr[24]가 가리키던 노드를 가리킴*/		
	}
	else if((p->name[0]-'a')<0)/*name의 첫글자가 대문자인 경우*/
	{
		int first=p->name[0]-'A';

		q=arr[first];
		arr[first]=p;
		p->link=q;
	}
	else
	{
		int first=p->name[0]-'a';
		q=arr[first];
		arr[first]=p;
		p->link=q;
	}
}

Link_node* search(Link_node* p) 
{
	if (p->name[0] == '\0') 
	{
		Link_node* point_node = arr[24];
		printf("You didn't enter a name.\n");
		printf("Please enter the phone number of the person you want to find.\n");
		enter_phone(p);

		while (point_node != NULL) 
		{
			if (!strcmp(p->phone, point_node->phone)) 
			{  // 찾는 전화번호가 전화번호부에 있는 경우
				return point_node;
			}
			point_node = point_node->link;
		}
		printf("Sorry, this phone book doesn't have the phone number you want to find.\n");
		return NULL;
	}
	else 
	{
		int first = (p->name[0] - 'a') < 0 ? p->name[0] - 'A' : p->name[0] - 'a';
		Link_node* point_node = arr[first];

		while (point_node != NULL) 
		{
			if (!strcmp(p->name, point_node->name))
		       	{  // 찾는 이름이 전화번호부에 있는 경우
				return point_node;
			}
			point_node = point_node->link;
		}
		printf("Sorry, this phone book doesn't have the name you want to find.\n");
		return NULL;
	}
}

void add_phone_number(void)
{
	Link_node * new_node=(Link_node*)malloc(sizeof(Link_node));
	create_node(new_node);
	printf("To enter someone name and then press enter key\n");
	enter_name(new_node);
	printf("To enter someone phone number and then press enter key\n");
	enter_phone(new_node);
	printf("To enter memo and then press enter key\n");
	enter_memo(new_node);
	insertion(new_node);//새로운 노드를 list에 집어 넣는다.	
}

void delete(Link_node*p)
{
	p=search(p);
	if(p!=0)
	{
		int en;
		printf("you want to delete this phone data?=>");
		printf("%s:%s:%s\n",p->name,p->phone,p->memo);
		printf("if you want to delete then you enter 1,if not you enter 0\n");
		scanf("%d",&en);
		if(en)
		{
			printf("delete that\n");
			free(p);
		}
	}

}

int main(void)
{

	int sel=0;//save data or search to name or phone number
	add_phone_number();
	while(1)
	{		
		do
		{		
			char k;	
			printf("if you want to save data then you enter 1\n");
			printf("if you want to search data with someone name then you enter 2\n");
			printf("if you want to delete data in phone book then you enter 3\n");
			printf("if you want to watch the phone book list then you enter 4\n");
			printf("if you want to finish this program then you enter 0\n");
			scanf("%d",&sel);
			k=getchar();//scanf로 인해 입력 버퍼에 남아있는 \n를 없애기 위해
		}while(sel!=1&&sel!=2&&sel!=3&&sel!=0&&sel!=4);//sel이 0,1,2,3,4중 하나면 반복문 종료

		if(sel==1)
		{
			add_phone_number();
		}
		else if(sel==2)
		{
			Link_node nod={0,0,0,0};
			printf("enter the name of the person you want to search\n");
			enter_name(&nod);/*nod라는 구조체 변수의 주소값을 전달하여 nod의 name에 데이터를 저장함*/
			nod.link=search(&nod);
			if(nod.link)
				printf("%s:%s:%s\n",(nod.link)->name,(nod.link)->phone,(nod.link)->memo);
	
		}
		else if (sel==3)//삭제하고 싶은 사람의 이름을 입력받고 그 사람의 이름이 있는 데이터 노드를 제거한다.
		{
			Link_node nod={0,0,0,0};
			printf("To enter the name of person who you want to delete\n");
			enter_name(&nod);
			delete(&nod);

		}
		else if (sel==4)//모든 전화번호 목록을 출력한다.
		{
			;
		}
		else if(sel==0)
			return 0;
	}
	

		
}
