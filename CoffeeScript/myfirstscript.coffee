# Description:
#   はじめてのCoffeeScript、関数とif文まで
#
# 関数:
#   square  - 2乗を求める
#   square_polite - 文字列に式を埋め込む
#   hubot calc_power - このスクリプトの集大成


module.exports = (robot) ->
  robot.respond /SING$/i, (msg) ->
    msg.send "ラララ"
    
  robot.respond /二かける四はいくつ$/i, (msg) ->
    msg.send tbf  
    
  robot.respond /5の2乗はいくつ$/i, (msg) ->
    msg.send square 5
    
  robot.respond /7の3乗はいくつ$/i, (msg) ->
    msg.send cube 7

  robot.respond /(.*)の2乗は何ですか/i, (msg) ->
    msg.send square msg.match[1]

  robot.respond /(.*)の3乗は何ですか/i, (msg) ->
    msg.send cube msg.match[1]
  
  robot.respond /(.*)の2乗をお願いします/i, (msg) ->
    msg.send square_polite msg.match[1]

  robot.respond /(.*)の(.*)乗はどうでしょうか/i, (msg) ->
   msg.send calc_power msg.match[1], msg.match[2]*1

 # robot.respond /ECHO (.*)$/i, (msg) ->
 #  msg.send msg.match[1]

 # robot.respond /TIME$/i, (msg) ->
 #  msg.send "Server time is: #{new Date()}"

  robot.respond /BYE$/i, (msg) ->
    msg.send "では失礼いたします"
    process.exit 0


tbf=2*4

square = (x) -> x*x

cube= (x) -> square(x)*x

square_polite = (x) ->
  "#{x}の2乗は#{square x}です"

cube_polite = (x) ->
  "#{x}の2乗は#{cube x}です"

calc_power = (x, p) ->
    if p is 2
       square_polite x
    else if p is 3
       cube_polite x
    else
       "そんなのわかりません"

