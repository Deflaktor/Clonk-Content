#strict


/* Steuerung */

public ControlUp:
  return (Move(COMD_Up()));

public ControlDown:
  return (Move(COMD_Down()));

/* Kontakt */

public ContactTop:
  return(Stop());

public ContactBottom:
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