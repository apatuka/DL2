// FUN_00461ff4 @ 00461ff4 size=230 sig=undefined FUN_00461ff4() cc=unknown
// callers: FUN_0045f608
// callees: ReadFile,strlen,FUN_004a6a60
// strings: \"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\\nPre-release version XXXXXXXXXXX\"|\"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\\nPre-release version S (7/21/97)\"|\"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\\nPre-release version T (7/31/97)\"|\"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\\nPre-release version U (8/04/97)\"|\"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\\nPre-release version V (9/05/97)\"

undefined4 FUN_00461ff4(HANDLE param_1,LPVOID param_2,undefined4 *param_3)

{
  BOOL BVar1;
  undefined4 uVar2;
  int iVar3;
  DWORD local_8;
  
  BVar1 = ReadFile(param_1,param_2,0x9c,&local_8,(LPOVERLAPPED)0x0);
  if (BVar1 == 0) {
    uVar2 = 2;
  }
  else {
    uVar2 = strlen(s_Deadlock_2__c_1997_Accolade_Inc__004d1ea0);
    iVar3 = FUN_004a6a60(param_2,s_Deadlock_2__c_1997_Accolade_Inc__004d1ea0,uVar2);
    if (iVar3 == 0) {
      *param_3 = DAT_004d1d3c;
    }
    else {
      iVar3 = FUN_004a6a60(param_2,s_Deadlock_2__c_1997_Accolade_Inc__004d1d40,0x58);
      if (iVar3 == 0) {
        *param_3 = 0;
      }
      else {
        iVar3 = FUN_004a6a60(param_2,s_Deadlock_2__c_1997_Accolade_Inc__004d1d98,0x58);
        if (iVar3 == 0) {
          *param_3 = 1;
        }
        else {
          iVar3 = FUN_004a6a60(param_2,s_Deadlock_2__c_1997_Accolade_Inc__004d1df0,0x58);
          if (iVar3 == 0) {
            *param_3 = 2;
          }
          else {
            iVar3 = FUN_004a6a60(param_2,s_Deadlock_2__c_1997_Accolade_Inc__004d1e48,0x58);
            if (iVar3 != 0) {
              return 2;
            }
            *param_3 = 3;
          }
        }
      }
    }
    if (DAT_004d5ae8 < *(int *)((int)param_2 + 0x58)) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

