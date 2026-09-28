// FUN_0048bdb0 @ 0048bdb0 size=114 sig=undefined FUN_0048bdb0() cc=unknown
// callers: FUN_0048be22,FUN_00464b90,FUN_00444398
// callees: GetObjectA,thunk_FUN_0045792c,CreateCompatibleDC,DeleteDC,SelectObject

void FUN_0048bdb0(HANDLE param_1,HDC param_2,undefined4 *param_3,int *param_4,undefined4 param_5)

{
  HDC hdc;
  int iVar1;
  int iVar2;
  undefined1 local_1c [4];
  int local_18;
  int local_14;
  
  hdc = CreateCompatibleDC(param_2);
  GetObjectA(param_1,0x18,local_1c);
  SelectObject(hdc,param_1);
  iVar2 = param_4[3] - param_4[1];
  if (param_4[3] - param_4[1] == 0) {
    iVar2 = local_14;
  }
  iVar1 = param_4[2] - *param_4;
  if (param_4[2] - *param_4 == 0) {
    iVar1 = local_18;
  }
  thunk_FUN_0045792c(param_2,*param_4,param_4[1],iVar1,iVar2,hdc,*param_3,param_3[1],param_5);
  DeleteDC(hdc);
  return;
}

