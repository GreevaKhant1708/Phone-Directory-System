#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int flag1,flag2,flag3,flag4,flag5;
struct contact
{
    char firstname[50];
    char lastname[50];
    char number[11];
    char email[50];
    struct contact *prev;
    struct contact *next;
};
struct contact *insert(char label1[],char label2[],char n[],char e[],struct contact *root)
{
    if(root==NULL)
    {
        struct contact *t=(struct contact *)malloc(sizeof(struct contact));
        strcpy(t->firstname,label1);
        strcpy(t->lastname,label2);
        strcpy(t->number,n);
        strcpy(t->email,e);
        t->prev=NULL;
        t->next=NULL;
        return t;
    }
    else if(strcmpi(label1,root->firstname)<0)
    {
        root->prev=insert(label1,label2,n,e,root->prev);
    }
    else if(strcmpi(label1,root->firstname)>0)
    {
        root->next=insert(label1,label2,n,e,root->next);
    }
    else
    {
        if(strcmpi(label2,root->lastname)<0)
        {
            root->prev=insert(label1,label2,n,e,root->prev);
        }
        else if(strcmpi(label2,root->lastname)>0)
        {
            root->next=insert(label1,label2,n,e,root->next);
        }
    }
    return root;
}
void display(struct contact *root)
{
    if(root!=NULL)
    {
        flag2=0;
        display(root->prev);
        printf("\n--------------------------------------------");
        printf("\nName: %s %s\nContact Number : %s\nContact Email : %s",root->firstname,root->lastname,root->number,root->email);
        printf("\n--------------------------------------------\n");
        display(root->next);
    }
}
struct contact *delete_node(char label1[],char label2[],struct contact *root)
{
    if(root==NULL)
    {
        return root;
    }
    if(strcmpi(label1,root->firstname)<0)
    {
        root->prev=delete_node(label1,label2,root->prev);
    }
    else if(strcmpi(label1,root->firstname)>0)
    {
        root->next=delete_node(label1,label2,root->next);
    }
    else
    {
        if(strcmpi(label2,root->lastname)<0)
        {
            root->prev=delete_node(label1,label2,root->prev);
        }
        else if(strcmpi(label2,root->lastname)>0)
        {
            root->next=delete_node(label1,label2,root->next);
        }
        else
        {
            flag1=0;
            if(root->prev==NULL)
            {
                struct contact *temp=root->next;
                free(root);
                return temp;
            }
            else if(root->next==NULL)
            {
                struct contact *temp=root->prev;
                free(root);
                return temp;
            }
            struct contact *temp=root->prev;
            while(temp&&temp->next!=NULL)
            {
                temp=temp->next;
            }
            strcpy(root->firstname,temp->firstname);
            strcpy(root->lastname,temp->lastname);
            root->prev=delete_node(temp->firstname,root->lastname,root->prev);
        }
    }
    return root;
}
struct contact *search(char label1[],char label2[],struct contact *root)
{
    if(root!=NULL)
    {
        if(strcmpi(label1,root->firstname)<0)
        {
            root->prev=search(label1,label2,root->prev);
        }
        else if(strcmpi(label1,root->firstname)>0)
        {
            root->next=search(label1,label2,root->next);
        }
        else
        {
            if(strcmpi(label2,root->lastname)<0)
            {
                root->prev=search(label1,label2,root->prev);
            }
            else if(strcmpi(label2,root->lastname)>0)
            {
                root->next=search(label1,label2,root->next);
            }
            else
            {
                flag3=0;
                printf("\n--------------------------------------------");
                printf("\nName: %s %s\nContact Number : %s\nContact Email : %s",root->firstname,root->lastname,root->number,root->email);
                printf("\n--------------------------------------------\n");
            }
        }
    }
    return root;
}
void find(char label1[],int len,struct contact *root)
{
        if(root!=NULL)
        {
            find(label1,len,root->prev);
            char title[100],check[len];
            flag5=-1;
            int i,j;
            strcpy(title,root->firstname);
            strcat(title," ");
            strcat(title,root->lastname);
            for(i=0;i<=(strlen(title)-len);i++)
            {
                for(j=0;j<len;j++)
                {
                    check[j]=title[i+j];
                }
                if(strcmpi(check,label1)==0)
                {
                    flag4=0;
                    if(flag5==-1)
                    {
                        printf("\n--------------------------------------------");
                        printf("\nName: %s %s\nContact Number : %s\nContact Email : %s",root->firstname,root->lastname,root->number,root->email);
                        printf("\n--------------------------------------------\n");
                    }
                    flag5=0;
                }
            }
            find(label1,len,root->next);
        }
}
void main()
{
    struct contact *root=NULL;
    int ch;
    char firstname[50],lastname[50],number[11],email[50],s[20];
    int len;
    printf("---------------------WELCOME TO CONTACT MANAGEMENT SYSTEM--------------------\n");
    printf("\n\n-------------------------------------MENU------------------------------------\n");
    printf("1> Add Contact\n2> Delete Contact\n3> Display all contacts\n4> Search contact\n5> Search by string\n6> Exit\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("\nEnter your choice : ");
    scanf("%d",&ch);
    while(ch!=6)
    {
        switch(ch)
        {
            case 1 :system("cls");
                    printf("\nEnter the contact name : ");
                    scanf("%s %s",firstname,lastname);
                    printf("\nEnter the contact number : ");
                    scanf("%s",number);
                    printf("\nEnter the contact email : ");
                    scanf("%s",email);
                    root=insert(firstname,lastname,number,email,root);
                    printf("\nContact has been added\n");
                    break;
            case 2 :flag1=-1;
                    system("cls");
                    printf("\nEnter the contact name to be deleted : ");
                    scanf("%s %s",firstname,lastname);
                    root=delete_node(firstname,lastname,root);
                    if(flag1==0)
                    {
                        printf("\nThe contact has been removed \n");
                    }
                    else
                    {
                        printf("\nContact not found \n");
                    }
                    break;
            case 3 :flag2=-1;
                    system("cls");
                    display(root);
                    if(flag2!=0)
                    {
                        printf("\nEmpty.....no contacts present \n");
                    }
                    break;
            case 4 :flag3=-1;
                    system("cls");
                    printf("\nEnter the contact to be searched : ");
                    scanf("%s %s",firstname,lastname);
                    search(firstname,lastname,root);
                    if(flag3!=0)
                    {
                        printf("\nContact not found \n");
                    }
                    break;
            case 5 :flag4=-1;
                    system("cls");
                    printf("\nEnter the string : ");
                    scanf("%s",s);
                    len=strlen(s);
                    find(s,len,root);
                    if(flag4!=0)
                    {
                        printf("\nNo contact with input string found \n");
                    }
                    break;
        }
    printf("\n-------------------------------------MENU------------------------------------\n");
    printf("1> Add Contact\n2> Delete Contact\n3> Display all contacts\n4> Search contact\n5> Search by string\n6> Exit\n");
    printf("------------------------------------------------------------------------------\n");
    printf("\nEnter your choice : ");
    scanf("%d",&ch);
    }
}
