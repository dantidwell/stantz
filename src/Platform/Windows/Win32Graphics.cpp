#include <windows.h>
#include <gl/gl.h>

static HDC deviceContext; 
static HGLRC openGlContext;
static int screenWidth; 
static int screenHeight;

void InitGraphics(HWND window) {
  deviceContext = GetDC(window);

  PIXELFORMATDESCRIPTOR desiredPixelFormat = {}; 
  PIXELFORMATDESCRIPTOR suggestedPixelFormat = {};

  desiredPixelFormat.nSize = sizeof(desiredPixelFormat); 
  desiredPixelFormat.nVersion = 1; 
  desiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
  desiredPixelFormat.cColorBits = 32; 
  desiredPixelFormat.cAlphaBits = 8; 
  desiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

  auto suggestedFmtIndex = ChoosePixelFormat(deviceContext, &desiredPixelFormat);
  DescribePixelFormat(deviceContext, suggestedFmtIndex, sizeof(suggestedPixelFormat), &suggestedPixelFormat); 
  SetPixelFormat(deviceContext, suggestedFmtIndex, &suggestedPixelFormat);

  openGlContext = wglCreateContext(deviceContext);   
  if(!wglMakeCurrent(deviceContext, openGlContext)) { 
    MessageBox(window, L"Graphics Not Initialized!", L"Notification", MB_OK);
  }

  RECT screen;
  GetClientRect(window, &screen);
  screenWidth = screen.right-screen.left;
  screenHeight = screen.bottom - screen.top;
}

void Draw() {
  glViewport(0, 0, screenWidth, screenHeight); 

  glClearColor(1.0f, 0.0f, 1.0f, 0.0f); 
  glClear(GL_COLOR_BUFFER_BIT); 
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();

  glBegin(GL_TRIANGLES);

  auto v = 0.9f; 

  glColor3f(1.0f, 0, 1.0f);
  glVertex2f(-v, -v);
  glColor3f(1.0f, 1.0f, 0);
  glVertex2f(v, v);
  glColor3f(0, 1.0f, 1.0f);
  glVertex2f(v, -v);

  glColor3f(1.0f, 0, 0);
  glVertex2f(-v, -v);
  glColor3f(0, 1.0f, 0);
  glVertex2f(v, v);
  glColor3f(0, 0, 1.0f);
  glVertex2f(-v, v); 

  glEnd();
  
  SwapBuffers(deviceContext);
}