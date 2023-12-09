//#include"List.h"
//
//
//
//template<typename T> List<T>::List()
//{
//    fRoot = nullptr;
//    fCount = 0;
//}
//
////copy constructor
//
//template<typename T> List<T>::List(const List& aOtherList)
//{
//    fRoot = nullptr;
//    fCount = 0;
//
//    Node* otherNode = aOtherList.fRoot;
//    while (otherNode != nullptr) 
//    {
//        push_back(otherNode->getPayload());
//        otherNode = otherNode->getNext();
//    }
//}
//
//
//
//template<typename T> List<T>::~List()
//{
//    Node* current_node = fRoot;
//    while (current_node != nullptr) {
//        Node* next_node = current_node->getNext();
//        delete current_node;
//        current_node = next_node;
//    }
//}
//
//
//// overloading the assignment operator to make a copy of an object
//// end goal is to leave the aOtherList unchanged.
//
//template<typename T> List<T>& List<T>::operator=(const List& aOtherList)
//{
//    
//    if (this != &aOtherList) // prevent self-assignment
//    {
//
//        while (fRoot != nullptr) 
//        {
//            //constantly removing data in the destiniation list, move to root to next before deleting the later.
//            Node* next_node = fRoot->getNext();
//            delete fRoot;
//            fRoot = next_node;
//        }
//       
//        //copy data from data source list->dest list
//        Node* otherNode = aOtherList.fRoot;
//        while (otherNode != nullptr) 
//        {
//            // use getPayLoad method to copy the value instead of whole node
//            this->push_back(otherNode->getPayload());
//            otherNode = otherNode->getNext();
//        }
//    }
//
//    
//    return *this;
//}
//
//
//
//
//template<typename T> bool List<T>::isisEmpty() const
//{
//	return fCount == 0;
//}
//
//
//
//template<typename T> size_t List<T>::size() const
//{
//	return fCount;
//}
//
//
//template<typename T> void List<T>::push_front(const T& aElement)
//{
//    Node* new_node = new Node(aElement);
//
//    // If list is isEmpty, make the new node as the root of the list.
//    if (fRoot == nullptr) 
//    {
//        fRoot = new_node;
//    }
//    // else add the new node at the front of the list.
//    else
//    {
//        fRoot->push_front(*new_node);
//    }
//    fCount++;
//}
//
//// same story as push_front but we push the new node at the end of the list instead
//
//template<typename T> void List<T>::push_back(const T& aElement) {
//    Node* new_node = new Node(aElement);
//    if (fRoot == nullptr) 
//    {
//        fRoot = new_node;
//    }
//    else {
//        fRoot->push_back(*new_node);
//    }
//    fCount++;
//}
//
////template<typename T>
//void List<T>::remove(const T& aElement)
//{
//    Node* current_node = fRoot;
//    Node* prev_node = nullptr;   
//    // iterate all of the elements in list to find the matching element
//    while (current_node != null)
//    {
//        //compare the current node value to the desired element for removal
//        if (current_node->getPayload() == aElement)
//        {
//            // we cant remove the root node, so have to set root value to the fnext pointer
//            if (current_node == fRoot)
//            {
//                fRoot = current_node->getNext();
//            }
//          
//            //isolate, terminate and decrease the count
//            currentNode->isolate();
//            delete currentNode;
//            fCount--;
//            return;
//        }
//
//        // Move to the next node
//        prev_node = current_node;
//        current_node = current_node->getNext();
//    }
//
//}
//
//
//
//// List indexer
//template<typename T>
//const T& List<T>::operator[](size_t aIndex) const {
//   
//}
//
//// Return a forward iterator
//template<typename T>
//typename List<T>::Iterator List<T>::begin() const {return Iterator(fRoot).begin();}
//
//// Return a forward end iterator
//template<typename T>
//typename List<T>::Iterator List<T>::end() const {return Iterator(fRoot).end();}
//
//// Return a backwards iterator
//template<typename T>
//typename List<T>::Iterator List<T>::rbegin() const {return Iterator(fRoot).rbegin();}
//
//// Return a backwards end iterator
//template<typename T>
//typename List<T>::Iterator List<T>::rend() const {return Iterator(fRoot).rend();}
//
//// Move constructor
//template<typename T>
//List<T>::List(List&& aOtherList) : fRoot(aOtherList.fRoot), fCount(aOtherList.fCount) 
//{
//    aOtherList.fRoot = nullptr;
//    aOtherList.fCount = 0;
//}
//
//
//// overloading the assignment operator to actually move the data
//// end goal is to leave the aOtherList data changed, root will be null and fCount=0
//template<typename T>
//List<T>& List<T>::operator=(List&& aOtherList) 
//{
//    if (this != &aOtherList) {
//        delete fRoot;
//
//        fRoot = aOtherList.fRoot;
//        fCount = aOtherList.fCount;
//
//        aOtherList.fRoot = nullptr;
//        aOtherList.fCount = 0;
//    }
//
//    return *this;
//}
//
//// Adds aElement at front
//template<typename T>
//void List<T>::push_front(T&& aElement) 
//{
//    Node* newNode = new Node(std::move(aElement));
//    if (fRoot == nullptr) 
//    {
//        fRoot = newNode;
//    }
//    else 
//    {
//        newNode->push_front(*fRoot);
//        fRoot = newNode;
//    }
//    fCount++;
//}
//
//// Adds aElement at back
//template<typename T>
//void List<T>::push_back(T&& aElement) {
//    Node* newNode = new Node(std::move(aElement));
//    if (fRoot == nullptr) {
//        fRoot = newNode;
//    }
//    else {
//        fRoot->push_back(*newNode);
//    }
//    fCount++;
//}
//
//
