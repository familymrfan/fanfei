#if !defined RES_H
#define RES_H

class ResString
{
	enum { MAX_RESSTRING = 255 };
public:
	ResString (HINSTANCE hInst, int resId){
		::LoadString (hInst, resId, buf_, MAX_RESSTRING + 1);
	}
	operator wchar_t const * () const { return buf_; }
private:
	wchar_t buf_ [MAX_RESSTRING + 1];
};

class ResIcon
{
	enum { MAX_RESSTRING = 255 };
public:
	ResIcon (HINSTANCE hInst, int resId){
		hion_ = ::LoadIcon(hInst,MAKEINTRESOURCE(resId));
	}
	operator HICON () const { return hion_; }
private:
	HICON hion_;
};

#endif