#ifndef KFC_H_
#define KFC_H_

#include"CommonFunction.h"
#include"BaseObject.h"

class kfcobject :public baseobject
{
public:
	enum KFC_
	{
		kfc0,
		kfc1,
		kfc2,
		kfc3
	};

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
	
	void SetKfcType(const int& x)
	{
		kfcType = x;
	}
	int GetKfcType() const { return kfcType; }

	void LoadKfc(SDL_Renderer* renderer);
	void Handle();
private:
	int x_val_;
	int y_val_;
	bool kfcStatus;
	bool is_Run = false;
	int kfcType;
};

#endif

