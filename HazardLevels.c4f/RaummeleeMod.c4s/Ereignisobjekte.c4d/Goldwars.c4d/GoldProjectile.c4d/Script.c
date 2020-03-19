#strict
#include _GVK

Hit:
  Local(0)=0;
  Local(1)=0;
  return(1);
  
/* Fliegt */
Travel:
  // Bewegung
  if(Local(0))
    SetXDir(Local(0));
  if(Local(1))
    SetYDir(Local(1));
  return(1);
