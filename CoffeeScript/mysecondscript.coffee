# Description:
#   2件目のCoffeeScript
#
# 関数:
#   is_square, triple - if文
#   greeting - switch文
#   countup, simplecountdown, laugh - 数値配列と繰り返し
#   power_perfect - 繰り返し処理による、累乗計算の決定版
#   about_root - while文で平方根の概算
#   simple_timer - while文で簡易タイマー
#

module.exports = (robot) ->
  robot.respond /$/i, (msg) ->
    msg.send 
    
  robot.respond /(.*)の2乗は(.*)ですか$/i, (msg) ->
    msg.send is_square msg.match[1], msg.match[2]*1

  robot.respond /(.*)の3倍は何ですか$/i, (msg) ->
    msg.send triple msg.match[1]

  robot.respond /(.*)の(挨拶|あいさつ)は/i, (msg) ->
    msg.send greeting msg.match[1]

  robot.respond /1から(.*)まで数えてください/i, (msg) ->
    msg.send countup msg.match[1]

  robot.respond /準備はいいですか$/i, (msg) ->
    msg.send simplecountdown
    
  robot.respond /すばらしいですね$/i, (msg) ->
    msg.send laugh

  robot.respond /もう(.*)の(.*)乗も計算できますね$/i, (msg) ->
    msg.send power_perfect msg.match[1], msg.match[2]

  robot.respond /(.*)の平方根は何ですか/i, (msg) ->
    msg.send about_root msg.match[1]

  robot.respond /あとはよろしく$/i, (msg) ->
    msg.send "..."
    simple_timer 5000
    msg.send "はい"





is_square = (x, sqx) -> 
	if sqx is x*x  then "その通りです" else "違います"

    
triple = (x, str="") ->
   str = "えーと" if x > 10
   "#{str}#{x*3}です"

greeting = (str) ->
  switch str
    when "朝" then "グッモーニン"
    when "昼" then "グーテンターク"
    when "夜" ,"晩" then "ボンソワール"
    else "まあ、人それぞれですから"
    

countup = (n) -> 
  if n<11 
    num for num in [n..1] 
  else 
    "そんなたくさんイヤです"

simplecountdown=  "#{num for num in [3..1]}ゴー"
 
laugh =
  "ホ" for num in[1..5]
  
power_perfect = (x, p, result =1) ->
  result *= x for power in [1..p]
  "はい、おかげさまで#{x}の#{p}乗は#{result}です"

about_root = (n, r=2) ->
  r++  while n > r*r
  "#{r-1}か#{r}じゃないでしょうか"

simple_timer= (millisec) ->
  start = (new Date()).getTime()
  answer = no while (new Date()).getTime() - start < millisec 
  answer = yes

