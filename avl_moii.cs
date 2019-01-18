#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <stdio.h> 

using namespace std;
int level = 0;

struct Node //Звено дерева 
{
	int x; //То, что записываем в дерево 
	Node *l, *r; //Это указатели на новые звенья 
	bool red;
};
//функия для нахождение высоты дерева
int Node_Height(Node* Tree) {
	int l, r, h = 0;
	if (Tree != NULL) {
		l = Node_Height(Tree->l);
		r = Node_Height(Tree->r);
		h = ((l > r) ? l : r) + 1;
	}
	return h;
}

//функция для нахождения количества потомков дерева
//int Node_Child(Node* Tree) {
//	int l, r, h = 0;
//	if (Tree != NULL) {
//		l = Node_Child(Tree->l);//рекрсивная функция для нахождения количества потомков дерева
//		r = Node_Child(Tree->r);
//		h = r + l + 1;
//	}
//	return h;
//}
void show(Node *&Tree) //Функция вывода дерева на экран
{

	if (Tree != NULL) //Пока не встретится пустое звено 
	{
		level++;
		show(Tree->l); //Рекурсивная функция для вывода левого поддерева 

		for (int i = 0; i<level; i++)
			cout << " ";
		cout << " " << Tree->x << endl; //Отображаем корень дерева 

		show(Tree->r); //Рекурсивная функци для вывода правого поддерева 
		level--;
	}

}


void add_node(int x, Node *&MyTree) //Фукция добавления звена в дерево 
{
	if (NULL == MyTree) 
	{
		MyTree = new Node; //Выделяем память под звено дерева 
		MyTree->x = x; //Записываем данные в звено 
		MyTree->l = MyTree->r = NULL; //Подзвенья инициализируем пустотой во избежание ошибок 
		return;
	}

	if (x<MyTree->x) //Если нововведенный элемент x меньше чем элемент x из семечка дерева, уходим влево 
	{
		if (MyTree->l != NULL) add_node(x, MyTree->l); //При помощи рекурсии заталкиваем элемент на свободный участок 
		else //Если элемент получил свой участок, то 
		{
			MyTree->l = new Node; //Выделяем память левому подзвену.
			MyTree->l->l = MyTree->l->r = NULL; //У левого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой 
			MyTree->l->x = x; //Записываем в левое подзвено записываемый элемент 
		}
	}

	if (x >= MyTree->x) //Если нововведенный элемент x больше чем элемент x из семечка дерева, уходим вправо 
	{
		if (MyTree->r != NULL) add_node(x, MyTree->r); //При помощи рекурсии заталкиваем элемент на свободный участок 
		else //Если элемент получил свой участок, то 
		{
			MyTree->r = new Node; //Выделяем память правому подзвену.
			MyTree->r->l = MyTree->r->r = NULL; //У правого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой 
			MyTree->r->x = x; //Записываем в правое подзвено записываемый элемент 
		}
	}
}


//обратный обход,снизу-вверх(левое поддерево, правое,узел)
void equ(Node*Tree)
{
	if (Tree == NULL)
		return;
	equ(Tree->l); //функция обхода поддеревьев
	equ(Tree->r);
	if (((Tree->l)==NULL)&&((Tree->r) == NULL)) // проверка на лист(задача)
	{
		cout << Tree->x << " ";
	}

}

int main()
{
	int i;
	Node *Tree = NULL; //Создаю указатель, тип которого = звено дерева и инициализирую его пустотой 

	cout << "Введите числа: (0 - для завершения )" << endl;
	do
	{
		scanf("%d", &i);
		if (i != 0) add_node(i, Tree);
	} while (i != 0);

	cout << "Дерево:" << endl;
	show(Tree); //Вывод на экран дерева 
	cout << '\n';
	equ(Tree); //Обход дерева 
	system("pause");
}