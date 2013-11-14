#ifndef UGINE_LIST_H
#define UGINE_LIST_H

#include "array.h"
#include <stdlib.h>

template <typename T>
class List {
public:
    // Inner Node class
    class Node 
	{
		public:
			friend class List<T>;
			Node(List<T>* list, Node* prevNode, const T& value);
			Node* Next() { return next; }
			const Node* Next() const { return next; }
			void Set(const T& val) { value = val; }
			T& Value() { return value; }
			const T& Value() const { return value; }
		private:
	        T value;
			Node* next;
	};

	List() : m_pFirst(NULL), m_pLast(NULL), m_iSize(0) {}
    ~List();

    int Size() const; //done
    bool IsEmpty() const; //done 
    Node* Add(const T& val); //donde 
    Node* InsertBefore(const Node* node, const T& val);
    Node* InsertAfter(Node* node, const T& val); //done
    Node* First(); //donde
    Node* Last(); //done
    const Node* First() const;
    const Node* Last() const;
    void Remove(Node* node); //done
    void Remove(const T& obj); //done
    void Clear();
    Array<T> ToArray();
    void Sort(bool (*compareFunc)(T&, T&));

private:
	Node *m_pFirst;
	Node *m_pLast;
	unsigned int m_iSize;
};

template <typename T>
List<T>::Node::Node(List<T>* list, Node* prevNode, const T& value) : value(value) {
	
	this->value=value;

	//si se pasa el nodo previo...
	if (prevNode!=NULL)
	{	//el siguiente sera el siguiente del nodo pasado
		this->next=prevNode->next;
		
		//y el siguiente del nodo pasado seremos nosotros
		prevNode->next=this;
	}
	else
		this->next=NULL;
	
}

template <typename T>
List<T>::~List() {
	
	Clear();
}

template <typename T>
int List<T>::Size() const {

	return m_iSize;
}

template <typename T>
bool List<T>::IsEmpty() const {

	return !m_iSize;
}

template <typename T>
typename List<T>::Node* List<T>::Add(const T& val) {
	
	List<T>::Node *newNode=new List<T>::Node(this,NULL,val);

	if (m_pLast==NULL)
		m_pFirst= m_pLast = newNode;
	else
	{
		m_pLast->next = newNode;
		m_pLast= m_pLast->Next();
	}
	m_iSize++;

	return newNode;
	
}
template <typename T>
typename List<T>::Node* List<T>::First()
{
	return m_pFirst;
}

template <typename T>
typename List<T>::Node* List<T>::Last()
{
	return m_pLast;
}

template <typename T>
typename List<T>::Node* List<T>::InsertBefore(const Node* node, const T& val) {			
}

template <typename T>
typename List<T>::Node* List<T>::InsertAfter(Node* node, const T& val) {
	
	List<T>::Node *newNode=new List<T>::Node(this,node,val);

	//si insertamos despues del ultimo, el nuevo elemento pasa a serlo
	if (node==m_pLast)
		m_pLast=newNode;

	m_iSize++;

	return newNode;

}

template <typename T>
void List<T>::Remove(Node* node) {

	Node *pNodoIterator;
	Node *pNodoRemove;
	bool nodeRemoved=false;

	if (m_pFirst!=NULL)
	{
		pNodoIterator=m_pFirst;

		//comprobamos el primer elemento
		if (pNodoIterator==node)
		{
			//borramos el primero y apuntamos al siguiente
			m_pFirst=pNodoIterator->next;
			delete pNodoIterator;
			m_iSize--;			

		}
		else //seguimos con el resto
		{
			while (pNodoIterator!=NULL && !nodeRemoved)
			{
				//si el siguiente elemento del que estamos actualmente es el que buscamos
				if (pNodoIterator->next==node)
				{
					//lo asignamos a un puntero temporal
					pNodoRemove=pNodoIterator->next;

					//si es el ultimo elemento marcamos el ultimo como el anterior al que vamos a borrar
					if (pNodoRemove==m_pLast)
					{	m_pLast=pNodoIterator;
						m_pLast->next=NULL;
					}
					else //no es el ultimo, asi que enlazamos con el siguiente al que borramos
						pNodoIterator->next=pNodoRemove->next;

					//borramos
					delete pNodoRemove;
					m_iSize--;
					nodeRemoved=true;
				}
				else //pasamos al siguiente
					pNodoIterator=pNodoIterator->next;
			}
		}

		if (m_iSize==0)
			m_pFirst=m_pLast=NULL;
	}
}

template <typename T>
void List<T>::Remove(const T& obj) {
	Node *pNodoIterator;
	Node *pNodoRemove;
	bool nodeRemoved=false;

	if (m_pFirst!=NULL)
	{
		pNodoIterator=m_pFirst;

		//comprobamos el primer elemento
		if (pNodoIterator->Value()==obj)
		{
			//borramos el primero y apuntamos al siguiente
			m_pFirst=pNodoIterator->next;
			delete pNodoIterator;
			m_iSize--;			

		}
		else //seguimos con el resto
		{
			while (pNodoIterator!=NULL && !nodeRemoved)
			{
				//si el siguiente elemento del que estamos actualmente es el que buscamos
				if (pNodoIterator->next->Value()==obj)
				{
					//lo asignamos a un puntero temporal
					pNodoRemove=pNodoIterator->next;

					//si es el ultimo elemento marcamos el ultimo como el anterior al que vamos a borrar
					if (pNodoRemove==m_pLast)
					{	m_pLast=pNodoIterator;
						m_pLast->next=NULL;
					}
					else //no es el ultimo, asi que enlazamos con el siguiente al que borramos
						pNodoIterator->next=pNodoRemove->next;

					//borramos
					delete pNodoRemove;
					m_iSize--;
					nodeRemoved=true;
				}
				else //pasamos al siguiente
					pNodoIterator=pNodoIterator->next;
			}
		}

		if (m_iSize==0)
			m_pFirst=m_pLast=NULL;
	}
}

template <typename T>
void List<T>::Clear() {
	
	while (m_pFirst!=NULL)
	{
		Node *pNext = m_pFirst->Next();		
		delete m_pFirst;
		m_pFirst = pNext;
	}

	m_pFirst = m_pLast = NULL;
	m_iSize=0;
}

template <typename T>
Array<T> List<T>::ToArray() {
	
	List<T>::Node *pNodo;
	Array<T> nuevoArray=Array<T>(m_iSize);

	pNodo=m_pFirst;

	while (pNodo!=NULL)
	{
		nuevoArray.Add(pNodo->Value());
		pNodo = pNodo->Next();						
	}

	return nuevoArray;
}

template <typename T>
void List<T>::Sort(bool (*compareFunc)(T&, T&)) {

	//otra opcion mas eficiente (con total seguridad jejeje) hubiera sido utilizar la funcion qsort de C pasando la lista a array y utilizando el puntero a funcion 
	//tal como he hecho aqui, lo que pasa es que me hacia ilusion usar el algoritmo de la burbuja por una gracieta personal y creo que el motivo de la practica no era
	//encontrar el algoritmo mas eficiente no? prometo cambiarlo para poder usarla en el resto de asignaturas. De todas formas la linea seria algo del tipo...
	//qsort((void *)&miArray, miArray.Size(), sizeof(T), (int (*)(const void *, const void *))compareFunc); Seguramente nuestro Array no valdria y tendriamos que pasarle un array "standard" Otro problema seria que la funcion qsort requiere que la funcion de comparacion
	//devuelva un entero, por lo que habria que cambiar el parametro que recibimos en esta funcion o sobrecargarla. Tambien queda la opcion de implementar el quicksort sobre la lista, obviamente.

	List<T>::Node *pNodo;	
	T temp;
	bool changed=false;

	pNodo=m_pFirst;

	while (pNodo!=NULL)
	{
		if (pNodo->Next() != NULL)
		{	
			if (compareFunc(pNodo->Value(),pNodo->Next()->Value()))
			{	temp=pNodo->Value();
				pNodo->Set(pNodo->Next()->Value());
				pNodo->Next()->Set(temp);

				changed=true;
			}
		}
		if (changed)
		{	pNodo=m_pFirst;
			changed=false;
		}
		else
			pNodo = pNodo->Next();						
	}
		
}

#endif // UGINE_LIST_H
