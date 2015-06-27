#pragma once


class arRenderer
{
public:
	arRenderer();
	~arRenderer();

	bool init(int hInst, int hWnd);
	void update();
	void free();

private:

};
