#include <stdio.h>
#include <stdlib.h>

#define Max_Length 100    //˳�����󳤶�
#define Increment_Length 10    //˳���洢�ռ��������
typedef int ElemType;    //ElemTypeΪ˳����Ԫ������

#define OK 0    //�ɹ�ִ��
#define Err_Memory -1    //�ڴ�������
#define Err_OverFlow -2  //���
#define Err_IllegalPos -3  //�Ƿ�����λ��

typedef struct {
	ElemType *data;    //dataָ��洢����Ԫ�ص�һά���飬��ʼ��СΪMax_Length
	int Length;    //˳����ʵ�ʳ��ȣ���ֵС�ڵ���ListLength
	int ListLength;    //��ǰ˳������Ŀռ��С����ʼֵΪMax_Length
}SeqList;

//��ʼ��˳���
int InitList(SeqList *L) {
	L->data = (ElemType*)malloc(Max_Length * sizeof(ElemType));    //�����ڴ�ռ�
	if (!L->data) {    //�����ڴ����
		printf("�ڴ�����쳣�����ܳ�ʼ��˳���\n");
		return Err_Memory;
	}
	L->Length = 0;    //˳���ʵ�ʳ�����Ϊ0
	L->ListLength = Max_Length; //��ǰ˳���洢��С��ΪMax_Length
	return OK;
}

//���˳���
int ClearList(SeqList *L) {
	L->Length = 0; //˳����ʵ�ʳ�����Ϊ0
	return OK;
}

//����˳����Ƿ�Ϊ��
bool IsEmpty(SeqList *L) {
	return (L->Length == 0);
}

//�����Ա�ĳ���
int LengthList(SeqList *L) {
	return L->Length;
}

//�������Ա�
void Traverse(SeqList *L) {
	int i = 0;
	for (i = 0; i < L->Length; i++) {
		printf("%d\t", L->data[i]);
		if ((i+1) % 10 == 0)
			printf("\n");
	}
	printf("\n");
}

//�����Ա��в���Ԫ��
int InsertList(SeqList *L,int p,ElemType e) {
	if (p<1 || p>L->Length + 1) {  //�Ϸ�����λ��Ϊ1 ~ Length+1
		printf("����λ�÷Ƿ���\n");
		return Err_IllegalPos;
	}
	if (L->Length == L->ListLength) {  //˳������������ӷ���
		ElemType *newdata=(ElemType*)realloc(L->data, (L->Length + Increment_Length) * sizeof(ElemType));
		if (!newdata) {  //�ڴ����ʧ�ܣ������ڴ�������
			printf("�ڴ�����쳣����������˳���ռ䣡\n");
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

//ɾ��Ԫ��
int DeleteList(SeqList *L,int p,ElemType *e) {
	if (L->Length == 0) {  //˳���Ϊ��
		printf("˳���Ϊ�գ�����ɾ��Ԫ�أ�\n");
		return Err_IllegalPos;
	}
	if (p<1 || p>L->Length) {  //�Ϸ�ɾ��λ��Ϊ1-Length
		printf("ɾ��λ�÷Ƿ���\n");
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

//��λԪ��
int LocateList(SeqList *L, ElemType e) {
	int i = 0;
	while (i < L->Length && L->data[i] != e) {
		i++;
	}
	if (i < L->Length)
		return i + 1;  //��λ�ɹ�
	printf("δ�ܲ��ҵ���Ԫ�أ�\n");
	return 0;  //��λʧ��
}

//��ȡָ��λ�õ�Ԫ��
int GetElem(SeqList *L,int p,ElemType *e) {
	if (p<1 || p>L->Length) {
		printf("λ�ò����Ƿ�������ȡ�ø�Ԫ�أ�\n");
		return Err_IllegalPos;
	}
	*e = L->data[p - 1];
	return OK;
}

int main() {
	SeqList *MyList = (SeqList*)malloc(sizeof(SeqList));
	//��ʼ��һ��˳���
	if (InitList(MyList)==OK) {
		printf("��ʼ��˳���ɹ���\n");
	}
	printf("˳�������Ϊ��%d\n", MyList->ListLength);
	printf("��������Ϊ��%d\n",MyList->Length);
	int i = 0;
	ElemType j = 1;
	for(i=1;i<=100;i++){
		InsertList(MyList,i,j);
		j*=2;
		if (j > 5000) {
			j=3;
		}
	}
	//�ж�˳����Ƿ�Ϊ��
	if (IsEmpty(MyList)) {
		printf("��ǰ˳���Ϊ�գ�û��Ԫ�أ�\n");
	}
	else {
		//����˳���
		Traverse(MyList);
		printf("��������Ϊ��%d\n", MyList->Length);
	}

	int pos=0;
	ElemType elem;
	ElemType* e = &elem;

	//��ָ��λ�ò�������
	printf("������Ҫ�����λ�ã�\n");
	scanf_s("%d", &pos);
	printf("������Ҫ�����Ԫ�أ�\n");
	scanf_s("%d", &elem);
	if (InsertList(MyList, pos, elem) == OK) {
		printf_s("����Ԫ�سɹ�����˳������£�\n");
		Traverse(MyList);
	}

	//ɾ��ָ��λ�õ�����
	printf("������Ҫɾ����λ�ã�\n");
	scanf_s("%d",&pos);
	if (DeleteList(MyList, pos, e) == OK) {
		printf("ɾ��Ԫ��%d�ɹ�����˳������£�\n", *e);
		Traverse(MyList);
	}

	//��λĳԪ��
	printf("��������Ҫ���ҵ�Ԫ�أ�\n");
	scanf_s("%d",&elem);
	pos = LocateList(MyList,elem);
	if (pos > 0) {
		printf("��Ԫ���ǵ�%d��Ԫ�أ�\n",pos);
	}

	//��ȡָ��λ�õ�Ԫ��
	printf("������Ҫȡ����λ�ã�");
	scanf_s("%d",&pos);
	if (GetElem(MyList, pos, e) == OK) {
		printf("��%d��Ԫ���ǣ�%d\n",pos,*e);
	}
	system("pause");
	return 0;
}