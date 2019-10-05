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
		doubll* list1 = (doubll*)(malloc(sizeof(doubll)));
		doubll* list2 = (doubll*)(malloc(sizeof(doubll)));
		doubll_item *b;
		doubll_item *c;
		doubll_item *d;
		int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
		list_init(list1);
		list_init(list2);
		b = insert_list(list1, list_head(list1), &a[3], sizeof(int));
		c = insert_list(list2, list_head(list2), &a[9], sizeof(int));
		d = insert_list(list1, b, &a[7], sizeof(int));
		print_item(insert_list(list1, d, &a[4], sizeof(int)));
		print_item(insert_list(list2, c, &a[2], sizeof(int)));
		print_item(insert_list(list1, d, &a[11], sizeof(int)));
		print_item(insert_list(list2, c, &a[1], sizeof(int)));
		print_item(insert_list(list1, d, &a[5], sizeof(int)));
		print_item(insert_list(list2, d, &a[8], sizeof(int)));
		/*The above should print NULL*/

		print_list(list1);
		print_list(list2);
		sort_list(list2, less);
	print_list(list2);

	print_item(remove_item(list1, b));
	print_item(remove_item(list2, d));
	print_list(list2);

	purge_list(list1);
	purge_list(list2);
	free(list1);
	free(list2);
	return 0;
}