// FUN_00484864 @ 00484864 size=104 sig=undefined FUN_00484864() cc=unknown
// callers: FUN_00484980,FUN_004848cc
// callees: SetDlgItemInt,GetDlgItemInt

UINT FUN_00484864(HWND param_1)

{
  int iVar1;
  UINT UVar2;
  UINT UVar3;
  BOOL local_8;
  
  UVar2 = GetDlgItemInt(param_1,0xc9,&local_8,0);
  iVar1 = DAT_0065e018;
  if (*(char *)(DAT_0065e01c + 0x20) != *(char *)(DAT_0065e020 + 0x20)) {
    UVar3 = GetDlgItemInt(param_1,0xb,&local_8,0);
    iVar1 = UVar3 + DAT_0065e018;
  }
  SetDlgItemInt(param_1,0xc,UVar2 * iVar1,0);
  return UVar2 * iVar1;
}

