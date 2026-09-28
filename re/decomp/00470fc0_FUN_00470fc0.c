// FUN_00470fc0 @ 00470fc0 size=104 sig=undefined FUN_00470fc0() cc=unknown
// callers: FUN_00471068,FUN_00471028,FUN_00471634,FUN_00471170,FUN_004719a0
// callees: GetPrivateProfileStringA

undefined4 FUN_00470fc0(LPCSTR param_1,LPCSTR param_2,char *param_3,DWORD param_4,LPCSTR param_5)

{
  char *pcVar1;
  DWORD DVar2;
  undefined4 uVar3;
  char *pcVar4;
  bool bVar5;
  
  DVar2 = GetPrivateProfileStringA(param_1,param_2,&DAT_004d6326,param_3,param_4,param_5);
  pcVar4 = &DAT_004d6326;
  do {
    if (*param_3 != *pcVar4) goto LAB_0047100f;
    bVar5 = true;
    if (*param_3 == '\0') break;
    pcVar1 = param_3 + 1;
    if (*pcVar1 != pcVar4[1]) goto LAB_0047100f;
    param_3 = param_3 + 2;
    pcVar4 = pcVar4 + 2;
    bVar5 = *pcVar1 == '\0';
  } while (!bVar5);
  if (bVar5) {
    uVar3 = 0;
  }
  else {
LAB_0047100f:
    if (param_4 - 1 == DVar2) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
  }
  return uVar3;
}

