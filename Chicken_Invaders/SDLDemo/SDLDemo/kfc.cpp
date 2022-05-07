#include"kfc.h"

kfcobject::kfcobject()
{

	x_val_ = 0;
	y_val_ = 0;
	kfcStatus = false;
	kfcType = kfc0;
}

kfcobject::~kfcobject()
{

}

void kfcobject::Handle()
{
	rect_.y += y_val_;
	if (rect_.y >= WINDOW_HEIGHT)
	{
		kfcStatus = false;
	}
}

void kfcobject::LoadKfc(SDL_Renderer* renderer)
{
	if (kfcType == kfc0)
	{
		LoadImage("kfc0.png", renderer);
	}
	else if (kfcType == kfc1)
	{
		LoadImage("kfc1.png", renderer);
	}
	else if (kfcType == kfc2)
	{
		LoadImage("kfc2.png", renderer);
	}
	else if (kfcType == kfc3)
	{
		LoadImage("kfc3.png", renderer);
	}
}