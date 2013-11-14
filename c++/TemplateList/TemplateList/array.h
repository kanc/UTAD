#ifndef UGINE_ARRAY_H
#define UGINE_ARRAY_H

#define CAPACITY_INC 16

template <typename T>
class Array {
public:
    Array(unsigned int initialCapacity = 0);
    ~Array();

    T& operator[](unsigned int pos);
    const T& operator[](unsigned int pos) const;

    int Size() const { return m_iInsertedElements; }
    void Add(const T& elem);
    void Set(unsigned int index, const T& elem);
    T& Last();
    const T& Last() const;
    void RemoveLast();
    void RemoveAt(unsigned int index);
    void Remove(const T& elem);
    void RemoveEach(const T& elem);
    void Clear();

private:
	T *m_elements;
	unsigned int m_iFinalCapacity;
	unsigned int m_iInsertedElements;
	void OrganizeElements();
	void ResizeMem();
};

template <typename T>
Array<T>::Array(unsigned int initialCapacity) {

	if (initialCapacity==0)
	{	m_elements=new T[CAPACITY_INC];
		m_iFinalCapacity=CAPACITY_INC;
	}
	else
	{	m_elements=new T[initialCapacity];
		m_iFinalCapacity=initialCapacity;
	}

	m_iInsertedElements=0;
}

template <typename T>
Array<T>::~Array() {

	m_elements=NULL;
	delete[] m_elements;
}

template <typename T>
T& Array<T>::operator[](unsigned int pos) {
	
	if (pos >=0 && pos < m_iInsertedElements)			
		return m_elements[pos];	
	else
		return m_elements[m_iInsertedElements-1]; //devolvemos el ultimo porque al no saber el tipo de antemano no sabemos no que podemos devolver si null o 0 o que...
}

template <typename T>
const T& Array<T>::operator[](unsigned int pos) const {
	
	if (pos >=0 && pos < m_iFinalCapacity)	
		return m_elements[pos];	
	else
		return m_elements[m_iInsertedElements-1]; //devolvemos el ultimo 
}

template <typename T>
void Array<T>::Add(const T& elem) {

	if (m_iInsertedElements == m_iFinalCapacity)
		ResizeMem();

		m_elements[m_iInsertedElements]=elem;
		m_iInsertedElements++;

}

template <typename T>
void Array<T>::Set(unsigned int index, const T& elem) {
	
	if (index >=0 && index < m_iFinalCapacity)
	{
		m_elements[index]=elem;
	}
}

template <typename T>
void Array<T>::RemoveAt(unsigned int index) {

	if (index >=0 && index < m_iFinalCapacity)
	{		
		m_elements[index]=NULL;
		OrganizeElements();
		m_iInsertedElements--;
	}
}

template <typename T>
void Array<T>::Remove(const T& elem) {
//no entiendo muy bien la funcionalidad de este metodo... borra el primero que encuentre?
	
	for (unsigned int i=0; i< m_iInsertedElements;i++)	
		if (m_elements[i]==elem) //esto no funcionara si el tipo no tiene implementado el operador ==
		{	RemoveAt(i);			
			break;
		}
}

template <typename T>
void Array<T>::RemoveEach(const T& elem) {

	unsigned int deleted=0;

	for (unsigned int i=0; i< m_iInsertedElements;i++)	
		if (m_elements[i]==elem) //esto no funcionara si el tipo no tiene implementado el operador ==		
		{
			m_elements[i]=NULL;
			deleted++;
		}

	OrganizeElements();
	m_iInsertedElements-=deleted;
	
}

template <typename T>
void Array<T>::Clear() {
	
	//no tengo muy claro que funcione... si guardamos objetos no habria que hacer el delete?? pero si no son objetos no podemos hacer delete....
	for (unsigned int i=0; i < m_iInsertedElements; i++)			
		m_elements[i]=NULL;	

	m_iInsertedElements=0;
}

template <typename T>
void Array<T>::OrganizeElements() {
		
	for (unsigned int i=0; i < m_iInsertedElements; i++)
	{
		unsigned int next;

		//con esto evitamos acceder fuera de los limites de nuestra memoria
		if(m_elements[i]==NULL && (i+1) < m_iInsertedElements)
		{			
			next=i;

			for (next;next < m_iInsertedElements; next++)
				if (m_elements[next] != NULL)
					break;

			m_elements[i]=m_elements[next];
			m_elements[next]=NULL;

		}
	}

}

template <typename T>
void Array<T>::ResizeMem() {

	//pedimos memoria
	T *newArray= new T[m_iFinalCapacity + CAPACITY_INC];

	//actualizamos el tamaño 
	m_iFinalCapacity+=CAPACITY_INC;

	//copiamos el contenido al nuevo array
	for (unsigned int i=0; i<m_iInsertedElements; i++)	
		newArray[i]=m_elements[i];
	
	//borramos el array
	delete[] m_elements;
	
	//le decimos que apunte al nuevo que hemos creado
	m_elements=newArray;

}

template <typename T>
T& Array<T>::Last(){
	
	//aqui tengo un problema, si no hay elementos no se que devolver... si es un array de enteros (por ejemplo) no puedo devolver null
	return m_elements[m_iInsertedElements-1];
}

template <typename T>
const T& Array<T>::Last() const{
	
	//aqui tengo un problema, si no hay elementos no se que devolver... si es un array de enteros (por ejemplo) no puedo devolver null
	return m_elements[m_iInsertedElements-1];
}

template <typename T>
void Array<T>::RemoveLast(){

	if (m_iInsertedElements > 0)
		RemoveAt(m_iInsertedElements-1);
}

#endif // UGINE_ARRAY_H
