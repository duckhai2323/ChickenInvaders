#ifndef KFC_H_
#define KFC_H_

#include"CommonFunction.h"
#include"BaseObject.h"

class kfcobject :public baseobject
{
public:
	kfcobject();
	~kfcobject();

	void SetXY_val(const int& x, const int& y)
	{
		x_val_ = x;
		y_val_ = y;
	}
	void SetKfcStatus(const bool& status)
	{
		kfcStatus = status;
	}
	bool GetStatus() const { return kfcStatus; }

	void Handle();
private:
	int x_val_;
	int y_val_;
	bool kfcStatus;
};

#endif

