#include <stdio.h>
#include <stdlib.h>

#define Max_Length 100    //顺序表最大长度
#define Increment_Length 10    //顺序表存储空间分配增量
typedef int ElemType;    //ElemType为顺序表的元素类型

#define OK 0    //成功执行
#define Err_Memory -1    //内存分配错误
#define Err_OverFlow -2  //溢出
#define Err_IllegalPos -3  //非法插入位置

typedef struct {
	ElemType *data;    //data指向存储数据元素的一维数组，初始大小为Max_Length
	int Length;    //顺序表的实际长度，其值小于等于ListLength
	int ListLength;    //当前顺序表分配的空间大小，初始值为Max_Length
}SeqList;

//初始化顺序表
int InitList(SeqList *L) {
	L->data = (ElemType*)malloc(Max_Length * sizeof(ElemType));    //分配内存空间
	if (!L->data) {    //分配内存错误
		printf("内存分配异常，不能初始化顺序表！\n");
		return Err_Memory;
	}
	L->Length = 0;    //顺序表实际长度置为0
	L->ListLength = Max_Length; //当前顺序表存储大小置为Max_Length
	return OK;
}

//清空顺序表
int ClearList(SeqList *L) {
	L->Length = 0; //顺序表的实际长度置为0
	return OK;
}

//测试顺序表是否为空
bool IsEmpty(SeqList *L) {
	return (L->Length == 0);
}

//求线性表的长度
int LengthList(SeqList *L) {
	return L->Length;
}

//遍历线性表
void Traverse(SeqList *L) {
	int i = 0;
	for (i = 0; i < L->Length; i++) {
		printf("%d\t", L->data[i]);
		if ((i+1) % 10 == 0)
			printf("\n");
	}
	printf("\n");
}

//向线性表中插入元素
int InsertList(SeqList *L,int p,ElemType e) {
	if (p<1 || p>L->Length + 1) {  //合法插入位置为1 ~ Length+1
		printf("插入位置非法！\n");
		return Err_IllegalPos;
	}
	if (L->Length == L->ListLength) {  //顺序表已满，增加分配
		ElemType *newdata=(ElemType*)realloc(L->data, (L->Length + Increment_Length) * sizeof(ElemType));
		if (!newdata) {  //内存分配失败，返回内存分配错误
			printf("内存分配异常，不能增加顺序表空间！\n");
			return Err_Memory;
		}
		L->data = newdata;
		L->ListLength += Increment_Length;
	}
	int i = 0;
	for (i = L->Length - 1; i >= p-1; i--) {
		L->data[i + 1] = L->data[i];
	}
	L->data[p - 1] = e;
	L->Length++;
	return OK;
}

//删除元素
int DeleteList(SeqList *L,int p,ElemType *e) {
	if (L->Length == 0) {  //顺序表为空
		printf("顺序表为空，不能删除元素！\n");
		return Err_IllegalPos;
	}
	if (p<1 || p>L->Length) {  //合法删除位置为1-Length
		printf("删除位置非法！\n");
		return Err_IllegalPos;
	}
	*e = L->data[p - 1];
	int i = 0;
	for (i = p; i < L->Length; i++) {
		L->data[i - 1] = L->data[i];
	}
	L->Length--;
	return OK;
}

//定位元素
int LocateList(SeqList *L, ElemType e) {
	int i = 0;
	while (i < L->Length && L->data[i] != e) {
		i++;
	}
	if (i < L->Length)
		return i + 1;  //定位成功
	printf("未能查找到该元素！\n");
	return 0;  //定位失败
}

//获取指定位置的元素
int GetElem(SeqList *L,int p,ElemType *e) {
	if (p<1 || p>L->Length) {
		printf("位置参数非法，不能取得该元素！\n");
		return Err_IllegalPos;
	}
	*e = L->data[p - 1];
	return OK;
}

int main() {
	SeqList *MyList = (SeqList*)malloc(sizeof(SeqList));
	//初始化一个顺序表
	if (InitList(MyList)==OK) {
		printf("初始化顺序表成功！\n");
	}
	printf("顺序表容量为：%d\n", MyList->ListLength);
	printf("已用容量为：%d\n",MyList->Length);
	int i = 0;
	ElemType j = 1;
	for(i=1;i<=100;i++){
		InsertList(MyList,i,j);
		j*=2;
		if (j > 5000) {
			j=3;
		}
	}
	//判断顺序表是否为空
	if (IsEmpty(MyList)) {
		printf("当前顺序表为空，没有元素！\n");
	}
	else {
		//遍历顺序表
		Traverse(MyList);
		printf("已用容量为：%d\n", MyList->Length);
	}

	int pos=0;
	ElemType elem;
	ElemType* e = &elem;

	//在指定位置插入数据
	printf("请输入要插入的位置：\n");
	scanf_s("%d", &pos);
	printf("请输入要插入的元素：\n");
	scanf_s("%d", &elem);
	if (InsertList(MyList, pos, elem) == OK) {
		printf_s("插入元素成功，新顺序表如下：\n");
		Traverse(MyList);
	}

	//删除指定位置的数据
	printf("请输入要删除的位置：\n");
	scanf_s("%d",&pos);
	if (DeleteList(MyList, pos, e) == OK) {
		printf("删除元素%d成功，新顺序表如下：\n", *e);
		Traverse(MyList);
	}

	//定位某元素
	printf("请输入您要查找的元素：\n");
	scanf_s("%d",&elem);
	pos = LocateList(MyList,elem);
	if (pos > 0) {
		printf("该元素是第%d个元素！\n",pos);
	}

	//获取指定位置的元素
	printf("请输入要取数的位置：");
	scanf_s("%d",&pos);
	if (GetElem(MyList, pos, e) == OK) {
		printf("第%d个元素是：%d\n",pos,*e);
	}
	system("pause");
	return 0;
}