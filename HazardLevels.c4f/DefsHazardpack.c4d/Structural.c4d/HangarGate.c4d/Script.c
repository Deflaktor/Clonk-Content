#strict


/* Steuerung */

public ControlLeft:
  return (Move(COMD_Left()));

public ControlRight:
  return (Move(COMD_Right()));

/* Kontakt */

protected ContactLeft:
  return(Stop());

protected ContactRight:
  return(Stop());

/* Kommandos */

private Move:
  Sound("HangarOpen");
  SetAction("Travel");
  SetComDir(Par(0));
  SetYDir(0);
  return(1);  

private Stop:
  Sound("HangarClose");
  SetAction("Hold");
  SetComDir(COMD_Stop());
  SetXDir(0); SetYDir(0);
  return(1);

/* Initialisierung */

protected Initialize:
  SetAction("Hold");
  return(1);