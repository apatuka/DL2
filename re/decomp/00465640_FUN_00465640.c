// FUN_00465640 @ 00465640 size=176 sig=undefined FUN_00465640() cc=unknown
// callers: CreateMainWindow
// callees: LoadResource,CreateDIBitmap,ReleaseDC,GetDC,memcpy,FindResourceA

HBITMAP FUN_00465640(HWND param_1,LPCSTR param_2)

{
  HMODULE hModule;
  HRSRC hResInfo;
  int *piVar1;
  HDC hdc;
  HBITMAP unaff_EDI;
  BITMAPINFO local_42c [24];
  
  hModule = DAT_0058f19c;
  hResInfo = FindResourceA(DAT_0058f19c,param_2,(LPCSTR)0x2);
  piVar1 = LoadResource(hModule,hResInfo);
  if (piVar1 != (int *)0x0) {
    DAT_0058df48 = (void *)((int)piVar1 +
                           (1 << ((byte)*(undefined2 *)((int)piVar1 + 0xe) & 0x1f)) * 4 + *piVar1);
    memcpy(local_42c,piVar1,0x28);
    memcpy(local_42c[0].bmiColors,&DAT_0051a8a4,0x400);
    hdc = GetDC(param_1);
    unaff_EDI = CreateDIBitmap(hdc,&local_42c[0].bmiHeader,4,DAT_0058df48,local_42c,0);
    ReleaseDC(param_1,hdc);
  }
  return unaff_EDI;
}

