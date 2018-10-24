/*--- citytemp.c--------------------------- Listing 2-1 ---------
 *  Reads a text file of cities and temperatures in the
 *  following format:   TempCity
 *      where Temp is a number of three digits or
 *      a sign and two digits; City is a string of length < 124
 *  Examples:     -10Duluth
 *                096Phoenix
 *  The records are read into a singly linked list by order
 *  of temperature and city; duplicates are discarded. At EOF,
 *  the whole list is printed with an indication of the median
 *  temperature. And then, the list is progressively shortened
 *  and reprinted showing the median.
 *              Usage: citytemp filename.ext
 *-------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--- data definitions ---*/

struct Node {           /* a node in our linked list */
    char  *City;
    int    Temp;
    struct Node *Next;
};

typedef struct Node * Link; /* Links are pointers to nodes */

Link Head;              /* head of our linked list */
int  NodeCount;         /* how many nodes in the list */

/*--- functions declarations for linked lists ---*/

int  AddNodeAscend ( Link );        /* add a node           */
void CreateList ( void );           /* initialize list      */
int  DeleteNode ( Link );           /* delete a node        */
int  DuplicateNode ( Link, Link );  /* handle duplicate inserts */
void FreeNode ( Link );             /* free a node's memory */
void ShowNodes ( void );            /* show list of nodes   */
int  NodeCmp ( Link, Link );        /* compare two nodes    */

/*--- function definitions ---*/

int AddNodeAscend ( Link to_add )
{
    Link   pn,   /* local copy of node to be added */
           prev, /* points to previous node */
           curr; /* points to node being examined */
    struct Node dummy;
    int    i;

    /* Make a copy of the input node */
    pn = ( Link ) malloc ( sizeof ( struct Node ));
    if ( pn == NULL )
        return 0;
    memcpy ( pn, to_add, sizeof ( struct Node ));

    /* set up a dummy node to simplify logic */
    dummy.Next = Head;
    prev = &dummy;
    curr = Head;

    /* insert node pn */
    for ( ;; prev = curr, curr = curr->Next )
    {
        if ( curr == NULL )
            break; /* reached the end */

        i = NodeCmp ( pn, curr );
        if ( i <= 0 )
             break; /* pn precedes curr */
    }

    if ( curr && i == 0 ) /* we have a duplicate */
        if ( DuplicateNode ( curr, pn ) == 0 )
            return ( 1 ); /* bail out if DuplicateNode says to */

    prev->Next = pn;
    pn->Next = curr;

    Head = dummy.Next;
	NodeCount+=1;//yyw
    return ( 1 );
}

/*--------------------------------------------------------------
 * Handle the duplicate node. In this program,
 * we just delete the duplicate.
 *-------------------------------------------------------------*/
int DuplicateNode ( Link inlist, Link duplicate )
{
    FreeNode ( duplicate );
    return ( 0 );
}

int DeleteNode ( Link to_delete )
{
    Link curr,  /* the current node */
         prev;  /* the previous node */
    int  i;

    /*--- Is there anything in the list? ---*/
    if ( Head == NULL )
        return ( 0 );

    /*--- If so, step through the list looking for the node ---*/
    for ( prev = NULL, curr = Head;
        curr != NULL && ( i = NodeCmp ( to_delete, curr )) > 0;
        prev = curr, curr = curr->Next )
        /* loop around */ ;

    /*--- Found a match, so delete it ---*/
    if ( curr != NULL && i == 0 )
    {
        if ( prev )
            prev->Next = curr->Next;
        else              /* deleting Head */
            Head = curr->Next;

        FreeNode ( curr );
        NodeCount -= 1;
        return ( 1 );
    }

    return ( 0 );
}

int NodeCmp ( Link a, Link b )
{
    /* returns 1, 0, -1, depending on whether the data in
     * a is greater than, equal, or less than b.
     */

    /* if temps are unequal, return based on temp */
    if ( a->Temp != b->Temp )
        return ( a->Temp - b->Temp );

    /* else, return based on city's name */
    return strcmp ( a->City, b->City );
}

void CreateList ( void )
{
    Head = NULL;
    NodeCount = 0;
}

void FreeNode ( Link n )
{
    free ( n->City );
    free ( n );
}

void ShowNodes( void )
{
    Link pn;
    int count, median;

 //   /* count the nodes */
 //   for ( count = 0, pn = Head; pn; pn = pn->Next )
 //       count += 1;

 //   /* compute the median node */
 //   median = count / 2 + 1;

	///* compute the median node */
	median = NodeCount/2+1;//yyw

    /* step through the list printing cities and
     * temperatures. Announce the median temperature.
     */
    if ( NodeCount ) /* only print if there's a node */
    {
        /* initialize the needed variables */
        count = 0;     /* count of nodes we've printed */
        for ( pn = Head; pn; pn = pn->Next )
        {
            printf ( "%-20s: %3d", pn->City, pn->Temp );
            count += 1;
            if ( count == median )
                printf ( " --Median--" );
            printf ( "\n" );
        }
    }
    else
        printf ( "Empty list\n" );
}

/*--- main line ---*/
int main ( int argc, char *argv[] )
{
    FILE *fin;        /* file we'll be reading from */
    char buffer[128]; /* where we'll read the file into */

    struct Node n;    /* the node we add each time */

    if ( argc != 2 )
    {
        fprintf ( stderr, "Usage: citytemp filename.ext\n" );
        exit ( EXIT_FAILURE );
    }

    fin = fopen ( argv[1], "rt" );
    if ( fin == NULL )
    {
        fprintf ( stderr, "Cannot open/find %s\n", argv[2] );
        exit ( EXIT_FAILURE );
    }

    /* Create and initialize the linked list to empty */
    CreateList();

    /*--- main loop ---*/
    while ( ! feof ( fin ))
    {
        /* read a record consisting of a line of text */
        if ( fgets ( buffer, 127, fin ) == NULL )
            break;

        /* get rid of the trailing carriage return */
        buffer [ strlen ( buffer ) - 1 ] = '\0';

        /* copy the city name to the node to be added */
        n.City = strdup ( buffer + 3 );

        /* mark off the temperature and convert to int */
        buffer[3] = '\0';
        n.Temp = atoi ( buffer );

        /* add the node to the list */
        if ( AddNodeAscend ( &n ) == 0 )
        {
            fprintf ( stderr, "Error adding node. Aborting\n" );
            exit ( EXIT_FAILURE );
        }
    }

    ShowNodes();

    /* Now, delete something */
    printf( "\n" );
    DeleteNode ( Head );
    ShowNodes();

    while (Head && Head->Next)
    {
        printf ( "\n" );
        DeleteNode ( Head->Next );
        ShowNodes();
    }

    printf ( "\n" );
    DeleteNode ( Head );
    ShowNodes();

    fclose ( fin );
    return ( EXIT_SUCCESS );
}
