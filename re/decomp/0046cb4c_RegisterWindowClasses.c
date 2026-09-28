// RegisterWindowClasses @ 0046cb4c size=178 sig=undefined RegisterWindowClasses() cc=unknown
// callers: WinMain
// callees: LoadIconA,LoadCursorA,GetStockObject,RegisterClassExA,memset
// strings: \"XenoMainWnd\"|\"XenoBackground\"|\"XenoIntro\"

/* Registers XenoMainWnd / XenoBackground / XenoIntro */

undefined4 RegisterWindowClasses(HINSTANCE param_1)

{
  WNDCLASSEXA local_34;
  
  memset(&local_34,0,0x30);
  local_34.style = 0x2b;
  local_34.cbWndExtra = 0x10;
  local_34.cbSize = 0x30;
  local_34.hInstance = param_1;
  local_34.hIcon = LoadIconA(param_1,(LPCSTR)0x3);
  local_34.hIconSm = LoadIconA(param_1,(LPCSTR)0x4);
  local_34.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  local_34.hbrBackground = GetStockObject(5);
  local_34.lpfnWndProc = _MainWndProc_qqspvuiuil;
  local_34.lpszClassName = s_XenoMainWnd_004d594c;
  RegisterClassExA(&local_34);
  local_34.lpfnWndProc = _BackWndProc_qqspvuiuil;
  local_34.lpszClassName = s_XenoBackground_004d5958;
  RegisterClassExA(&local_34);
  local_34.lpfnWndProc = _IntroWndProc_qqspvuiuil;
  local_34.lpszClassName = s_XenoIntro_004d5967;
  RegisterClassExA(&local_34);
  return 1;
}

