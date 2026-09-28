// FUN_004b38b0 @ 004b38b0 size=58 sig=undefined FUN_004b38b0() cc=unknown
// callers: FUN_004b382c,FUN_004ac974,FUN_004ab648
// callees: FUN_004b1660,FUN_004a68dc
// strings: \"Semaphore error \"

void FUN_004b38b0(undefined4 param_1)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char local_54 [80];
  
  pcVar2 = s_Semaphore_error_00521890;
  pcVar3 = local_54;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar3 = pcVar3 + 4;
  }
  *pcVar3 = *pcVar2;
  FUN_004a68dc(local_54,param_1);
  FUN_004b1660(local_54);
  return;
}

