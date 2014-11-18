#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"

#define END 256
#define l(x) ((x)*2+1)
#define p(x) (((x)-1)/2)
#define r(x) ((x)*2+2)

void insert(struct tree *tr);
struct tree *delete(void);
void print(void);

static int count;
static int counts[END+1];
static struct tree *heap[END+1];
static struct tree *nodes[END+1];

int main (int argc, char *argv[])
{
        assert (argc == 3); 
    

        FILE *fp;
        fp = fopen(argv[1], "r");
        assert(fp != NULL);
    
        struct tree *new1;
        struct tree *new2;
        int i,c;
    
        count =0; 

        for(i=0;i<END;i++)
        {   
                counts[i] =0;   
                nodes[i] = NULL;
        }   
        while((c=getc(fp))!= EOF) //c is an int
                counts[c]++;
        for(i=0;i<END;i++)
        {   
                if (counts[i] != 0)
                {   
                        insert(nodes[i] = createTree (counts[i], NULL, NULL));
                }   
        }   
        insert(nodes[END] = createTree(0,NULL, NULL));
        while(count > 1)
        {
                new1 = delete();
                new2 = delete();
                insert(createTree((getData(new1)+getData(new2)), new1, new2));
        }
        fclose(fp);
        print();
        pack(argv[1], argv[2], nodes);
        return 0;
}

# if 1


void insert(struct tree *tr)
{
        assert(tr != NULL);

        int index=count++;
        int parent;

        while (index>0 && getData(heap[p(index)])>getData(tr))
        {
                parent = p(index);
                heap[index]= heap[parent];
                index = parent;
        }
        heap[index] = tr;
        return;
}

struct tree *delete (void)
{
        struct tree *min;
        struct tree *initial;
        struct tree *temp;
        int index, right, left, minchild;

        index = 0;
        left = l(index);
        right = r(index);
        min = heap[0];
        initial = heap[count-1];

        while (left < count)
        {
                //Only left child
                if (left == count-1)
                {
                        if(getData(initial)>getData(heap[left]))
                        {
                                heap[index]= heap[left];
                                index = left;}
                        break;
                }
                //Left and right child
                minchild = (getData(heap[left]) < getData(heap[right]))? left:right;
                if (getData(initial) <= getData(heap[minchild]))
                {
                        break;
                }
                else
                {
                        heap[index] = heap[minchild];
                        index = minchild;
                        left = l(index);
                        right = r(index);
                }
        }
        heap[index] = heap[count-1];
        count--;
        return min;
}

# else

void insert(struct tree *x) 
{
    heap[count ++] = x;
}

struct tree *delete(void) 
{
    int i, min;
    struct tree *temp;

    min = 0;

    for (i = 1; i < count; i ++)
        if (getData(heap[i]) < getData(heap[min]))
            min = i;

    temp = heap[min];
    heap[min] = heap[-- count];
    return temp;
}

# endif


void leafprint(struct tree *leaf)
{
        if(getParent(leaf) == NULL)
        {
                return;
        }
        leafprint (getParent(leaf));
        if(leaf  == getLeft(getParent(leaf)))
                printf ("1");
        else
                printf("0");
}

void print (void)
{
        int i;

        for (i=0; i<=END; i++)
        {
                if (nodes[i] == NULL)
                        continue;
                if (isprint(i))
                        printf("'%c' :", i);
                else
                        printf("%03o :", i);
                printf("%d ", counts[i]);
                leafprint(nodes[i]);
                printf("\n");
        }
}
