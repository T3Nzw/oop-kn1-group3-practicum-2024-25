#include <iostream>
#include <vector>

struct node {
  int data;
  node* next;
  node(int data=int(), node* next=nullptr)
  : data(data), next(next) {}
};

node* fromVector(std::vector<int> const& vec) {
  node dummy;
  node* dptr = &dummy;
  for (int el : vec) {
    dptr->next = new node(el);
    dptr = dptr->next;
  }
  return dummy.next;
}

//освобождава паметта и за потенциално
//циклични списъци. може да се направи и итеративно
void free(node* list, node* init) {
  if (!list || list==init)
    return;

  free(list->next,init);
  delete list;
}

void print(node* list) {
  if (!list) return;

  std::cout << list->data << ' ';
  node* begin = list;
  list = list->next;
  while (list && list != begin) {
    std::cout << list->data << ' ';
    list = list->next;
  }
}

node* createCycle(int x, node*& start) {
  if (!start) return start;

  node* rest = nullptr;
  if (start->data > x) {
    rest = start;
    start = new node(x);
    return rest;
  }

  node* tmp = start;
  while (tmp->next && tmp->next->data <= x) {
    tmp = tmp->next;
  }

  rest = tmp->next;
  tmp->next = new node(x,start);
  return rest;
}

int main() {

  node* list1 = fromVector({1,0,5,4,8});
  node* rest1 = createCycle(0,list1); 

  print(list1);
  std::cout << '\n';
  print(rest1);


  free(list1);
  if (list1!=rest1)
    free(rest1);

  return 0;
}