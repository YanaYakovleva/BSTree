# define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


struct BST
{
	int key;
	BST *l, *r;
};

BST* add(BST *root, int addKey)//добавление по ключу
{
	if (root == NULL)
	{
		root = (BST*)malloc(sizeof(BST));
		root->key = addKey;
		root->l = NULL;
		root->r = NULL;
    }
	else
	{
		if (addKey<root->key)
			root->l = add(root->l, addKey);
		else
			root->r = add(root->r, addKey);
	}
	return root;
}

BST* remove(BST *root, int rmvKey)//удаление по ключу
{
	if (rmvKey != root->key)//если ключ корня не равен ключу удаляемого
	{
		if (rmvKey < root->key)
		{
			root->l = remove(root->l, rmvKey);
		}
		else
		{
			root->r = remove(root->r, rmvKey);
		}
	}
	else //если ключи совпали 
	{
		if (root->l == NULL && root->r == NULL)
		{
			free(root);
			return NULL;
		}
		else if (root->l != NULL && root->r == NULL)
		{
			BST *temp = root->l;
			free(root);
			return temp;
		}
		else if (root->l == NULL && root->r != NULL)
		{
			BST *temp = root->r;
			free(root);
			return temp;
		}
		else
		{
			BST *temp = root->r;
			BST *ptemp = NULL;
			while (temp->l != NULL)//ищем 
			{
				ptemp = temp;
				temp = temp->l;
			}
			root->key = temp->key;
			if (ptemp != NULL)
			{
				ptemp->l = temp->r;
			}
			else
			{
				root->r = temp->r;
			}
			free(temp);
			return root;
		}

	}
	return root;
}

int insertInArray(BST *root,int *arr,int &i)
{
	if (root != NULL)
	{
		insertInArray(root->l,arr,i);
		arr[i] = root->key;
		i++;
		insertInArray(root->r,arr,i);
	}
	return i;
}

BST* deleteTree(BST *root)
{
	if (root != NULL)
	{
		deleteTree(root->l);
		deleteTree(root->r);
		free(root);
	}
	return NULL;
}

BST* insertFromArray(BST *root, int *arr, int n)
{
	if (n == 0)
		return root;
	else
	{
		root = add(root, arr[n / 2]);
		insertFromArray(root, arr, (n/2));
		insertFromArray(root, &arr[n/2+1],(n-(n/2)-1));
	}
	return root;
}

BST* balance(BST *root)
{
	int i = 0;
	int N=256;
	int *tempArr = (int*)malloc(N * sizeof(int));
	int n = insertInArray(root, tempArr,i);
	root = deleteTree(root);
	root = insertFromArray(root, tempArr, n);
	free(tempArr);
	return root;
	 
}

void showInDepth(BST *root, int level)
{
	if (root == NULL)
	{
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("NULL\n");
	}
	else
	{
		showInDepth(root->l, level + 1);
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("%d\n", root->key);
		showInDepth(root->r, level + 1);
	}
}

void show2(BST *root)
{
	if (root != NULL)
	{
		show2(root->l);
		printf("%d ", root->key);
		show2(root->r);
	}
}

void showInWidth(BST *root)
{
	BST *it = root;
    BST *q[50];
    int front = 0, back = 0;
	if (it == NULL)
		printf("NULL\n");
		return;
	q[front++] = it;
    while (front != back)
	{
		it = q[back++];
		printf("%d\n", it->key);

		if (it->l != NULL)
			q[front++] = it->l;
		if (it->r != NULL)
			q[front++] = it->r;
	}
}

void showMenu()
{
	printf("1. Insert\n");
	printf("2. Remove\n");
	printf("3. Show in depth\n");
	printf("4. Show in width\n");
	printf("5. Balance\n");
	printf("0. Exit\n");

}

void menu(BST *root)
{
	int click;
	do
	{
		showMenu();
		click = _getch();
		system("cls");
		switch (click)
		{
		case '1'://добавление нового узла дерева по ключу
			int index;
			printf("Enter key for insert: ");
			scanf("%d", &index);
			root = add(root, index);
			printf("Done!\n");
			break;
		case '2'://удаление узла дерева по ключу
			showInDepth(root,0);
			int index2;
			printf("Enter key for remove: ");
			scanf("%d", &index2);
			remove(root, index2);
			printf("Done!\n");
			break;
		case '3'://Вывод дерева в глубину
			showInDepth(root, 0);
			break;
		case '4'://Вывод дерева в ширину
			showInWidth(root);
			break;
		case '5'://Балансировка
			root = balance(root);
			printf("Done!\n");
			break;
		case '0'://выход
			exit(0);
		default://нажата любая другая клавиша
			printf("wrong menu number\n");
			break;
		}
		system("pause");
		system("cls");
	} while (click != 0);
}

void main()
{
	system("color F0");
	BST *tree=NULL;
	int keys[] = { 20,10,50,25,60,45,12,40,30,35,24 };
	for (int i = 0; i < 11; i++)
	{
		tree = add(tree, keys[i]);
	}
	menu(tree);
	
	
	system("pause");
}