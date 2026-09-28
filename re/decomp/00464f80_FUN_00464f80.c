// FUN_00464f80 @ 00464f80 size=240 sig=undefined FUN_00464f80() cc=unknown
// callers: FUN_004655b0,FUN_00465070,FUN_00457bec,FUN_00464a3c,FUN_00465164
// callees: FUN_00458bb0,MoveToEx,CreatePen,LineTo,GetStockObject,SelectObject

void FUN_00464f80(HDC param_1,int *param_2,int param_3)

{
  HPEN h;
  HGDIOBJ pvVar1;
  HGDIOBJ h_00;
  HPEN local_10;
  
  if (param_3 == 0) {
    local_10 = GetStockObject(6);
    h = CreatePen(0,0,0x4b4b4b);
  }
  else {
    local_10 = CreatePen(0,0,0x4b4b4b);
    h = GetStockObject(6);
  }
  pvVar1 = GetStockObject(5);
  pvVar1 = SelectObject(param_1,pvVar1);
  h_00 = SelectObject(param_1,local_10);
  MoveToEx(param_1,*param_2,param_2[3] + -1,(LPPOINT)0x0);
  LineTo(param_1,*param_2,param_2[1]);
  LineTo(param_1,param_2[2] + -1,param_2[1]);
  SelectObject(param_1,h);
  LineTo(param_1,param_2[2] + -1,param_2[3] + -1);
  LineTo(param_1,*param_2,param_2[3] + -1);
  SelectObject(param_1,pvVar1);
  SelectObject(param_1,h_00);
  if (param_3 == 0) {
    FUN_00458bb0(h);
  }
  else {
    FUN_00458bb0(local_10);
  }
  return;
}

