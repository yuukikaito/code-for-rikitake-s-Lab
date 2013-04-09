# Description:
#   5件目のCoffeeScript
#   Hubotと仲間たちの力比べプログラム
#
# クラス：
#  Rival, BetterRival - ライバルのクラスとサブクラス
#  HubotSpec, HubotBetterSpec
#     - Hubotの性能を表すクラスとサブクラス
#       ライバルとの勝ち負け判定、報告をする関数も含む
#  
#  

   

module.exports = (robot) ->
  robot.respond /$/i, (msg) ->
    msg.send 
    
  robot.respond /最近どうですか$/i, (msg) ->
    msg.send first_spec.report bear
    msg.send first_spec.report rabbit
    msg.send better_spec.report grasshopper
    msg.send better_spec.report beetle
    msg.send better_spec.report hornet



class Rival
  constructor: (@name, @strength) ->


bear = new Rival "クマ", 40
rabbit = new Rival "ウサギ", 100


class HubotSpec
  constructor: (@strength) ->

  won_against: (rival) ->
     rival.strength < @strength

  result: (rival) ->
     if @won_against rival then "勝ちました"
     else "やられました"

  report: (rival) ->
     "#{rival.name}さんには#{@result rival}"

first_spec = new HubotSpec 60

class BetterRival extends Rival
   constructor: ->
     super
     @toughness = 100-@strength 
     
grasshopper = new BetterRival "バッタ", 20      
beetle = new BetterRival "カブトムシ", 50
hornet = new BetterRival "スズメバチ", 90

class HubotBetterSpec extends HubotSpec
  constructor: ->
     super
     @toughness = 100-@strength 
  won_against:(rival) ->
     rival.strength*rival.toughness  < @strength*@toughness

better_spec = new HubotBetterSpec 60
