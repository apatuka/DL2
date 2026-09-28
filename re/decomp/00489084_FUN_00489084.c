// FUN_00489084 @ 00489084 size=213 sig=undefined FUN_00489084() cc=unknown
// callers: FUN_00438b9c,FUN_004397a0
// callees: FUN_004a6964,FindFirstFileA,FUN_0048f774,FUN_004a68dc

bool FUN_00489084(CHAR *param_1,undefined4 param_2,undefined1 *param_3)

{
  char *pcVar1;
  HANDLE pvVar2;
  char *pcVar3;
  char *pcVar4;
  CHAR local_54 [80];
  
  FUN_0048f774(param_3,0x248,0);
  pcVar1 = param_1 + -1;
  do {
    pcVar1 = pcVar1 + 1;
  } while (*pcVar1 != '\0');
  do {
    pcVar1 = pcVar1 + -1;
    if (((pcVar1 < param_1) || (*pcVar1 == ':')) || (*pcVar1 == '/')) break;
  } while (*pcVar1 != '\\');
  pcVar4 = param_3 + 2;
  do {
    pcVar1 = pcVar1 + 1;
    if (*pcVar1 == '\0') {
      param_3[1] = 0;
      FUN_004a6964(local_54,param_1);
      FUN_004a68dc(local_54,&DAT_0051b5f0);
      *pcVar4 = '.';
      pcVar4[1] = '*';
      pcVar3 = pcVar4 + 2;
      param_1 = local_54;
LAB_00489125:
      *pcVar3 = '\0';
      pvVar2 = FindFirstFileA(param_1,(LPWIN32_FIND_DATAA)(param_3 + 0x106));
      *(HANDLE *)(param_3 + 0x244) = pvVar2;
      if (*(int *)(param_3 + 0x244) != -1) {
        *param_3 = 1;
      }
      return *(int *)(param_3 + 0x244) != -1;
    }
    if (*pcVar1 == '.') {
      param_3[1] = 1;
      for (pcVar3 = pcVar4; (*pcVar1 != '\0' && (pcVar3 < pcVar4 + 4)); pcVar3 = pcVar3 + 1) {
        *pcVar3 = *pcVar1;
        pcVar1 = pcVar1 + 1;
      }
      goto LAB_00489125;
    }
    if (pcVar4 < param_3 + 10) {
      *pcVar4 = *pcVar1;
      pcVar4 = pcVar4 + 1;
    }
  } while( true );
}

