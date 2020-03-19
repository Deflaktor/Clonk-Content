#strict

Completion:
  SetAction("Exist");
  SetComDir(COMD_Stop());
  return(1);
Die:
  AssignRemoval();
  return(1);
