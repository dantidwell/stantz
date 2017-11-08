#include <windows.h> 

void InitGraphics(HWND window);
void Draw();

static LRESULT CALLBACK WindowEventCallback(
  _In_ HWND   hwnd,
  _In_ UINT   uMsg,
  _In_ WPARAM wParam,
  _In_ LPARAM lParam
) {
  switch(uMsg) { 
    case WM_PAINT:
      Draw();
      break;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);  
};

int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  WNDCLASSEX WindowClass {
    sizeof(WNDCLASSEX), 
    0,
    &WindowEventCallback, 
    0, 
    0, 
    hInstance,
    NULL,
    NULL, 
    NULL,
    NULL, 
    L"StantzWindowClass", 
    NULL
  };
   
  RegisterClassEx(&WindowClass);
  auto window = CreateWindowEx(
    0,
    L"StantzWindowClass", 
    L"Stantz",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,    
    CW_USEDEFAULT,    
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL, 
    NULL,
    hInstance,
    NULL
  );

  InitGraphics(window);
  ShowWindow(window, nCmdShow);

  /* main message loop */
  MSG windowMessage = {};  
  while(GetMessage(&windowMessage, NULL, 0, 0)) { 
    TranslateMessage(&windowMessage); 
    DispatchMessage(&windowMessage);
  }
  return 0;
}
