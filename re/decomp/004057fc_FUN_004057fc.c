// FUN_004057fc @ 004057fc size=145 sig=undefined FUN_004057fc() cc=unknown
// callers: 
// callees: sprintf,DebugMessage
// strings: \"Job Type: %s\"|\"    Minister: %s\"|\"    Priority: %d\"

void FUN_004057fc(int param_1)

{
  int *piVar1;
  undefined1 local_84 [128];
  
  for (piVar1 = (int *)(&DAT_00522294)[param_1 * 0x11]; piVar1 != (int *)0x0;
      piVar1 = (int *)piVar1[5]) {
    sprintf(local_84,s_Job_Type___s_004b610e,(&PTR_s_NULL_JOB_004b5fe8)[*piVar1]);
    DebugMessage(local_84);
    sprintf(local_84,s_Minister___s_004b611b,(&PTR_s_DEFENSE_MIN_004b5fd0)[piVar1[1]]);
    DebugMessage(local_84);
    sprintf(local_84,s_Priority___d_004b612c,piVar1[2]);
    DebugMessage(local_84);
  }
  return;
}

