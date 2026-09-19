Program Chamada;
Var nomes      : Array[1..100] Of String[20];
    nomeTemp   : String[20];
    i, j, n, k : Integer;

Procedure ImprimeNomes;
Var i : Integer;
Begin
  For i := 1 To n Do
    WriteLn(nomes[i]);
  WriteLn;
End;

Begin
  ReadLn(n, k);
  For i := 1 To n Do
    ReadLn(nomes[i]);

  For i := 1 To n - 1 Do
    For j := i + 1 To n Do
      If (nomes[i] > nomes[j]) Then Begin
        nomeTemp := nomes[i];
        nomes[i] := nomes[j];
        nomes[j]:= nomeTemp;
      End;

  WriteLn(nomes[k]);
end.
