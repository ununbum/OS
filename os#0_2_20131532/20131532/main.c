#include "testlib.h"

int main()
{
	char  input[100];
	char *ptr[10];
	int num=0;
	struct list_elem *loc; 
	struct list *tmp;
	int i=0;
	int index;

	while(1)
	{
		num=0;
		fgets(input,100,stdin);

		input[strlen(input)-1] = '\0';

		ptr[0]=strtok(input," ");
		while(ptr[num]!=NULL)
		{
			num++;
			ptr[num]=strtok(NULL," ");
		}
		if(strcmp(ptr[0],"quit")==0)
			break;

		else if(strcmp(ptr[0],"list_insert")==0)
		{
			struct list_item *node = (struct list_item *)malloc(sizeof(struct list_item));
			loc = list_begin( find_list_arg(ptr[1]));
			node->data = atoi(ptr[3]);
			index = atoi(ptr[2]);
			i = 0;
			while(i<index)
			{
				loc = list_next(loc);
				i++;
			}
			list_insert(loc,&node->elem);
		}
		else if(strcmp(ptr[0],"list_push_front")==0)
		{
			struct list_item *node= (struct list_item *)malloc(sizeof(struct list_item));
			node->data = atoi(ptr[2]);
			list_push_front(find_list_arg(ptr[1]),&node->elem);
		}
		else if(strcmp(ptr[0],"list_push_back")==0)
		{
			struct list_item *node= (struct list_item *)malloc(sizeof(struct list_item));
			node->data = atoi(ptr[2]);
			list_push_back(find_list_arg(ptr[1]),&node->elem);
		}
		else if(strcmp(ptr[0],"list_splice")==0)
		{
			struct list_elem *target,*first,*last;
			int from,to;
			loc = list_begin(find_list_arg(ptr[1]));
			index = atoi(ptr[2]);
			target = list_begin(find_list_arg(ptr[3]));
			from =atoi(ptr[4]);
			to = atoi(ptr[5]);
			i=0;
			for(;loc!=list_end(find_list_arg(ptr[1]));loc=list_next(loc))
			{
				if(i==index)
					break;
				i++;
			}
			i=0;
			for(;target!=list_end(find_list_arg(ptr[1]));target=list_next(target))
			{
				if(i==from)
					first = target;
				if(i==to)
				{
					last = target;
					break;
				}
				i++;
			}

			list_splice(loc,first,last);	

		}
		else if (strcmp(ptr[0],"list_remove")==0)
		{
			struct list_elem * eraser;
			loc = list_begin(find_list_arg(ptr[1]));
			index = atoi(ptr[2]);
			i=0;
			for(;loc!=list_end(find_list_arg(ptr[1]));loc=list_next(loc))
			{
				if(i==index)
					break;
				i++;
			}
			eraser = loc;
			list_remove(loc);
			free(list_entry(eraser,struct list_item,elem));
		}
		else if(strcmp(ptr[0],"list_pop_front")==0)
			free(list_entry(list_pop_front(find_list_arg(ptr[1])),struct list_item,elem));
		else if(strcmp(ptr[0],"list_pop_back")==0)
			free(list_entry(list_pop_back(find_list_arg(ptr[1])),struct list_item,elem));
		else if(strcmp(ptr[0],"list_front")==0)
			printf("%d\n",list_entry(list_front(find_list_arg(ptr[1])),struct list_item,elem)->data);
		else if(strcmp(ptr[0],"list_back")==0)
			printf("%d\n",list_entry(list_back(find_list_arg(ptr[1])),struct list_item,elem)->data);
		else if(strcmp(ptr[0],"list_size")==0)
			printf("%d\n",(int)list_size(find_list_arg(ptr[1])));
		else if(strcmp(ptr[0],"list_empty")==0)
		{
			if(list_empty(find_list_arg(ptr[1])))
				printf("true\n");
			else
				printf("false\n");
		}
		else if(strcmp(ptr[0],"list_reverse")==0)
		{
			list_reverse(find_list_arg(ptr[1]));	
		}
		else if(strcmp(ptr[0],"list_sort")==0)
		{
				list_sort(find_list_arg(ptr[1]),&compare,NULL);
		}
		else if(strcmp(ptr[0],"list_insert_ordered")==0)
		{
				struct list_item *new_node=(struct list_item*)malloc(sizeof(struct list_item));
				new_node->data = atoi(ptr[2]);
				list_insert_ordered(find_list_arg(ptr[1]),&(new_node)->elem,compare,NULL);
		}
		else if(strcmp(ptr[0],"list_unique")==0)
		{
			struct list * dup=NULL;
			if(ptr[2]!=NULL)
				dup = find_list_arg(ptr[2]);
			list_unique(find_list_arg(ptr[1]),dup,compare,NULL);
		}
		else if(strcmp(ptr[0],"list_max")==0)
		{
			printf("%d\n",list_entry(list_max(find_list_arg(ptr[1]),compare,NULL),struct list_item,elem)->data);		
		}
		else if(strcmp(ptr[0],"list_min")==0)
		{
			printf("%d\n",list_entry(list_min(find_list_arg(ptr[1]),compare,NULL),struct list_item,elem)->data);	
		}
		else if(strcmp(ptr[0],"list_swap")==0)
		{
			struct list_elem *a,*b;
			int ia,ib;
			loc=list_begin(find_list_arg(ptr[1]));
			ia = atoi(ptr[2]);
			ib = atoi(ptr[3]);
			i=0;
			for(;loc!=list_end(find_list_arg(ptr[1]));loc=list_next(loc))
			{
				if(i==ia)
					a = loc;
				if(i == ib)
				{
					b = loc;
					break;
				}
				i++;
			}
			
			list_swap(a,b);
		}
		else if(strcmp(ptr[0],"list_shuffle")==0)
		{
			list_shuffle(find_list_arg(ptr[1]));
		}
		else if(strcmp(ptr[0],"bitmap_size")==0)
		{
			printf("%d\n",(int)bitmap_size(find_bit_arg(ptr[1])));	
		}
		else if(strcmp(ptr[0],"bitmap_set")==0)
		{
			bool boolian;
			if(strcmp(ptr[3],"true")==0)
					boolian = true;
			else
				boolian = false;
			bitmap_set(find_bit_arg(ptr[1]),atoi(ptr[2]),boolian);
		}
		else if(strcmp(ptr[0],"bitmap_mark")==0)
		{
				bitmap_mark(find_bit_arg(ptr[1]),atoi(ptr[2]));
		}
		else if(strcmp(ptr[0],"bitmap_reset")==0)
				bitmap_reset(find_bit_arg(ptr[1]),atoi(ptr[2]));
		else if(strcmp(ptr[0],"bitmap_flip")==0)
				bitmap_flip(find_bit_arg(ptr[1]),atoi(ptr[2]));
		else if(strcmp(ptr[0],"bitmap_test")==0)
		{
				bool res = bitmap_test(find_bit_arg(ptr[1]),atoi(ptr[2]));
				if(res==true)
					printf("true\n");
				else
					printf("false\n");
		}
		else if(strcmp(ptr[0],"bitmap_set_all")==0)
		{
			bool boolian;
			if(strcmp(ptr[2],"true")==0)
					boolian = true;
			else
				boolian = false;
			bitmap_set_all(find_bit_arg(ptr[1]),boolian);
		}
		else if(strcmp(ptr[0],"bitmap_set_multiple")==0)
		{
			bool boolian;
			if(strcmp(ptr[4],"true")==0)
					boolian = true;
			else
				boolian = false;
			bitmap_set_multiple(find_bit_arg(ptr[1]),atoi(ptr[2]),atoi(ptr[3]),boolian);
		}
		else if(strcmp(ptr[0],"bitmap_count")==0)
		{
			bool boolian;
			if(strcmp(ptr[4],"true")==0)
					boolian = true;
			else
				boolian = false;
			printf("%d\n",(int)bitmap_count(find_bit_arg(ptr[1]),atoi(ptr[2]),atoi(ptr[3]),boolian));
		}
		else if(strcmp(ptr[0],"bitmap_contains")==0)
		{
			bool boolian,res;
			if(strcmp(ptr[4],"true")==0)
					boolian = true;
			else
				boolian = false;
			res =	bitmap_contains(find_bit_arg(ptr[1]),atoi(ptr[2]),atoi(ptr[3]),boolian);
			if(res == true)
				printf("true\n");
			else
				printf("false\n");
		}
		else if(strcmp(ptr[0],"bitmap_any")==0)
		{
			bool boolian = bitmap_any(find_bit_arg(ptr[1]),atoi(ptr[2]),atoi(ptr[3]));
			if(boolian == true)
				printf("true\n");
			else
				printf("false\n");
		}
		else if(strcmp(ptr[0],"bitmap_none")==0)
		{
			bool boolian = 	bitmap_none(find_bit_arg(ptr[1]),atoi(ptr[2]),atoi(ptr[3]));
			if(boolian == true)
				printf("true\n");
			else
				printf("false\n");
		}
		else if(strcmp(ptr[0],"bitmap_all")==0)
		{
			bool boolian = bitmap_all(find_bit_arg(ptr[1]),atoi(ptr[2]),atoi(ptr[3]));
			if(boolian == true)
				printf("true\n");
			else
				printf("false\n");
		}
		else if(strcmp(ptr[0],"bitmap_scan")==0)
		{
			bool boolian;
			if(strcmp(ptr[4],"true")==0)
					boolian = true;
			else
				boolian = false;
			printf("%u\n",(unsigned int)bitmap_scan(find_bit_arg(ptr[1]),atoi(ptr[2]),atoi(ptr[3]),boolian));
		}
		else if(strcmp(ptr[0],"bitmap_scan_and_flip")==0)
		{
			bool boolian;
			if(strcmp(ptr[4],"true")==0)
					boolian = true;
			else
				boolian = false;
			printf("%u\n",(unsigned int)bitmap_scan_and_flip(find_bit_arg(ptr[1]),atoi(ptr[2]),atoi(ptr[3]),boolian));
		}
		else if(strcmp(ptr[0],"bitmap_dump")==0)
			bitmap_dump(find_bit_arg(ptr[1]));
		else if(strcmp(ptr[0],"bitmap_expand")==0)
		{
			struct bitmap * res = find_bit_arg(ptr[1]);
			bit_name[bit_num-1].bitmap=bitmap_expand(res,atoi(ptr[2]));
		}
		else if(strcmp(ptr[0],"hash_insert")==0)
		{
			struct hash_item * new_node = malloc(sizeof(struct hash_item));
			new_node->data = atoi(ptr[2]);
			hash_insert(find_hash_arg(ptr[1]),&new_node->elem);			
		}
		else if(strcmp(ptr[0],"hash_replace")==0)
		{
			struct hash_item * new_node = malloc(sizeof(struct hash_item));
			new_node->data = atoi(ptr[2]);
			hash_replace(find_hash_arg(ptr[1]),&new_node->elem);			
		}
		else if(strcmp(ptr[0],"hash_find")==0)
		{
			struct hash_item * new_node = malloc(sizeof(struct hash_item));
			new_node->data = atoi(ptr[2]);
			struct hash_elem * test = hash_find(find_hash_arg(ptr[1]),&new_node->elem);
			if(test !=NULL)
				printf("%d\n",hash_entry(test,struct hash_item,elem)->data);			
		}
		else if(strcmp(ptr[0],"hash_delete")==0)
		{
			struct hash_item * new_node = malloc(sizeof(struct hash_item));
			new_node->data = atoi(ptr[2]);
			hash_delete(find_hash_arg(ptr[1]),&new_node->elem);
		}
		else if(strcmp(ptr[0],"hash_clear")==0)
		{
			hash_clear(find_hash_arg(ptr[1]),hashdeleter);
		}
		else if(strcmp(ptr[0],"hash_size")==0)
		{
			printf("%d\n",(int)hash_size(find_hash_arg(ptr[1])));
		}
		else if(strcmp(ptr[0],"hash_empty")==0)
		{
			bool res = hash_empty(find_hash_arg(ptr[1]));
			if(res ==true)
				printf("true\n");
			else
				printf("false\n");
		}
		else if(strcmp(ptr[0],"hash_apply")==0)
		{
			if(strcmp(ptr[2],"square")==0)
				hash_apply(find_hash_arg(ptr[1]),square);
			else if(strcmp(ptr[2],"triple")==0)
				hash_apply(find_hash_arg(ptr[1]),triple);
		}
		else if(strcmp(ptr[0],"dumpdata")==0)
		{
			tmp = find_list_arg(ptr[1]);
			if(tmp!=NULL)
			{
				struct list_elem *search;

				for(search = list_begin(tmp);search != list_end(tmp);search = list_next(search))
				{
					if(search->next==NULL)
						break;
					printf("%d ",list_entry(search,struct list_item,elem)->data);
				}
				if( list_begin(tmp) != list_end(tmp) )
					printf("\n");
				continue;
			}
			struct bitmap* tmp1 = find_bit_arg(ptr[1]);
			if(tmp1 != NULL)
			{
				int i;
				for(i=0;i<tmp1->bit_cnt;i++)
					printf("%d",bitmap_test(tmp1,i));	
				printf("\n");
				continue;
			}
			struct hash* tmp2 = find_hash_arg(ptr[1]);
			if(tmp2 !=NULL)
			{
				struct hash_iterator iter;

				hash_first(&iter,tmp2);
				while(hash_next(&iter))
				{
					struct hash_item * p = hash_entry(hash_cur(&iter),struct hash_item,elem);
					printf("%d ",p->data);
				}
				printf("\n");
				continue;
			}
			
		}
		else if(strcmp(ptr[0],"create")==0)
		{
			if(strcmp(ptr[1],"list")==0)
			{
				list_init( &list_name[list_num].list );
				strcpy(list_name[list_num].name,ptr[2]);
				list_num++;
			}
			else if(strcmp(ptr[1],"hashtable")==0)
			{
				hash_init(&hash_name[hash_num].hash,hashswan,hashbrown,NULL);
				strcpy(hash_name[hash_num].name,ptr[2]);
				hash_num++;
			}
			else if(strcmp(ptr[1],"bitmap")==0)
			{
				bit_name[bit_num].bitmap = bitmap_create(atoi(ptr[3]));
				strcpy(bit_name[bit_num].name,ptr[2]);
				bit_num++;
			}

		}
		else if(strcmp(ptr[0],"delete")==0)
		{
			tmp = find_list_arg(ptr[1]);
			if(tmp!=NULL)
			{
				struct list_elem *search,*eraser;

				for(search = list_begin(tmp);search != list_end(tmp);)
				{
					if(search->next==NULL)
						break;
					eraser = search;
					search = list_remove(search);
					free(list_entry(eraser,struct list_item,elem));
				}
				continue;
			}
			struct bitmap* tmp1 = find_bit_arg(ptr[1]);
			if(tmp1 != NULL)
			{
				free(tmp1);
				continue;
			}
			struct hash* tmp2 = find_hash_arg(ptr[1]);
			if(tmp2 !=NULL)
			{
				hash_clear(tmp2,hashdeleter);
			}

		}
		for(i=0;i<100;i++)
			input[i]='\0';
		for(i=0;i<10;i++)
			ptr[i]=NULL;
	}

	return 0;
}
struct list* find_list_arg(char * str)
{
	int i;
	for (i=0;i<list_num;i++)
	{
		if(strcmp(list_name[i].name,str)==0)
		{
			return &list_name[i].list;
		}
	}
	return NULL;
}
struct bitmap* find_bit_arg(char * str)
{
	int i;
	for (i=0;i<bit_num;i++)
	{
		if(strcmp(bit_name[i].name,str)==0)
		{
				return bit_name[i].bitmap;
		}
	}
	return NULL;
}

struct hash* find_hash_arg(char * str)
{
	int i;
	for (i=0;i<hash_num;i++)
	{
		if(strcmp(hash_name[i].name,str)==0)
		{
				return &hash_name[i].hash;
		}
	}
	return NULL;
}
