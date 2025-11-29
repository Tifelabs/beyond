#include <iostream>
#include <string>

struct node {
   int data;
   struct node *next;
};
struct node *head = NULL;
struct node *current = NULL;


void DisplayList(){
   struct node *p = head;
   std::cout << "\n[";
   
   /* starting from beginning */
   while(p != NULL) {
      std::cout << " " << p->data << " ";
      p = p->next;
   }
   std::cout << "]";
}

//insertion at the beginning
void InsertAtBegin(int data){
   
   /* New Link */
   struct node *lk = (struct node*) malloc(sizeof(struct node));
   lk->data = data;
   
   /* Pointing to first node */
   lk->next = head;
   
   /* Pointing to the new first node */
   head = lk;
}
int main(){
   InsertAtBegin(40);
   InsertAtBegin(23);
   InsertAtBegin(15);
   InsertAtBegin(99);
   InsertAtBegin(17);
   std::cout << "Linked List: ";
   
   DisplayList();
}
