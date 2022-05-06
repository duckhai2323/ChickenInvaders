#include"kfc.h"

kfcobject::kfcobject()
{

	x_val_ = 0;
	y_val_ = 0;
	kfcStatus = false;
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