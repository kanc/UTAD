#ifndef _ICONTAINER_H_
#define _ICONTAINER_H_

class IContainer
{
public:
	void addChildControl( Control* control );
	std::list<Control*> getChildrenControls();

protected:
	std::list<Control*>					m_children;
};

#endif // _ICONTAINER_H_
