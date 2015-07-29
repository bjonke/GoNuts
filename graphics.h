#ifndef GRAPHICS_H
#define GRAPHICS_H

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

class CGraphics
{
private:

	HWND main_window_handle;

public:

	LARGE_INTEGER ticksPerSecond; //frequency
	LARGE_INTEGER tick; // a point in time
	LARGE_INTEGER time;// for converting tick into real time

	LARGE_INTEGER startFrame;
	LARGE_INTEGER stopFrame;
	LARGE_INTEGER nFrames;
	LARGE_INTEGER tickstowait;
	LARGE_INTEGER tickspassed;
	LARGE_INTEGER ticksleft;
	LARGE_INTEGER prev_frame;

	int done;
	bool showmenu;
	bool Splash;
	bool up;
	bool down;
	bool right;
	bool left;
	int col;
	int row;
	int x;
	int y;

	int velocity;

	bool Init(HWND hwnd);
	bool Paint();
	bool Collecting(int x, int y);
	bool SquirrelSick();
	bool FillBag();
	void EmptyBag();
	bool Status();
	bool GameFinished();
	void EraseScreen();
	void Text();
	void Menu();
	bool Input();
	void SplashScreen();
	void RandomTest();

	CGraphics();
	~CGraphics() {};
};
#endif
