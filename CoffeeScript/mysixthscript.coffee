# Description:
#   6件目のCoffeeScript
#   
# クラス:
#   SingingRobot- プロパティに関数を持つ
#  
#  配列:
#   songs - 文字列の引数をひとつ取る関数の配列
#   singers - クラスSingingRobotのインスタンスを
#               定義する文自体を配列に収めた
#

module.exports = (robot) ->
  robot.respond /$/i, (msg) ->
    msg.send 
    

  robot.respond /テーマソングを/i, (msg) ->
    msg.send newline sing_songs "Hubot"
  robot.respond /全員合唱を/i, (msg) ->
    msg.send newline (singer.sing_it() for singer in singers)



song_name= (myrobot) ->
 "#{myrobot}は私の名前"

song_work = (myrobot) ->
 "#{myrobot}は働き者"

song_clever = (myrobot) ->
 "#{myrobot}は賢い"

song_weakpoint = (myrobot) ->
 "でも#{myrobot}は犬には弱い"

songs=[song_name, song_work, song_clever, song_weakpoint]


sing_songs = (myrobot)->
  song myrobot for song in songs

newline = (arr) -> arr.join "\n"



class SingingRobot
  constructor: (@name, @callback) ->
  sing_it: ->
     @callback @name


singers = [
  zabot = new SingingRobot "Zabot", song_name
  gebot = new SingingRobot "Gebot", song_work
  mubot = new SingingRobot "Mubot", song_clever
  myself = new SingingRobot "Hubot", song_weakpoint
  quartet = 
    new SingingRobot "ロボット4人組", 
    (myrobot) -> "以上#{myrobot}でした"
]




