#if !defined CANVAS_H
#define  CANVAS_H

#include <windows.h>
#include <string>
#include <D2D1.h>

class Canvas
{
public:
    virtual void DrawRect(int x,int y,int width,int height,COLORREF color = RGB(0,0,0)) = 0;
};

class PaintCanvas :public Canvas
{
public:
    PaintCanvas(HWND hwnd)
        :hwnd_(hwnd) {
        hdc_ = ::BeginPaint(hwnd_,&ps_);
    }

    virtual void DrawRect(int x,int y,int width,int height,COLORREF color = RGB(0,0,0)) override{
        auto brush = ::CreateSolidBrush(color);
        auto old_brush = ::SelectObject(hdc_,brush);
        ::Rectangle (hdc_, x, y, x + width, y + height);
        ::SelectObject(hdc_,old_brush);
        ::DeleteObject(brush);
    }

    ~PaintCanvas(){
        ::EndPaint(hwnd_,&ps_);
    }
private:
    HDC hdc_;
    PAINTSTRUCT ps_;
    HWND hwnd_;
};

class D2DCanvas :public Canvas
{
public:
    D2DCanvas(HWND hwnd)
        :hwnd_(hwnd) {
        CreateD2DTarget();
        pRenderTarget->BeginDraw() ;
        // Clear background color white
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
    }

    ~D2DCanvas(){
        pRenderTarget->EndDraw() ;
        pRenderTarget->Release();
        pBlackBrush->Release();
        pD2DFactory->Release();
    }

    virtual void DrawRect(int x,int y,int width,int height,COLORREF color = RGB(0,0,0)) override{
        CreateD2DBrush();

        pRenderTarget->DrawRectangle(
                  D2D1::RectF(100.f, 100.f, 500.f, 500.f),
                  pBlackBrush);
    }
protected:
    void CreateD2DTarget() {
        HRESULT hr ;
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory) ;
        if (FAILED(hr))
        {
            MessageBox(hwnd_, L"Create D2D factory failed!", L"Error", 0) ;
            return ;
        }

        RECT rc;
        GetClientRect(hwnd_,&rc);
        hr = pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hwnd_, 
            D2D1::SizeU(rc.right - rc.left,rc.bottom - rc.top)), 
            &pRenderTarget);
        if (FAILED(hr)) {
            MessageBox(hwnd_, L"Create render target failed!", L"Error", 0) ;
            return ;
        }
    }

    void CreateD2DBrush() {
        HRESULT hr ;
        // Create a brush
        hr = pRenderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Red),
            &pBlackBrush
                ) ;
        if (FAILED(hr)) {
            MessageBox(hwnd_, L"Create brush failed!", L"Error", 0) ;
            return ;
        }
    }
private:
    ID2D1Factory* pD2DFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pBlackBrush;

    HWND hwnd_;
};

#endif // define CANVAS_H