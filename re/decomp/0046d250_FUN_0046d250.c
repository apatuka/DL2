// FUN_0046d250 @ 0046d250 size=149 sig=undefined FUN_0046d250() cc=unknown
// callers: WriteUnitData,FUN_0043b8b0,FUN_00417434,SetItemStats,FUN_0041f7f0,FUN_0045a6e4,FUN_0041b500,FUN_0041b330,FUN_00436a44
// callees: 

char * FUN_0046d250(int param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  char local_18;
  char local_17 [15];
  int local_8;
  
  local_8 = 0;
  iVar3 = param_1;
  if (param_1 < 0) {
    iVar3 = -param_1;
  }
  pcVar1 = &local_18;
  pcVar4 = param_2;
  if (param_1 == 0) {
    local_18 = '0';
    pcVar2 = local_17;
  }
  else {
    while (pcVar2 = pcVar1, iVar3 != 0) {
      *pcVar2 = (char)(iVar3 % 10) + '0';
      iVar3 = iVar3 / 10;
      local_8 = local_8 + 1;
      pcVar1 = pcVar2 + 1;
      if ((local_8 == 3) && (iVar3 != 0)) {
        local_8 = 0;
        *pcVar1 = ',';
        pcVar1 = pcVar2 + 2;
      }
    }
    if (param_1 < 0) {
      *pcVar2 = '-';
      pcVar2 = pcVar2 + 1;
    }
  }
  while (pcVar2 = pcVar2 + -1, &local_18 <= pcVar2) {
    *pcVar4 = *pcVar2;
    pcVar4 = pcVar4 + 1;
  }
  *pcVar4 = '\0';
  return param_2;
}

