#pragma once


class ARRenderer
{
public:
	ARRenderer();
	~ARRenderer();

	virtual bool init(int hInst, int hWnd);
	virtual void update();
	virtual void free();

private:

};
