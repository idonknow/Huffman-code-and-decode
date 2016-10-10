/***Huffman code and decode***
****function:
    1.Code
      input a string of capital letters, and output the corresponding Huffman code
    2.Decode
      input a text of o and 1 output the corresponding alphabet string
*********************************************************************************
****author: weiguoqiang****
****wgq711@mail.ustc.edu.cn****
****10/09/2016****/

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

#define N 26
#define M 2*N-1
#define Code_Size 10

int alphabet_num;    //presents the num of kinds of letters among input text

typedef struct 
{
	int parent;
	int weight;
	int lchild;
	int rchild;
}HTNode;//the node of Huffman tree

typedef struct 
{
	char alpha;
	char codes[Code_Size];
}HCNode;//the node of Huffman code 

//count the num of kinds of letters among the text[]
void Alphabet_Weight_Count(char text[], HCNode HC[], HTNode HT[])
{   
	int temp[27] = { 0 };
	int i = 0;
	int j = 1;
	alphabet_num = 0;
	for(; text[i] != '\0'; i++)
	{
		temp[(int)text[i] - 64]++;
	}
	for (i = 1; i <= 26; i++)
	{
		if (temp[i] != 0)
		{   //set the huffman tree`s node`s weight 
			HC[j].alpha = 64 + i;
			HT[j].weight = temp[i];
			j++;
		}
	}
	alphabet_num = --j;
}

//select 2 min node from the assigned huffman tree,and store in min1 & min2
void min_2(HTNode HT[], int k, int *min1, int *min2)
{   
	int min = 1000;
	int i, j;
	for (i = 1; i <= k; i++)
	{   //find the minimun node
		if (HT[i].weight < min && HT[i].parent == -1)
		{
			j = i;
			min = HT[i].weight;
		}
	}
	*min1 = j;
	min = 1000;
	for (i = 1; i <= k; i++)
	{   //find the 2nd minimun node
		if (HT[i].weight < min && i != *min1 && HT[i].parent == -1)
		{
			j = i;
			min = HT[i].weight;
		}
	}
	*min2 = j;
}

//create a huffman tree according letters with different weight
void HuffmanTree(HTNode HT[], HCNode HC[])
{   
	int *min1, *min2;
	min1 = (int*)malloc(sizeof(int));
	min2 = (int*)malloc(sizeof(int));
	for (int i = 1; i <= 2*alphabet_num - 1; i++)
	{  //initilize the huffman tree
		HT[i].lchild = -1;
		HT[i].parent = -1;
		HT[i].rchild = -1;
		if (i > alphabet_num)
			HT[i].weight = 0;
	}
	for (int i = alphabet_num + 1; i <= 2 * alphabet_num - 1; i++)
	{   
		min_2(HT, i - 1, min1, min2);
		HT[*min1].parent = i;
		HT[*min2].parent = i;
		HT[i].lchild = *min1;
		HT[i].rchild = *min2;
		HT[i].weight = HT[*min1].weight + HT[*min2].weight;
	}
}

//calculate the huffman code of text[] according to the created huffman tree 
void HuffmanCode(HTNode HT[], HCNode HC[], char text[])
{
	int node, p;
	int start = Code_Size - 1;
	printf("each alphabet`s huffman code symbol is :\n");
	for (int i = 1; i <= alphabet_num; i++)
	{   //find the huffman code of each alphabet from the leaf to root 
		char temp[Code_Size] = {'0'};
		node = i;
		while ((p = HT[node].parent) > 0)
		{
			temp[--start] = (HT[p].lchild == node) ? '0' : '1';
			node = p;
 		}
		strcpy(HC[i].codes, &temp[start]);
		printf("the huffman code of %c is : %s\n", HC[i].alpha, HC[i].codes);
	}
}

//print the huffman code of input text
void print_code(HCNode HC[], char text[])
{
	int i = 0;
	printf("the huffman codes of the text is \n");
	while (text[i] != '\0')
	{
		printf("%s", HC[(int)text[i] - 64].codes);
		i++;
	}
	printf("\n");
}

//decode the text containing 0 and 1 according to huffman code HC
void Decode(HCNode HC[], char text[])
{
	char temp[Code_Size], string[Code_Size];
	int i, k, j, t, flag;
	i = 0;
	k = 0;
	t = 0;
	printf("the alphabet of the codes is :\n");
	while (text[t] != '\0')
	{
		flag = 0;
		for (i = 0; text[t] != '\0' && flag != 1; i++, t++)
		{
			temp[i] = text[t];
			temp[i + 1] = '\0';
			for (j = 1; j <= alphabet_num; j++)
			{
				if (!strcmp(temp, HC[j].codes))
				{   //find the corresponding code
					string[k++] = HC[j].alpha;
					flag = 1;
					break;
				}
			}
		}
	}
	string[k] = '\0';
	printf("%s\n", string);
}

int main()
{
	HTNode HT[N + 1];
	HCNode HC[2*N + 1];
	char c;
	char alpha_text[100];
	char code_text[100];
	printf("please input a text:\n");
	gets_s(alpha_text);
	Alphabet_Weight_Count(alpha_text, HC, HT);
	printf("the kinds of alphabet is :	%d\n", alphabet_num);
	HuffmanTree(HT, HC);
	HuffmanCode(HT, HC, alpha_text);
	print_code(HC, alpha_text);
	printf("\n\ninput the codes needed to be decoded :\n");
	gets_s(code_text);
	Decode(HC, code_text);
	return 0;
}
