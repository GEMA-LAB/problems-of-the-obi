
function permutator (inputArr) {
  let result = [];

  const permute = (arr, m = []) => {
    if (arr.length === 0) {
      result.push(m)
    } else {
      for (let i = 0; i < arr.length; i++) {
        let curr = arr.slice();
        let next = curr.splice(i, 1);
        permute(curr.slice(), m.concat(next))
      }
    }
  }

  permute(inputArr)

  return result;
}

const INF = 1e9 + 5;
var melhores_tempos = [
  [  
    [[INF, INF], [INF, INF]],  
    [[INF, INF], [INF, INF]],
    [[INF, INF], [INF, INF]],
    [[INF, INF], [INF, INF]]
  ],
  [ 
    [[INF, INF], [INF, INF]],
    [[INF, INF], [INF, INF]],
    [[INF, INF], [INF, INF]],
    [[INF, INF], [INF, INF]]
  ]
]


var N;
var meninos = 0;
scanf("%d", "N");
for (var i = 0; i < N; i++) {
  var modalidade = 0;
  scanf("%d", "modalidade");

  meninos += modalidade;

  var tempo_estilo = [0, 0, 0, 0];
  scanf("%d %d %d %d", "tempo_estilo[0]", "tempo_estilo[1]", "tempo_estilo[2]", "tempo_estilo[3]");

  for (let estilo = 0; estilo < 4; estilo++) {
    var tempo = tempo_estilo[estilo];
    if (tempo <= melhores_tempos[modalidade][estilo][0][1]) {
      melhores_tempos[modalidade][estilo][1] = melhores_tempos[modalidade][estilo][0]
      melhores_tempos[modalidade][estilo][0] = [i, tempo]
    } else if (tempo <= melhores_tempos[modalidade][estilo][1][1]) {
      melhores_tempos[modalidade][estilo][1] = [i, tempo]
    }
    
  }
}

if (meninos < 2 || (N - meninos) < 2) {
  printf("-1\n");
  return 0;
}

var combinacao = [0, 1, 2, 3]
var menor = -1


for (const perm of permutator(combinacao)) {
  var f1 = perm[0], f2 = perm[1], m1 = perm[2], m2 = perm[3]
  var f_total = 0, m_total = 0
  var aux1 = 0, aux2 = 0

  if(melhores_tempos[0][f1][0][0] != melhores_tempos[0][f2][0][0]) {
    f_total = melhores_tempos[0][f1][0][1] + melhores_tempos[0][f2][0][1]
  } else {
    aux1 = melhores_tempos[0][f1][0][1] + melhores_tempos[0][f2][1][1]
    aux2 = melhores_tempos[0][f1][1][1] + melhores_tempos[0][f2][0][1]
    // Acho que eu poderia usar math.min aqui, nao sei.
    if(aux1 < aux2) {
      f_total = aux1
    } else {
      f_total = aux2
    }
  }

  if(melhores_tempos[1][m1][0][0] != melhores_tempos[1][m2][0][0]) {
    m_total = melhores_tempos[1][m1][0][1] + melhores_tempos[1][m2][0][1]
  } else {
    aux1 = melhores_tempos[1][m1][0][1] + melhores_tempos[1][m2][1][1]
    aux2 = melhores_tempos[1][m1][1][1] + melhores_tempos[1][m2][0][1]
    if(aux1 < aux2) {
      m_total = aux1
    } else {
      m_total = aux2
    }
  }

  var total = f_total + m_total
  if (menor == -1 || total <= menor) {
    menor = total
  }
}

printf("%d\n", menor);