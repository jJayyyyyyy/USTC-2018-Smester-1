#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/*
Acknowledgement: ngncmh
感谢 ngncmh 博主的文章
https://blog.csdn.net/kqzxcmh/article/details/41552945

本次实验在其博客代码之上进行修改
*/

team_t team = {
	/* Team name */
	"hello",
	/* First member's full name */
	"world",
	/* First member's email address */
	"hello@world.com",
	/* Second member's full name (leave blank if none) */
	"",
	/* Second member's email address (leave blank if none) */
	""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(p) (((size_t)(p) + (ALIGNMENT-1)) & ~0x7)


#define WSIZE 4
#define DSIZE 8
#define TSIZE 12
#define QSIZE 16
#define CHUNKSIZE (256)


#define BLOCK4 (4)
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

#define PACK(size, alloc) ((size) | (alloc))
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)
#define GET_PRE_ALLOC(p) (GET(p) & 0x2)   //倒数第二位存放迁移块是否被释放的信息

#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))
//binary Tree
#define GET_LEFTSON(bp)  (GET( LEFTSON(bp)  ) ) 
#define GET_RIGHTSON(bp) (GET( RIGHTSON(bp) ) )
 
#define LEFTSON(bp)  ( (char *)(bp) )
#define RIGHTSON(bp) ( (char *)(bp) + WSIZE )

#define CHANGE32(bp) ( ( (char *)bp - Tnode))
#define CHANGE64(bp) ( (Tnode + bp))

#define CHECKMIN(bp, t) (GET_SIZE(HDRP(bp)) < GET_SIZE(HDRP(t))) || ((GET_SIZE(HDRP(bp)) == GET_SIZE(HDRP(t))) && CHANGE32(bp)<CHANGE32(t))
#define null (0)

static void *extend_heap(size_t words);
static void *coalesce(void *bp);
static void place(void *bp, size_t asize);
static char * heap_listp;
static char * listp4;
static char * listp2;
static unsigned int root ;
static char * Tnode;
static char * LASTBLOCK= NULL;
static int ok = 0;
static void insert(void * bp);
static void move(void *bp);
static void splay(void * bp);
static void * find_fit(size_t asize);

//static int find(void * bp);
// 自顶向下的splay
static void splay(void * bp){
	if ( root == null ){
		return ;
	}
	char * L = NULL;
	char * R = NULL;
	char * y = NULL;
	char * node = Tnode;
	PUT( LEFTSON(node), null );
	PUT( RIGHTSON(node), null );
	L = R = node;		
	void * t = CHANGE64(root);
	while (1){
		if ( CHANGE32(bp) == CHANGE32(t) ){
			break;
		}
		if ( CHECKMIN(bp,t)){
			if ( GET_LEFTSON(t) != null  && (CHECKMIN(bp,CHANGE64(GET_LEFTSON(t)))) ) {
				y = CHANGE64(GET_LEFTSON(t));
				PUT(LEFTSON(t), GET_RIGHTSON(y));
				PUT(RIGHTSON(y), CHANGE32(t));
				t = y;
			}
			if ( GET_LEFTSON(t) == null){
				break;
			}
			PUT(LEFTSON(R), CHANGE32(t));
			R = t;
			t = CHANGE64(GET_LEFTSON(t));
		}
		else {
			if ( GET_RIGHTSON(t) != null && (CHECKMIN(CHANGE64(GET_RIGHTSON(t)),bp))) {
				y = CHANGE64(GET_RIGHTSON(t));
				PUT(RIGHTSON(t), GET_LEFTSON(y));
				PUT(LEFTSON(y), CHANGE32(t));
				t = y;
			}
			if ( GET_RIGHTSON(t) == null){
				break;
			}
			PUT(RIGHTSON(L), CHANGE32(t));
			L = t;
			t = CHANGE64(GET_RIGHTSON(t));
		}
	}
	PUT( RIGHTSON(L), GET_LEFTSON(t));
	PUT( LEFTSON(R),  GET_RIGHTSON(t));
	PUT( LEFTSON(t),  GET_RIGHTSON(node));
	PUT( RIGHTSON(t), GET_LEFTSON(node));
	root = CHANGE32(t);
	return ;
}

// 找长度为4的块
static void * find_listp4(void){
	unsigned int t = GET_LEFTSON(listp4);
	if (t==0){
		return NULL;
	}
	return CHANGE64(t);
}

static void * find_fit(size_t asize){	
	void * bp = NULL;
	if (asize == DSIZE){
		unsigned int t = GET_RIGHTSON(listp2);
		if (t!=0){
			return CHANGE64(t);
		}
	}
	if (asize <= BLOCK4 * WSIZE){
		 bp = find_listp4();
		 if( bp != NULL ){
		 	return bp;
		 }
	}
	unsigned int tmp =root;
	while ( tmp != null){
			void * t = CHANGE64(tmp);
			if (GET_SIZE(HDRP(t))>= asize){
				bp = t;
				tmp = GET_LEFTSON(t);
			}else{
				tmp = GET_RIGHTSON(t);
			}
	}
	
	if( bp!=NULL ){
		splay(bp);
	}
	return bp;
}

// 在双向链表中插入长度为4的块
static void add_listp4(void * bp){
	unsigned int t  = GET(RIGHTSON( listp4) );
	PUT( listp4, CHANGE32(bp) );
	PUT( LEFTSON(bp), CHANGE32(listp4) );
	PUT( RIGHTSON(bp), t );
	if( t!=0 ){
		PUT( LEFTSON( CHANGE64(t) ), CHANGE32(bp) );
	} else{
		PUT(LEFTSON(listp4),CHANGE32(bp));
	}
}

static void insert(void * bp){
	if (FTRP(bp) == LASTBLOCK) {
		ok = 1;
	}
	if (GET_SIZE(HDRP(bp)) <= DSIZE) {
		PUT(RIGHTSON(listp2), CHANGE32(bp));
		return ;
	}
	if (GET_SIZE(HDRP(bp)) == BLOCK4 * WSIZE){
		add_listp4(bp);
		return ;
	}
	PUT(LEFTSON(bp), null);
	PUT(RIGHTSON(bp), null);

	if (root==null){
		root = CHANGE32(bp);
		return ; 
	}
	unsigned int tmp = root;
	void * last = NULL;
	while ( tmp != null){
		last = CHANGE64(tmp);
		if( CHECKMIN(bp, last) ){
			tmp = GET_LEFTSON(last) ;
		}
		else{
			tmp = GET_RIGHTSON(last);
		}
	}
	
	if (CHECKMIN(bp,last)){
		PUT(LEFTSON(last), CHANGE32(bp));
	}
	else{
		PUT(RIGHTSON(last), CHANGE32(bp));
	}
	splay(bp);
}

static void move_listp(void * bp){
	unsigned int pre = GET(LEFTSON(bp));
	unsigned int suc = GET(RIGHTSON(bp));

	if ( pre != 0 ){
		PUT(RIGHTSON(CHANGE64(pre)), suc);
	}
	
	if (suc != 0){
		PUT(LEFTSON(CHANGE64(suc)), pre);
	}else{
		PUT(LEFTSON(listp4), suc);
	}
}

//在splay或者双向链表中删除节点
static void move(void * bp){
	if( FTRP(bp) == LASTBLOCK ){
		ok = 0;
	}
	if( GET_SIZE(HDRP(bp)) <= DSIZE ){
		PUT( RIGHTSON(listp2), 0 );
		return ;
	}
	
	if( GET_SIZE(HDRP(bp) ) <= BLOCK4 * WSIZE ){
		move_listp(bp);
		return ;
	}
	splay(bp);
	
	if( CHANGE32(bp) !=root ){
		// printf("bp:(%p)  root:(%p)\n", bp, CHANGE64(root));
		// printTree(root, 0);
		exit(0);
	}
	unsigned int  T = GET_LEFTSON(bp);
	void * last = NULL;
	if( T == null ){
		root = GET_RIGHTSON(bp);
	} else {
		while ( T != null){
				last = CHANGE64(T);
				T = GET_RIGHTSON(last);
		}
		void * tmp = CHANGE64(root);
		root = GET_LEFTSON(tmp);
		splay( last );
		PUT(RIGHTSON(last), GET_RIGHTSON(tmp));
	}
}

static void * extend_heap( size_t word){
	char * bp;
	size_t size ;
	
	size = (word % 2 ) ? (word + 1) : word;
	size = (word)* WSIZE;
	if( (long)(bp = mem_sbrk(size))  == -1 ){
		return NULL;
	}
	if( ok==0 ){
		PUT(HDRP(bp), PACK(size, 2));
		PUT(FTRP(bp), PACK(size, 2));
	}else{
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 2));
	}
	LASTBLOCK = FTRP(bp); 
	PUT( HDRP(NEXT_BLKP(bp)), PACK(0, 1) );
	return coalesce(bp);
}

/*
 * Initialize: return -1 on error, 0 on success.
 */
int mm_init(void) {
	
	if( (void *)( Tnode = mem_sbrk(4 * WSIZE) ) < (void *)0){
		return -1;
	}
	Tnode += WSIZE;
	PUT( HDRP(Tnode), PACK(QSIZE,1) );
	PUT( FTRP(Tnode), PACK(QSIZE,1) );

	if( (void *)( listp2 = mem_sbrk(2 * WSIZE) ) < (void *)0 ){
		return -1;
	}
	PUT(listp2,0);
	PUT(listp2+WSIZE,0);
	if( (void *)( listp4 = mem_sbrk(2 * WSIZE) ) < (void *)0 ){
		return -1;
	}
	PUT(listp4,0);
	PUT(listp4+WSIZE,0);
	
	if( (void *)( heap_listp = mem_sbrk(4 * WSIZE) ) < (void *) 0 ){
		return -1;
	}
	
	root = null;
	LASTBLOCK = NULL;
	ok = 0;
	
	PUT( heap_listp , 0);
	PUT( heap_listp + (1 * WSIZE) , PACK(DSIZE,1) );
	PUT( heap_listp + (2 * WSIZE) , PACK(DSIZE,1) );
	PUT( heap_listp + (3 * WSIZE) , PACK(0,1));
	heap_listp +=(2 * WSIZE);

	return 0;
}

//切割函数
static void place(void * bp, size_t asize){
	size_t csize = GET_SIZE(HDRP(bp));
	move(bp);
	if( (csize - asize) >= DSIZE ){
		PUT(HDRP(bp), PACK(asize, 1+GET_PRE_ALLOC(HDRP(bp))));
		PUT(FTRP(bp), PACK(asize, 1+GET_PRE_ALLOC(HDRP(bp))));
		bp = NEXT_BLKP(bp);
		PUT(HDRP(bp), PACK((csize-asize),2));
		PUT(FTRP(bp), PACK((csize-asize),2));	
		insert(bp);
	}else{
		PUT(HDRP(bp), PACK(csize, 1+GET_PRE_ALLOC(HDRP(bp))));
		PUT(FTRP(bp), PACK(csize, 1+GET_PRE_ALLOC(HDRP(bp))));
		PUT(HDRP(NEXT_BLKP(bp)), (GET(HDRP(NEXT_BLKP(bp))) | (0x2)));
	}
}

/*
 * mm_malloc
 */
void * mm_malloc (size_t size) {
	size_t asize;
	size_t extendsize;
	char * bp;
	if (size == 0){
		return NULL;
	}
	if (size <= WSIZE){
		asize =  DSIZE;
	}else{
	 	asize = DSIZE * ( ( size + (WSIZE)+(DSIZE-1) )/ DSIZE);
	}
	if ((bp = find_fit(asize)) != NULL){
		place(bp,asize);
		return bp;
	}
	if ( ok == 0) {
		extendsize = MAX(asize, CHUNKSIZE);
	 } else {
		extendsize = asize - GET_SIZE(LASTBLOCK);    // 如果上一次申请的块还有剩余则这次申请可以节在上次申请的后面
	 }
	 if (ok ==1 && extendsize == 0){
		ok = 0;
		bp = LASTBLOCK;
		place(bp,asize);
	 } else {
		if ((bp= extend_heap(extendsize/WSIZE)) == NULL){
			return NULL;
		}
		place(bp,asize);
	}
	return bp;
}

// 合并操作
static void * coalesce(void *bp){
	size_t prev_alloc = GET_PRE_ALLOC( HDRP(bp) );
	size_t next_alloc = GET_ALLOC(HDRP( NEXT_BLKP(bp)) );
	size_t size= GET_SIZE( HDRP(bp) );
 
	if (prev_alloc && next_alloc){
		insert(bp);
		PUT(HDRP(NEXT_BLKP(bp)), (GET(HDRP(NEXT_BLKP(bp))) & (~0x2)));
		return bp;
	}
	else if( prev_alloc && !next_alloc ){
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		move(NEXT_BLKP(bp));
		PUT( HDRP(bp), PACK(size,GET_PRE_ALLOC(HDRP(bp))));
		PUT( FTRP(bp), PACK(size,GET_PRE_ALLOC(HDRP(bp))));
	}
	else if( !prev_alloc && next_alloc ){
		size += GET_SIZE(HDRP(PREV_BLKP(bp)));
		move(PREV_BLKP(bp));    
		PUT( FTRP(bp), PACK(size,GET_PRE_ALLOC(HDRP(PREV_BLKP(bp)))));
		PUT( HDRP((PREV_BLKP(bp))), PACK(size,GET_PRE_ALLOC(HDRP(PREV_BLKP(bp)))) );
		bp = PREV_BLKP(bp);
	}
	else{
		size += GET_SIZE(HDRP(PREV_BLKP(bp)))+GET_SIZE(FTRP(NEXT_BLKP(bp)));
		move(PREV_BLKP(bp)); 
		move(NEXT_BLKP(bp));
		PUT( HDRP(PREV_BLKP(bp)), PACK(size,GET_PRE_ALLOC(HDRP(PREV_BLKP(bp))) ));
		PUT( FTRP(NEXT_BLKP(bp)), PACK(size,GET_PRE_ALLOC(HDRP(PREV_BLKP(bp))) ));
		bp = PREV_BLKP(bp);		
	}
	insert(bp);
	PUT(HDRP(NEXT_BLKP(bp)), (GET(HDRP(NEXT_BLKP(bp))) & (~0x2)));
	return bp;
}

/*
 * mm_free
 */
void mm_free (void *bp) {
	if (bp==NULL)   return ;
	size_t size = GET_SIZE(HDRP(bp));

	PUT(HDRP(bp), PACK(size,GET_PRE_ALLOC(HDRP(bp))));
	PUT(FTRP(bp), PACK(size,GET_PRE_ALLOC(HDRP(bp))));
	coalesce(bp);
}
 
 
/*
 * mm_realloc - you may want to look at mm-naive.c
 */
void *mm_realloc(void *oldptr, size_t size) {
	char * newptr;
	size_t csize;
	if (oldptr == NULL)
		return mm_malloc(size);
	if (size == 0) {
		mm_free(oldptr);
		return NULL;
	}
	newptr = mm_malloc(size);
	csize = MIN(size, GET_SIZE(HDRP(oldptr)) - WSIZE);

	memmove(newptr, oldptr, csize);
	mm_free(oldptr);
	return newptr;
}

/*
 * mm_calloc - you may want to look at mm-naive.c
 * This function is not tested by mdriver, but it is
 * needed to run the traces.
 */
void * mm_calloc (size_t nmemb, size_t size) {
	size_t cntSize = nmemb * size;
	char * ptr = mm_malloc(cntSize);
	char * temp = ptr;
	size_t i;	
	for (i = 0; i < nmemb; i++) {
		* temp = 0;
		temp = temp + size;
	}
	return ptr;
}

/*
 * Return whether the pointer is in the heap.
 * May be useful for debugging.
 */
/*
static int in_heap(const void *p) {
	return p <= mem_heap_hi() && p >= mem_heap_lo();
}*/
 
 
/*
 * Return whether the pointer is aligned.
 * May be useful for debugging.
 */
/*
static int aligned(const void *p) {
	return (size_t)ALIGN(p) == (size_t)p;
}

*/
/*
 * mm_checkheap
 */

/*
static void printNode(unsigned int root){
	char * t = CHANGE64(root);
	printf("node:(%p)  size:%u: ", t,(unsigned int) GET_SIZE(HDRP(t)));
	printf("L:(%p)   R:(%p)\n", CHANGE64(GET_LEFTSON(t)), CHANGE64(GET_RIGHTSON(t)));
}
*/

/*
static void printTree(unsigned int root, unsigned int fa){
	if (root == null){
		return;
	}
	printf( "father :(%p) ", CHANGE64(fa) );
	printNode(root);
	unsigned int l = GET_LEFTSON( CHANGE64(root) );
	if(l!=null) {
		printTree(l,root);
	}
	unsigned int r = GET_RIGHTSON(CHANGE64(root));
	if(r!=null){
		printTree(r,root);
	}
}
*/

/*
void mm_checkheap(int verbose){
	char *bp = heap_listp;
	if (verbose == 1) {
		printf("root:%u\n",root);
		printTree(root,0);
		printNode(root);	
		printf("%u\n", GET_SIZE(HDRP(bp)));
		printf("HDRP (%p):\n", HDRP(bp));	
		printf("Heap (%p):\n", bp);
		printf("node (%p):\n", Tnode);
		unsigned int r = bp - Tnode;	
		printf("%u\n",r);
		printf("Heap (%p):\n", Tnode+r);
		PUT(LEFTSON(Tnode), 14);
		r = GET_LEFTSON(Tnode);
		printf("%u\n",r);
		printf("=================================\n");	
		printf("\n");	
	}
}
*/
