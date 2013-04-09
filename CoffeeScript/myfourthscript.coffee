# Description:
#   4件目のCoffeeScript
#
# オブジェクト:
#   myself_jp, keys_jp -オブジェクトの例
#   Animal, FarmAnimal, Cow, Horse, OtherAnimal
#    -クラスとサブクラス
# 関数：
#   newline - 配列を改行記号で連結
#   about_me_jp - 同じ構造の二つのオブジェクトを結びつける
#   find_animal - 同じクラスからいろいろなインスタンスを作る
#   describe_animal - 同じクラスから作った異なるサブクラスを使う
#

   

module.exports = (robot) ->
  robot.respond /$/i, (msg) ->
    msg.send 
    
  robot.respond /自己紹介を$/i, (msg) ->
    msg.send about_me
    
  robot.respond /日本語で自己紹介を$/i, (msg) ->
    msg.send newline about_me_jp
    
  robot.respond /足が(.*)本の動物が$/i, (msg) ->
    msg.send (find_animal msg.match[1]*1).identify()

  robot.respond /あれは牛ですか$/i, (msg) ->
    msg.send describe_animal new Cow "干し草"

  robot.respond /あれは馬ですか$/i, (msg) ->
    msg.send describe_animal new Horse "ニンジン"

  robot.respond /あれは羊ですか$/i, (msg) ->
    msg.send describe_animal new OtherAnimal "羊", "紙"




myself=
  name: "Hubot"
  birthday: "Sep. 7, 2011"
  star: "Virgo"
  character: "Calm"
  favorite: "Coffee"
  hate: "Bad indent"

keys_jp=
  name: "名前"
  birthday: "誕生日"
  star: "星座"
  character: "性格"
  favorite: "好きなもの"
  hate: "きらいなもの"

myself_jp=
  name: "Hubot"
  birthday: "2011年9月7日"
  star: "おとめ座"
  character: "温厚"
  favorite: "コーヒー"
  hate: "字下げの乱れ"


class Animal
  constructor: (@name) ->
  identify: ->
    "あれは#{@name}ですね" 


class FarmAnimal extends Animal
   constructor: (@name, @food) ->

   identify: ->
     "そうですね、#{super}"

   eats: ->
     "#{@food}をよく食べます"

   cooked: (dish) ->
     "いい#{@name}#{dish}になりますよ"  


class Cow extends FarmAnimal
   constructor: (@food) ->
      super "牛", @food
   cooked: ->
      super "丼"


class Horse extends FarmAnimal
   constructor: (@food) ->
     super "馬", @food
   cooked: ->
      super "刺"

class OtherAnimal extends FarmAnimal
   cooked: ->
       super "鍋"




newline = (arr) -> arr.join "\n"

about_me = for the_key, the_value of myself
     "my #{the_key} is #{the_value}"

about_me_jp = for the_key, the_value of myself_jp
   "私の#{keys_jp[the_key]}は#{the_value}です"

find_animal = (feet) ->
  switch feet
   when 2 then new Animal "ペンギン"
   when 4 then new Animal "猫"
   when 6 then new Animal "虫"
   else new Animal "何か"

describe_animal= (animal) ->
  newline [animal.identify(), animal.eats(), animal.cooked()]

