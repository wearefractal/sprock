should = require 'should'
Sprock = require '../index'

obj =
  hello: 'test'
  other: 'tazt'

trap = ({type, property, value}) ->
  console.log type, property, value
  if type is 'get'
    if property is 'fsgfsd'
      return 'wot'
    else
      return @[property]
  else if type is 'set'
    @[property] = value
  else if type is 'call'
    console.log 1
  else if type is 'construct'
    console.log 1

prox = new Sprock obj, trap

prox.hello.should.equal "test"
prox.fsgfsd.should.equal "wot"
should.not.exist prox.waaaa
prox.hello = "hi"
prox.hello.should.equal "hi"

prox.testi 'test'