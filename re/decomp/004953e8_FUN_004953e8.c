// FUN_004953e8 @ 004953e8 size=108 sig=undefined FUN_004953e8() cc=unknown
// callers: 
// callees: FUN_004ab474,LoadStringA,MessageBoxA,FUN_00495162

void FUN_004953e8(UINT param_1)

{
  int iVar1;
  CHAR local_804 [1024];
  CHAR local_404 [1024];
  
  iVar1 = LoadStringA(DAT_0065eb98,param_1,local_804,0x400);
  if (iVar1 != 0) {
    FUN_004ab474(local_404,local_804,local_404);
    FUN_00495162(local_404);
    MessageBoxA((HWND)0x0,local_404,(LPCSTR)0x0,0x2010);
  }
  return;
}

