/*
** Local Variables
*/
var POP_SIZE = 500
  , MUT_RATE = 0.02
  , MAX_HERO = 100
  , population = []
  , fitness = new Array(POP_SIZE)
  , individual_length = 100
  , iterations = 10000
  , evaluations = 0
  , tournament_size = 2
  , hero = 0
  , i, j
;

// initialize
for(i = 0; i < POP_SIZE; i++) {
    var p = [];
    for(j = 0; j < individual_length; j++) {
        p.push(randomInt(0, 1));
      }
    ;
    population.push(p);
  }
;

// Evaluate fitness levels
for(i = 0; i < POP_SIZE; i++) { fitness[i] = fv(i); }

console.log("initial population created", population, "now evolve!");

for(var trial = 0; trial < iterations; trial++) {
    var pair1, pair2
      , p1 = 0 , p2 = 0
    ;
    pair1 = tournament();
    pair2 = tournament();

    if(hero >= MAX_HERO) break;

    make_children(pair1, pair2);
    if(MUT_RATE > 0.0) {
        mutate(pair1.loser);
        mutate(pair2.loser);
    }

    fitness[pair1.loser] = fv(pair1.loser);
    fitness[pair2.loser] = fv(pair2.loser);
}

console.log(hero, iterations, evaluations);


/*
** Helper Functions
*/
function fv(index) {
    var fit = d3.sum(population[index]);
    evaluations++;
    if(fit > hero) {
        console.log("New hero", evaluations, fit, fit/MAX_HERO);
        hero = fit;
    }
    return fit;
} // fv()

function tournament() {
    var win = -99999
      , lose = 99999
      , ret = { winner: null, loser: null }
    ;
    for(i = 0; i < tournament_size; i++) {
        var randex = randomInt(0, POP_SIZE);
        if(fitness[randex] >= win) {
            win = fitness[ret.winner = randex];
        }
        if(fitness[randex] <= lose) {
            lose = fitness[ret.loser = randex];
        }
    }
    return ret;
} // tournament()

function make_children(pair1, pair2) {
    for(i = 0; i < individual_length; i ++) {
        if(randomInt(0, 1)) {
            population[pair1.loser][i] = population[pair1.winner][i];
            population[pair2.loser][i] = population[pair2.winner][i];
        } else {
            population[pair1.loser][i] = population[pair2.winner][i];
            population[pair2.loser][i] = population[pair1.winner][i];
        }
    }
} // make_children()

function mutate(index) {
    for(i = 0; i < individual_length; i++) {
        if(Math.random() < MUT_RATE)
            population[index][i] = Math.round(Math.random());
    }
} // mutate()


function randomInt(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1)) + min;
}
