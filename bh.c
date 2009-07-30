#include <stdio.h>
#define ARRAY_LIMIT 100

/*
    A Binary Heap implementation
*/

/* Binary Heap struct with a length and set length array */
struct BinaryHeap {
    int length;
    int array[ARRAY_LIMIT];
};

/* Returns 1 if length is zero */
int is_empty(struct BinaryHeap *bh) {
    return bh->length == 0;
}

/* Returns the minimum element without removing it */
int find_min(struct BinaryHeap *bh) {
    return bh->array[0];
}

/* Percolates the hole from the new position and fills the x once no elements above are less */
void insert(struct BinaryHeap *bh, int x) {
    int hole = ++bh->length;
    for( ; hole > 1 && x < bh->array[ hole / 2 - 1]; hole /= 2 )
        bh->array[ hole - 1] = bh->array[ hole / 2 - 1];
    bh->array[ hole - 1 ] = x;
}

/* Percolates the hole down after removing the top element */
void percolate_down(struct BinaryHeap *bh, int hole )
{
    int child;
    int tmp = bh->array[ hole - 1 ];

    for( ; hole * 2 <= bh->length; hole = child )
    {
        child = hole * 2;
        if( child != bh->length && bh->array[ child ] < bh->array[ child - 1 ] )
            child++;
        if( bh->array[ child -1 ] < tmp )
            bh->array[ hole - 1 ] = bh->array[ child - 1 ];
        else
            break;
    }
    bh->array[ hole - 1] = tmp;
}

/* Removes the minimun element and returns it */
int remove_min(struct BinaryHeap *bh) {
    int min;
    min = bh->array[0];
    bh->array[ 0 ] = bh->array[bh->length-- - 1];
    percolate_down(bh, 1);
    return min;
}

/* Forces the heap empty by setting length to zero */
void make_empty(struct BinaryHeap *bh){
    bh->length = 0;
}

/* Builds the heap if the array was populated manually */
void build_heap(struct BinaryHeap *bh) {
    int i;
    for(i = bh->length / 2; i > 1; i-- )
        percolate_down(bh, i);
}

int main() {
    struct BinaryHeap bh;
    bh.length = 0;
    int num;
    while(1) {
        printf( "Please enter a number (0 to sort and quit): " );
        scanf("%d", &num );
        if(num == 0)
            break;
        insert(&bh, num);
    }
    printf("\n");
    printf("Heap Sorted: ");
    while(!is_empty(&bh)) {
        printf("%d ", remove_min(&bh));
    }
    printf("\n");

}

