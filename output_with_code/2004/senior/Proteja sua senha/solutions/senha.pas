{ OBI2004             }
{ Tarefa Senha        }
{ r. anido            }


program par;

type
   botao = record
	      val1, val2 : integer;
	   end;
var
   n, i, j, teste	: integer;
   senha		: array[1..6] of botao;
   botoes		: array['A'..'E'] of botao;
   total_dig_conhecidos	: integer;
   c			: char;

begin
   teste := 1;
   readln(n);
   while n > 0 do begin
      writeln('Teste ', teste);
      inc(teste);
      total_dig_conhecidos := 0;
      { le associacoes letras/numeros }
      for c := 'A' to 'E' do with botoes[c] do begin
	 read(val1, val2);
      end;
      for i := 1 to 6 do with senha[i] do begin
	 read(c); read(c);
	 val1 := botoes[c].val1;
	 val2 := botoes[c].val2;
      end;
      for i := 2 to n do begin
	 for c := 'A' to 'E' do with botoes[c] do begin
	    read(val1, val2);
	 end;
	 for j := 1 to 6 do with senha[j] do begin
	    read(c); read(c);
	    if val1 <> val2 then { posicao ainda indefinida }
	       if (val1 = botoes[c].val1) and (val2 <> botoes[c].val2) then begin
		  inc(total_dig_conhecidos);
		  val2 := val1;
	       end
	       else if (val1 = botoes[c].val2) and (val2 <> botoes[c].val1) then begin
		  inc(total_dig_conhecidos);
		  val2 := val1;
	       end
	       else if (val2 = botoes[c].val2) and (val1 <> botoes[c].val1) then begin
		  inc(total_dig_conhecidos);
		  val1 := val2;
	       end
	       else if (val2 = botoes[c].val1) and (val1 <> botoes[c].val2) then begin
		  inc(total_dig_conhecidos);
		  val1 := val2;
	       end;
	 end;
      end;
      { imprime resultado }
      if total_dig_conhecidos = 6 then
	 for i := 1 to 6 do write(senha[i].val1:1, ' ')
      else
	 write('impossivel! ', total_dig_conhecidos);
      writeln; writeln;
      readln(n);
   end;
end.
