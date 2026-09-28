// FUN_0049539b @ 0049539b size=77 sig=undefined FUN_0049539b() cc=unknown
// callers: FUN_00498826,FUN_0048e5f8,FUN_0046fc70,FUN_0046fae4
// callees: FUN_004ab474,MessageBoxA,FUN_00495162

void FUN_0049539b(int param_1)

{
  CHAR local_404 [1024];
  
  if (param_1 != 0) {
    FUN_004ab474(local_404,param_1,&stack0x00000008);
    FUN_00495162(local_404);
    MessageBoxA((HWND)0x0,local_404,(LPCSTR)0x0,0x2010);
  }
  return;
}

