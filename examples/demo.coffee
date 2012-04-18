Sprock = require '../index'

obj =
  hello: 'test'
  other: 'tazt'

trap = (name) ->
  console.log name
  if name is 'fsgfsd'
    return 'wot'
  else
    return @[name]

prox = new Sprock obj, trap

console.log prox.hello
console.log prox.fsgfsd
console.log prox.waaaa
console.log prox.wot.wot