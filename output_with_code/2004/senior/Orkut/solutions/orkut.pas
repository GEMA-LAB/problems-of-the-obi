(* Orkut      *)
(* OBI2004    *)
(* r. anido   *)

program orkut;
const
   MAX		  = 30;
   MAX_CARACTERES = 16;
type
   tipo_nome	  = array[1..MAX_CARACTERES] of char;
var
   grafo       : array [1..MAX, 1..MAX] of boolean;
   grau, lista : array [1..MAX] of integer;
   marca       : array [1..MAX] of boolean;
   pilha       : array [1..MAX] of integer;
   nomes       : array [1..MAX] of tipo_nome;
   n_nomes     : integer;
   um_nome     : tipo_nome;
   i, j, k, l  : integer;
   total       : integer;
   n, m, teste : integer;

procedure debug;
var
   i :  integer;
begin
   write(' entre com um inteiro: ');
   readln(i);
end; { debug }

procedure escreve_nome(s: tipo_nome);
var
   i : integer;
begin
   i := 1;
   while (s[i] <> ' ') do begin
      write(s[i]);
      inc(i);
   end;
end; { escreve_nome }

procedure le_nome(var s	: tipo_nome);
var
   i : integer;
begin
   repeat
      read(s[1]);
   until s[1] <> ' ';
   i := 1;
   while (s[i] <> ' ') and not eoln do begin
      inc(i);
      read(s[i]);
   end;
   for i := i+1 to MAX_CARACTERES do
      s[i] := ' '; 
end; { le_nome }

{ um dicionario bem simples, busca sequencial.  }
{ se o numero de nomes fosse grande, necessita  }
{ um dicionario mais bem implementado...        }
procedure dicio_insere(s : tipo_nome);
begin
   inc(n_nomes);
   nomes[n_nomes] := s;
end; { dicio_insere }

function dicio_procura(s : tipo_nome): integer;
var
   i : integer;
begin
   for i := 1 to n_nomes do
      if nomes[i] = s then
	 dicio_procura := i;
end; { dicio_procura }

function dicio_nome(k : integer): tipo_nome;
begin
   dicio_nome := nomes[k];
end; { dicio_nome }

procedure elimina(k : integer);
var i, j : integer;
begin
   {writeln('elimina ', k);}
   inc(total);
   lista[total] := k;
   marca[k] := true;
   for i := 1 to n do if (not marca[i]) and grafo[k, i] then begin
      grafo[k, i] := false;
      dec(grau[i]);
      if grau[i] = 0 then elimina(i);
   end;
end; { elimina }

begin
   teste := 1;
   readln(n);
   while (n > 0) do begin
      (* inicializa grafo *)
      for i := 1 to n do
	 for j := 1 to n do begin
	    grafo[i, j] := false;
	    grafo[j, i] := false;
	 end;
      for i := 1 to n do begin
	 marca[i] := false;
	 grau[i] := 0;
      end;
      (* le nomes *)
      n_nomes := 0;
      for i := 1 to n do begin
	 le_nome(nomes[i]);
	 dicio_insere(nomes[i]);
      end;
      readln;
       (* le exigencias *)
      for i := 1 to n do begin
	 le_nome(um_nome);
	 k := dicio_procura(um_nome);
	 read(m);
	 for j := 1 to m do begin
	    le_nome(um_nome);
	    l := dicio_procura(um_nome);
	    inc(grau[k]);
	    grafo[l, k] := true;
	 end;
	 readln;
      end;
      (* procura pessoa com grau 0 (nao depende de nenhum outro) *)
      (* imprime esse nome, elimina arestas de saida e repete o  *)
      (* processo *)
      writeln('Teste ', teste);
      teste := teste + 1;

      total := 0;
      for i:=1 to n do
	 if (grau[i] = 0) and (not marca[i]) then begin
	    elimina(i);
	 end;
      if total = n then for i:=1 to n do begin
	 escreve_nome(dicio_nome(lista[i]));
	 write(' ');
      end
      else
	 write('impossivel');

      writeln; writeln;
      readln(n);
   end;
end.
