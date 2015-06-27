#pragma once


class ARRenderer
{
public:
	ARRenderer();
	~ARRenderer();

	bool init(int hInst, int hWnd);
	void update();
	void free();

private:

};
