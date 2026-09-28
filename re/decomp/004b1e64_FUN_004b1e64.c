// FUN_004b1e64 @ 004b1e64 size=234 sig=undefined FUN_004b1e64() cc=unknown
// callers: FUN_004b1fb4
// callees: strlen,GetShortPathNameA,FUN_004a6bf8,FUN_004b0b44

undefined1 * FUN_004b1e64(CHAR *param_1,int param_2,int *param_3)

{
  DWORD DVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  int *piVar5;
  int iVar6;
  CHAR local_108 [260];
  
  if ((param_1 != (LPCSTR)0x0) && (DVar1 = GetShortPathNameA(param_1,local_108,0x104), DVar1 != 0))
  {
    param_1 = local_108;
  }
  iVar6 = 0;
  if (param_1 != (CHAR *)0x0) {
    iVar6 = strlen(param_1);
    iVar6 = iVar6 + 1;
  }
  piVar5 = param_3;
  if (param_2 != 0) {
    iVar2 = strlen(param_2);
    iVar6 = iVar2 + iVar6 + 1;
  }
  for (; *piVar5 != 0; piVar5 = piVar5 + 1) {
    iVar2 = strlen(*piVar5);
    iVar6 = iVar2 + iVar6 + 1;
  }
  puVar3 = (undefined1 *)FUN_004b0b44(iVar6);
  if (puVar3 == (undefined1 *)0x0) {
    puVar3 = (undefined1 *)0x0;
  }
  else {
    puVar4 = puVar3;
    if (param_1 != (CHAR *)0x0) {
      puVar4 = (undefined1 *)FUN_004a6bf8(puVar3,param_1);
      *puVar4 = 0x20;
      puVar4 = puVar4 + 1;
    }
    if (param_2 != 0) {
      puVar4 = (undefined1 *)FUN_004a6bf8(puVar4,param_2);
      *puVar4 = 0x20;
      puVar4 = puVar4 + 1;
    }
    if (param_1 != (CHAR *)0x0) {
      for (; *param_3 != 0; param_3 = param_3 + 1) {
        puVar4 = (undefined1 *)FUN_004a6bf8(puVar4,*param_3);
        *puVar4 = 0x20;
        puVar4 = puVar4 + 1;
      }
    }
    puVar4[-1] = 0;
  }
  return puVar3;
}

