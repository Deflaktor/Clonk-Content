/*-- Neues Script --*/

#strict
#appendto HK00



Initialize:
  var rand=Random(20);
  Local(0)=CreateContents(_REV);
  if(rand==0)
    Local(1)=CreateContents(GB02);
  if(rand==1)
    Local(1)=CreateContents(DR1D);
  if(rand==2)
    Local(1)=CreateContents(_BLZ);
  if(rand==3)
    Local(1)=CreateContents(_DG6);
  if(rand==4)
    Local(1)=CreateContents(_EGW);
  if(rand==5)
    Local(1)=CreateContents(GB01);
  if(rand==6)
    Local(1)=CreateContents(HLS_);
  if(rand==7)
    Local(1)=CreateContents(_PR4);
  if(rand==8&&!Random(5))
    Local(1)=CreateContents(_QRD);
  if(rand==9)
    Local(1)=CreateContents(_SG1);
  if(rand==10)
    Local(1)=CreateContents(SCG2);
  if(rand>=11)
    Local(1)=CreateContents(_WP4);
  return(_inherited());

Death:
  CreateObject(_GVK);
  if(Local(0)) RemoveObject(Local(0));
  if(Local(1)) RemoveObject(Local(1));
  return(_inherited());

SetEnemy:
  target=FindTarget(0,0,-1,-1);
  return(target);