//Locals  0Owner   1KI   2Counter
#strict

Initialize:
SetOwner(-1);
SetPosition(0,0);
Start();
return(1);

	Start:
SetAction("Los");
return(1);

	Remove:
Message("Flintregen hat aufgehört!");
return(RemoveObject());

	Explosion:
  SetVar(0,Random(22));
  if(Equal(Var(0),0)) SetVar(0,CreateObject(WBOB,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),1)) SetVar(0,CreateObject(FF4V,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),2)) SetVar(0,CreateObject(FL58,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),3)) SetVar(0,CreateObject(MBOM,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),4)) SetVar(0,CreateObject(JU58,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),5)) SetVar(0,CreateObject(HNTF,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),6)) SetVar(0,CreateObject(JU59,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),7)) SetVar(0,CreateObject(_AUS,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),8)) SetVar(0,CreateObject(_SFN,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),9)) SetVar(0,CreateObject(J102,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),10)) SetVar(0,CreateObject(_RND,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),11)) SetVar(0,CreateObject(MSFL,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),12)) SetVar(0,CreateObject(FLNT,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),13)) SetVar(0,CreateObject(SFLN,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),14)) SetVar(0,CreateObject(TFLN,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),15)) SetVar(0,CreateObject(EFLN,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),16)) SetVar(0,CreateObject(SHFT,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),17)) SetVar(0,CreateObject(_CGM,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),18)) SetVar(0,CreateObject(KAC5,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),19)) SetVar(0,CreateObject(SBOM,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),20)) SetVar(0,CreateObject(KREI,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
  if(Equal(Var(0),21)) SetVar(0,CreateObject(MELO,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100))),-1));
SetXDir(Sub(100,Random(200)),Var(0));
SetYDir(Sub(200,Random(50)),Var(0));
return(1);
