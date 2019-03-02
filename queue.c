/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"



/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) {
        return false;
    }
    q->head = NULL;
    q->tail = NULL;
    q->q_size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Free queue structure */
    if (!q) {
        return;
    }
    while (q->head) {
        q_remove_head(q, NULL, 0);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    newh->value = malloc((strlen(s) + 1) * sizeof(char));
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    newh->next = q->head;
    q->head = newh;
    if (!q->tail) {
        q->tail = newh;
    }
    q->q_size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    newh->value = malloc((strlen(s) + 1) * sizeof(char));
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    newh->next = NULL;
    if (q->tail) {
        q->tail->next = newh;
    } else {
        assert(!q->head);
        q->head = newh;
    }
    q->tail = newh;
    q->q_size++;
    /* Remember: It should operate in O(1) time */
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (is_null_or_empty(q)) {
        return false;
    }
    if (sp) {
        strcpy(sp, q->head->value);
    }

    if (q->head->value) {
        free(q->head->value);
    }
    list_ele_t *newh = q->head->next;

    free(q->head);
    q->head = newh;
    q->q_size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if (is_null_or_empty(q)) {
        return 0;
    }
    return q->q_size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (is_null_or_empty(q)) {
        return;
    }
    list_ele_t *cur = q->head;
    list_ele_t *next = cur->next;
    cur->next = NULL;
    q->tail = cur;
    while (next) {
        list_ele_t *nn = next->next;
        next->next = cur;
        cur = next;
        next = nn;
    }
    q->head = cur;
}
