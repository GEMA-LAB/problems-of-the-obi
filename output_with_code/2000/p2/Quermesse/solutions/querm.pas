program querm;

var
   teste, N, numero, pos : Integer;
   Num_solucoes, Solucao : Integer;

begin
   teste:=1;
   Readln(N);
   while N > 0 do begin
      Num_solucoes:=0;

      for pos:=1 to N do begin
	 Read(numero);
	 if numero=pos then begin
	    Inc(Num_solucoes);
	    Solucao:=numero;
	 end;
      end;

      Writeln('Teste ', teste);
      if Num_solucoes=1 then
	 Writeln(Solucao)
      else
	 Writeln('ERRO! Foram encontradas ', Num_solucoes, ' solucoes');
      Writeln;
      
      Inc(teste);
      Readln; Readln(N);
   end;
end.

