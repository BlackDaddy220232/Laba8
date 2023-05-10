#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"menu.h"
#include"input.h"
#include"intcheck.h"
#include"hash.h"
#include"Windows.h"
void Menu(Hash *Table)
{
	int choice;
	Hash *buf;
	char* login,*password;
	while(true)
	{
		printf("\nMenu:\n1.Search\n2.Add\n3.Change\n4.Delete\n9.End Programm\nYour choice:");
		switch(choice=Inputcheck())
	{
		case 1:
		do
		{
			printf("Input login to find password: ");
			login=Input();
			buf=Search(Table,login);
			if(buf!=NULL)
			{
				printf("Password: %s",buf->password);
			}
			else
			{
				printf("There is no such element!\n");
			}
            printf("Press 0 to exit or ENTER\n");
			_getch();
		} while (buf==NULL&&_getch()!='0');
		break;
		case 2:
			printf("Input login and password to add: ");
			login=Input();
			password=Input();
			HandleCreate(Table,login,password);
			printf("Press 0 to exit or ENTER\n");
			_getch();
		break;
		case 3:
		do
		{
			printf("Input login to change password: ");
			login=Input();
            printf("Input password: ");
			password=Input();
			buf=Change(Table,login,password);
			if(buf==NULL)
			{
				printf("There is no such element!\n");
			}
            printf("Press 0 to exit or ENTER\n");
			_getch();
		} while (buf==NULL&&_getch()!='0');
		break;
		case 4:
        do
        {
            printf("Input login to delete element: ");
            login=Input();
            if((buf=Delete(Table,login))==NULL)
            {
                printf("There is no such element!\n");
            }
            printf("Press 0 to exit or ENTER\n");
			_getch();
        } while (buf==NULL&&_getch()!='0');
        break;
        case 9:
		exit(1);
        break;
	}
    system("cls");
	}
}