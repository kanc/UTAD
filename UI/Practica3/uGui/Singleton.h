#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <class T> class Singleton
{
public:
	static T& instance()
	{
		static T laInstanciaSingleton;
		return laInstanciaSingleton;
	}
};

#endif // _SINGLETON_H_