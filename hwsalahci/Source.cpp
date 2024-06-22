// doublyLinked.cpp
// demonstrates circular doubly-linked list
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////
class Link
{
public:
  double Data; // data item
  Link *Next;  // next link in list
  Link *Prev;  // previous link in list
public:
  //-------------------------------------------------------------
  Link(double d) : // constructor
                   Data(d), Next(NULL), Prev(NULL)
  {
  }
  //------------------------------------------------------------
  void displayLink() // display this link
  {
    cout << Data << "  ";
  }
  //------------------------------------------------------------
}; // end class Link
////////////////////////////////////////////////////////////////
class CircularDoublyLinkedList
{
private:
  Link *Head; // pointer to first item
  Link *Tail; // pointer to last item
public:
  //------------------------------------------------------------
  CircularDoublyLinkedList() : // constructor
                               Head(NULL), Tail(NULL)
  {
  }
  //------------------------------------------------------------
  ~CircularDoublyLinkedList()
  {                     // destructor (deletes links)
    Link *ptr = Head;   // start at beginning of list
    while (ptr != Tail) // until end of list,
    {
      Link *Old = ptr; // save current link
      ptr = ptr->Next; // move to next link
      delete Old;      // delete old current
    }
    delete ptr;
  }
  //------------------------------------------------------------
  bool isEmpty() // true if no links
  {
    return Head == NULL;
  }
  //------------------------------------------------------------
  void insertFirst(double d) // insert at front of list
  {
    Link *NewLink = new Link(d); // make new link
    if (isEmpty())               // if empty list,
      Tail = NewLink;            // newLink <-- last
    else
    {
      Head->Prev = NewLink; // newLink <-- old first
      NewLink->Next = Head;
    }                  // newLink --> old first
    Head = NewLink;    // first --> newLink
    Tail->Next = Head; // last --> new first
    Head->Prev = Tail; // first <-- old last
  }
  //------------------------------------------------------------
  void insertLast(double d) // insert at end of list
  {
    Link *NewLink = new Link(d); // make new link
    if (isEmpty())               // if empty list,
      Head = NewLink;            // first --> newLink
    else
    {
      Tail->Next = NewLink; // old last --> newLink
      NewLink->Prev = Tail; // old last <-- newLink
    }
    Tail = NewLink;    // newLink <-- last
    Tail->Next = Head; // last --> new first
    Head->Prev = Tail; // first <-- old last
  }
  //------------------------------------------------------------
  void removeFirst() // remove first link
  {                  //(assumes non-empty list)
    if (isEmpty())
      return;
    Link *temp = Head;
    if (Head->Prev == temp) // if only one item //error
      Tail = Head = NULL;   // null <-- last,frist
    else
    {
      Head->Next->Prev = Tail; // last <-- old next
      Head = Head->Next;       // first --> old next
      Tail->Next = Head;       // last --> new frist
    }
    delete temp; // delete old first
  }
  //------------------------------------------------------------
  void removeLast() // remove last link
  {                 //(assumes non-empty list)
    if (isEmpty())
      return;
    Link *temp = Tail;
    if (Tail->Next == temp) // if only one item
      Tail = Head = NULL;   // first --> null
    else
    {
      Tail->Prev->Next = Head; // old previous --> first
      Tail = Tail->Prev;       // old previous <-- last
      Head->Prev = Tail;       // first <-- neww last
    }
    delete temp; // delete old last
  }
  //------------------------------------------------------------
  bool insertAfter(double key, double d)
  {                   //(assumes non-empty list)
    Link *ptr = Head; // start at beginning
    while (ptr->Data != key)
    {                  // until match is found,
      ptr = ptr->Next; // move to next link
      if (ptr == NULL)
        return false; // didn�t find it
    }
    Link *NewLink = new Link(d); // make new link
    if (ptr == Tail)             // if last link,
    {
      insertLast(d);
      /*NewLink->Next = Head;     //newLink --> First
      Tail->Next=NewLink;        //last --> newLink
      Tail = NewLink;           //newLink <-- last
      Head->Prev=Tail; */
      // first <-- last
    }
    else                         // not last link,
    {                            // newLink --> old next
      NewLink->Next = ptr->Next; // newLink <-- old next
      ptr->Next->Prev = NewLink;
      ptr->Next = NewLink; // old current --> newLink
    }
    NewLink->Prev = ptr; // old current <-- newLink
    return true;         // found it, did insertion
  }
  //------------------------------------------------------------
  bool removeKey(double key) // remove item w/ given key
  {                          //(assumes non-empty list)
    Link *ptr = Head;        // start at beginning
    while (ptr->Data != key) // until match is found,
    {
      ptr = ptr->Next; // move to next link
      if (ptr == NULL)
        return false; // didn�t find it
    }
    if (ptr == Head) // found it; first item?
    {
      removeFirst();
      return 1;
    }                // Head = ptr->Next;  //first --> old next
    if (ptr == Tail) // last item?         //not first //old previous --> old next
    {
      removeLast();
      return 1;
    }                            // Tail = ptr->Prev;  //old previous <-- last
    ptr->Prev->Next = ptr->Next; // not last           //old previous <-- old next
    ptr->Next->Prev = ptr->Prev;
    delete ptr;  // delete item
    return true; // successful deletion
  }
  //------------------------------------------------------------
  void displayForward()
  {
    cout << "List (first-->last): ";
    if (isEmpty())
    {
      cout << "empty\n";
      return;
    }
    Link *ptr = Head;         // start at beginning
    while (ptr->Next != Head) // until end of list,
    {
      ptr->displayLink(); // display data
      ptr = ptr->Next;    // move to next link
    }
    ptr->displayLink();
    cout << endl;
  }
  //------------------------------------------------------------
  void displayBackward()
  {
    cout << "List (last-->first): ";
    if (isEmpty())
    {
      cout << "empty\n";
      return;
    }
    Link *ptr = Tail;         // start at end
    while (ptr->Prev != Tail) // until start of list,
    {
      ptr->displayLink(); // display data
      ptr = ptr->Prev;    // go to previous link
    }
    ptr->displayLink();
    cout << endl;
  }
  //------------------------------------------------------------
}; // end class CircularDoublyLinkedList
////////////////////////////////////////////////////////////////
int main()
{
  CircularDoublyLinkedList theList; // make a new list
  theList.insertFirst(22);          // insert at front
  theList.insertFirst(44);
  theList.insertFirst(66);
  theList.insertLast(11); // insert at rear
  theList.insertLast(33);
  theList.insertLast(55);
  theList.displayForward();  // display list forward
  theList.displayBackward(); // display list backward
  cout << "Deleting first, last, and 11" << endl;
  theList.removeFirst();    // remove first item
  theList.removeLast();     // remove last item
  theList.removeKey(11);    // remove item with key 11
  theList.displayForward(); // display list forward
  cout << "Inserting 77 after 22, and 88 after 33" << endl;
  theList.insertAfter(22, 77); // insert 77 after 22
  theList.insertAfter(33, 88); // insert 88 after 33
  theList.displayForward();    // display list forward
  theList.removeFirst();
  theList.removeFirst();
  theList.removeFirst();
  theList.removeFirst();
  theList.removeFirst();
  theList.removeFirst();
  theList.displayForward();
  system("pause");
  return 0;
} // end main()
