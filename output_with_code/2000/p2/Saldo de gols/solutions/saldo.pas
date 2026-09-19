program saldo;

var N		    : Integer;
    saldos	    : array[1..10000] of Integer;
   saldoMaior, I, J : Integer;
   
Procedure CalculaVetorSaldos;
var jogo, X, Y : Integer;
begin
   for jogo:=1 to N do begin
      read(X, Y);
      saldos[jogo]:=X-Y;
   end;
end;
      
Procedure CalculaIntervalo;
var saldoAtual, inicio : Integer;
    jogo	       : Integer;
begin
   saldoMaior:=0;
   saldoAtual:=0;
   inicio:=1;
   for jogo:=1 to N do begin
      if saldoAtual+saldos[jogo] >= 0 then
	 saldoAtual:=saldoAtual+saldos[jogo]
      else begin
	 saldoAtual:=0;
	 inicio:=jogo+1;
      end;
      if (saldoAtual>saldoMaior) or
	 ((saldoAtual=saldoMaior) and (jogo-inicio > J-I)) then begin
	 saldoMaior:=saldoAtual;
	 I:=inicio; J:=jogo;
      end;      
   end;
end; { CalculaIntervalo }

var teste : Integer;
begin
   teste:=1;
   Readln(N);
   While N>0 do begin
      CalculaVetorSaldos;
      CalculaIntervalo;      
      Writeln('Teste ', teste);      
      if saldoMaior>0 then
	 Writeln(I, ' ', J)
      else
	 Writeln('nenhum');
      Writeln;
      Inc(teste); Readln(N);
   end;
end.

