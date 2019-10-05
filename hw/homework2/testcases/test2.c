#include"doubll.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

bool less(const void* a, const void* b)
{
	return (*((int*)a)) < (*((int*)b));
}

void print_list(doubll* list)
{
	doubll_item* a=list_begin(list), *b=list_end(list);
	printf("====%ld:====\n", list_size(list));
	for(; a!=b; a=a->next)
	{
		printf("%d ", *((int*)(a->data)));
	}
	printf("\n");
}
void print_item(doubll_item* a)
{
	if(a == NULL)
		printf("***NULL***\n");
	else
		printf("***%d***\n", *((int*)(a->data)));
}	

int main()
{
	doubll list;
	doubll_item* items[22];
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	list_init(&list);
	/*print_item(list_begin(&list));
	print_item(list_head(&list));*/
	printf("items = %d\n",(int)list_size(&list));
	items[4]=(insert_list(&list, list_begin(&list), &a[4], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	/*above null*/
	items[2]=(insert_list(&list, list_head(&list), &a[2], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	/*
	print_item(list_begin(&list));
	print_item(list_head(&list));*/
	items[11]=(insert_list(&list, list_begin(&list), &a[11], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	items[1]=(insert_list(&list, list_begin(&list), &a[1], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	items[15]=(insert_list(&list, list_begin(&list), &a[15], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	print_item(insert_list(&list, list_begin(&list), &a[6], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	print_item(insert_list(&list, list_begin(&list), &a[9], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	print_item(remove_item(&list, items[1]));
	printf("items = %d\n",(int)list_size(&list));
	print_list(&list);
	sort_list(&list, less);
	print_list(&list);
	print_item(insert_list(&list, list_begin(&list), &a[10], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	print_item(insert_list(&list, list_head(&list), &a[7], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	print_item(insert_list(&list, list_begin(&list), &a[13], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	print_item(insert_list(&list, list_head(&list), &a[5], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	items[8]=(insert_list(&list, list_begin(&list), &a[8], sizeof(int)));
	printf("items = %d\n",(int)list_size(&list));
	print_list(&list);
	sort_list(&list, less);
	print_list(&list);

	print_item(remove_item(&list, items[2]));
	printf("items = %d\n",(int)list_size(&list));
	print_list(&list);
	print_item(remove_item(&list, items[15]));
	printf("items = %d\n",(int)list_size(&list));
	print_list(&list);
	print_item(remove_item(&list, items[4]));/*NULL*/
	printf("items = %d\n",(int)list_size(&list));
	print_list(&list);
	print_item(remove_item(&list, items[8]));
	printf("items = %d\n",(int)list_size(&list));
	print_list(&list);
	sort_list(&list, less);
	print_list(&list);
	purge_list(&list);
	printf("items = %d\n",(int)list_size(&list));
	return 0;
}
