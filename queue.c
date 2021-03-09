#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;

    list_ele_t *next = q->head;
    while (next) {
        list_ele_t *cur = next;
        next = next->next;

        free(cur->value);
        cur->value = NULL;
        cur->next = NULL;
        free(cur);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!newh)
        return false;

    if (s) {
        size_t sml = strlen(s);
        newh->value = malloc(sml + 1);
        if (!newh->value) {
            free(newh);
            return false;
        }
        for (size_t i = 0; i < sml; i++)
            *((newh->value) + i) = *(s + i);
        *((newh->value) + sml) = '\0';
    }

    newh->next = q->head;

    if (!q->head)  // if list is empty
        q->tail = newh;

    q->head = newh;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));

    if (!newh)
        return false;

    if (s) {
        size_t sml = strlen(s);
        newh->value = malloc(sml + 1);
        if (!newh->value) {
            free(newh);
            return false;
        }
        for (size_t i = 0; i < sml; i++)
            *((newh->value) + i) = *(s + i);
        *((newh->value) + sml) = '\0';
    }

    newh->next = NULL;

    if (!q->tail)  // if list is empty
        q->head = newh;
    else  // if list isn't empty
        q->tail->next = newh;

    q->tail = newh;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return false;

    list_ele_t *list_h = q->head;
    q->head = q->head->next;

    q->size--;
    if (q->size == 0)
        q->tail = NULL;

    if (sp && list_h->value) {
        size_t i;
        for (i = 0; i < bufsize - 1; i++) {
            char tmp = *((list_h->value) + i);
            if (tmp == '\0')
                break;

            *(sp + i) = tmp;
        }
        *(sp + i) = '\0';
    }

    free(list_h->value);
    list_h->value = NULL;
    list_h->next = NULL;
    free(list_h);

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return 0;

    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return;

    list_ele_t *next = q->head;
    list_ele_t *cur = NULL;
    list_ele_t *prev;

    while (next) {
        prev = cur;
        cur = next;
        next = next->next;

        cur->next = prev;
    }

    q->tail = q->head;
    // q->tail->next = NULL;
    q->head = cur;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */

/*
 * Bubble Sort
 */
/*
void q_sort(queue_t *q)
{
    //TODO: You need to write the code for this function *
    //TODO: Remove the above comment when you are about to implement. *
    if(!q || !q->head)
        return;

    // result = strcmp(str1, str2)
    // result >  0 : str1 > str2
    // result == 0 : str1 == str2
    // result <  0 : str1 < str2


    list_ele_t **cur;

    for(int i = 1 ; i<q->size ; i++)
    {
        cur = &q->head;
        for(int j = 0 ; j<(q->size)-i ; j++)
        {
            list_ele_t *next = (*cur)->next;
            if(strcmp((*cur)->value, next->value) > 0)
            {
                next = *cur;
                *cur = (*cur)->next;

                next->next = (*cur)->next;
                (*cur)->next = next;
            }
            cur = &(*cur)->next;
        }
        if(i == 1)
        {
            q->tail = *cur;
        }
    }


}
*/

/*
 * Merge Sort
 */

/*
 * Get middle of the lineked list
 * And assign NULL to the next (pointer) of the prev of middle
 */
list_ele_t *get_middle_c(list_ele_t *h)
{
    list_ele_t *fast = h->next;
    list_ele_t *slow = h;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;
    return fast;
}

list_ele_t *merge(list_ele_t *left, list_ele_t *right)
{
    list_ele_t *mix;
    if (strcmp(left->value, right->value) <= 0) {
        mix = left;
        left = left->next;
    } else {
        mix = right;
        right = right->next;
    }
    list_ele_t *cur = mix;

    while (left && right) {
        if (strcmp(left->value, right->value) <= 0) {
            cur->next = left;
            left = left->next;
        } else {
            cur->next = right;
            right = right->next;
        }
        cur = cur->next;
    }

    if (!left) {
        cur->next = right;
    } else {
        cur->next = left;
    }
    return mix;
}

list_ele_t *mergesort(list_ele_t *h)
{
    if (!h->next)
        return h;

    list_ele_t *m = get_middle_c(h);

    list_ele_t *left = mergesort(h);
    list_ele_t *right = mergesort(m);
    return merge(left, right);
}


void q_sort(queue_t *q)
{
    if (!q || q->size < 2)
        return;

    q->head = mergesort(q->head);
    list_ele_t *cur = q->head;
    while (cur->next)
        cur = cur->next;
    q->tail = cur;
}
