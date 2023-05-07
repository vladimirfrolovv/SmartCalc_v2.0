#include "s21_smart_calc.h"

list *s21_push(list *head, char elem, int priority) {
  list *new;
  new = (list *)calloc(1, sizeof(list));
  if (head == NULL) {
    new->elem = elem;
    new->priority = priority;
    new->next = NULL;
  } else {
    new->elem = elem;
    new->priority = priority;
    new->next = head;
  }

  return new;
}
list *s21_pop(list *head) {
  list *cur = head;
  if (cur != NULL) {
    cur = head->next;
    free(head);
  }
  return cur;
}

// void s21_remove(list *head) {
//   list *cur = head;
//   list *next = NULL;
//   while (cur != NULL) {
//     next = cur->next;
//     free(cur);
//     cur = next;
//   }
// }

list_value *s21_push_value(list_value *head, double value) {
  list_value *new = {0};
  new = (list_value *)calloc(1, sizeof(list_value));
  if (head == NULL) {
    new->value = value;
    new->next = NULL;
  } else {
    new->value = value;
    new->next = head;
  }

  return new;
}
list_value *s21_pop_value(list_value *head) {
  list_value *cur = head;
  if (cur != NULL) {
    cur = head->next;
    free(head);
  }
  return cur;
}

void s21_remove_val(list_value *head) {
  list_value *cur = head;
  list_value *next = NULL;
  while (cur != NULL) {
    next = cur->next;
    free(cur);
    cur = next;
  }
}
