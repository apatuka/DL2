// FUN_00458640 @ 00458640 size=178 sig=undefined FUN_00458640() cc=unknown
// callers: FUN_00458434
// callees: CGNetSession_FindPlayers,CGNetPlayer_GetName,strlen,FUN_004a6a60
// strings: \"Deadlock 2 Host\"|\"Closed Deadlock 2 Host\"

undefined4 FUN_00458640(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_3c [52];
  int local_8;
  
  *param_1 = 0;
  if (((DAT_004d1708 != 0) && (iVar1 = CGNetSession_FindPlayers(DAT_004d1708,&local_8), 0 < iVar1))
     && (iVar4 = 0, 0 < iVar1)) {
    do {
      iVar2 = CGNetPlayer_GetName(*(undefined4 *)(local_8 + iVar4 * 4),local_3c,0x32);
      if (0 < iVar2) {
        uVar3 = strlen(s_Deadlock_2_Host_004d172c);
        iVar2 = FUN_004a6a60(local_3c,s_Deadlock_2_Host_004d172c,uVar3);
        if (iVar2 == 0) {
LAB_004586d3:
          *param_1 = *(undefined4 *)(local_8 + iVar4 * 4);
          return 1;
        }
        uVar3 = strlen(s_Closed_Deadlock_2_Host_004d173c);
        iVar2 = FUN_004a6a60(local_3c,s_Closed_Deadlock_2_Host_004d173c,uVar3);
        if (iVar2 == 0) goto LAB_004586d3;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < iVar1);
  }
  return 0;
}

