#ifndef _MESSAGE_H_
#define _MESSAGE_H_

enum eMessageType
{
	mtPointerMove,
	mtPointerButtonDown,
	mtPointerButtonUp,
	mtKeyDown,
	mtKeyUp
};

struct Message
{
	eMessageType type;
};

struct MessagePointerMove : public Message
{
	MessagePointerMove() 
	{ 
		type = mtPointerMove; 
	}

	MessagePointerMove( float _x, float _y) 
	{ 
		type = mtPointerMove;
		x = _x;
		y = _y;
	}

	float x;
	float y;
};

struct MessagePointerButtonDown : public Message
{
	MessagePointerButtonDown() 
	{ 
		type = mtPointerButtonDown; 
	}

	MessagePointerButtonDown( int _buttonId, float _x, float _y ) 
	{ 
		type = mtPointerButtonDown;
		buttonId = _buttonId;
		x = _x;
		y = _y;

	}

	int buttonId;
	float x;
	float y;
};

struct MessagePointerButtonUp : public Message
{
	MessagePointerButtonUp() 
	{ 
		type = mtPointerButtonUp; 
	}

	MessagePointerButtonUp( int _buttonId, float _x, float _y ) 
	{ 
		type = mtPointerButtonUp; 
		buttonId = _buttonId;
		x = _x;
		y = _y;
	}

	int buttonId;
	float x;
	float y;
};

struct MessageKeyDown : public Message
{
	MessageKeyDown() 
	{ 
		type = mtKeyDown; 
	}

	MessageKeyDown( int _keyCode ) 
	{ 
		type = mtKeyDown; 
		keyCode = _keyCode;
	}

	int keyCode;
};

struct MessageKeyUp : public Message
{
	MessageKeyUp() 
	{ 
		type = mtKeyUp; 
	}

	MessageKeyUp( int _keyCode ) 
	{ 
		type = mtKeyUp; 
		keyCode = _keyCode;
	}

	int keyCode;
};

#endif // _MESSAGE_H_
