should = require 'should'
Sprock = require '../index'

obj =
  hello: 'test'
  other: 'tazt'

trap = ({type, property, value}) ->
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

folder = ""
exec = (cb) -> console.log folder
obj = {}

trapo = ({type, property, value}) ->
  if type is 'get'
    return exec if property is 'run'
    folder += "#{property}/"
    return new Sprock obj, trapo

nad = new Sprock obj, trapo

nad.somefolder.somefolder.somefile.run (err, res) ->