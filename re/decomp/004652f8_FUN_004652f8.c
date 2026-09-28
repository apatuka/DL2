// FUN_004652f8 @ 004652f8 size=84 sig=undefined FUN_004652f8() cc=unknown
// callers: 
// callees: StretchBlt,SelectObject

void FUN_004652f8(HDC param_1,HGDIOBJ param_2,int param_3,int param_4,int param_5,int param_6)

{
  HGDIOBJ h;
  
  h = SelectObject(DAT_0058f1b0,param_2);
  StretchBlt(param_1,0,0,param_3,param_4,DAT_0058f1b0,0,0,param_5,param_6,0xcc0020);
  SelectObject(DAT_0058f1b0,h);
  return;
}

