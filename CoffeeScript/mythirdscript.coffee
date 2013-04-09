# Description:
#   3件目のCoffeeScript
#
# 関数:
#   substr_it - 文字列のm文字目からk文字取る。mもkも「1」から数える
#   say_match - 関数substr_itを用いて、文字列の検索を行う
#   list_it - 配列の要素とインデックスをともに取り出す
#   get_answer - 二つの配列の同じインデックスの要素を結びつける
#   answer_variable - 可変長引数を取る関数
#   favorite - 有限の引数と可変長引数の組み合わせ
#

module.exports = (robot) ->
  robot.respond /$/i, (msg) ->
    msg.send 
    
  robot.respond /友達はいますか$/i, (msg) ->
    msg.send "ええまあ"
    msg.send tell_friends
    
  robot.respond /(.*)はあなたの友達ですか$/i, (msg) ->
    msg.send is_friend msg.match[1]
 
  robot.respond /親友は誰ですか$/i, (msg) ->
    msg.send "#{robo}ですね"
    
  robot.respond /みなさんに挨拶を$/i, (msg) ->
    msg.send word_by_word "地球のみなさん"

  robot.respond /歌ってください$/i, (msg) ->
    msg.send pop_it "ヌタララララ"

  robot.respond /(.*)の(.*)文字目から(.*)文字とって$/i, (msg) ->
    msg.send substr_it msg.match[1], msg.match[2]*1, msg.match[3]*1
  
  robot.respond /「(.*)」の中に「(.*)」はありますか$/i, (msg) ->
    msg.send say_match msg.match[1], msg.match[2]

  robot.respond /本当にあなたの親友は$/i, (msg) ->
    msg.send good_friends

  robot.respond /打順は$/i, (msg) ->
    msg.send list_it

  robot.respond /あなたは(.*)ですか$/i, (msg) ->
     msg.send get_answer msg.match[1]

  robot.respond /痛み止めは(.*)と(.*)に飲んでください$/i, 
  (msg) ->
     msg.send answer_variable msg.match[1], msg.match[2]

  robot.respond /かゆみ止めは(.*)と(.*)と(.*)に飲んでください$/i,
  (msg) ->
     msg.send answer_variable msg.match[1], msg.match[2],
     msg.match[3]

  robot.respond /今朝は何を食べましたか$/i, (msg) ->
    msg.send eat_today foods...

  robot.respond /昼は何を食べましたか$/i, (msg) ->
    msg.send eat_today foods

  robot.respond /デートはどうでしたか$/i, (msg) ->
    msg.send eat_two foods...
    
  robot.respond /好きな食べ物は何ですか$/i, (msg) ->
    msg.send favorite foods...



friends = ["ピボット", "ロボリン", "ロボホップ", "ロゼット","コロボックル"]
stamen = ["松本","篠塚","原", "スミス"]
animals = ["犬", "猫", "チキン"]
answers = ["わんわん", "ニャオー", "失礼な"]
foods=[
	"カレー"
	"ハンバーグ"
	"牛丼"
	"唐揚げ"
	"パスタ"
	"ラーメン"
	"マーボ豆腐"
]



tell_friends =
 "#{friend for friend in friends}というところでしょうか"

is_friend = (name) ->
  if name in friends 
       "#{name} はいい人です"
     else
       "違います"

robo = 
  r for r in friends when r[0] is
  "ロ" and r[1] is "ボ"

word_by_word = (str)->
  c for c in str


pop_it = (str) ->
  str[1..]

    
substr_it = (str, m, k) ->
  str[m-1..m+k-2]


str_in_words = (str, pattern) ->
  substr_it str, m, pattern.length for m in [1..str.length]

do_match = (str, pattern) ->
  if pattern in str_in_words str, pattern then yes else no

say_match = (str, pattern) ->
   if do_match str, pattern then "あります" else "ありません"

good_friends =
  "実は
#{friend for friend in friends when do_match friend, "ロボ"}
というのが本当です"

list_it =
  "#{i+1}番 #{man}" for man, i in stamen 

get_answer= (input) ->
  result = answers[i] for animal, i in animals when animal is input 
  result ? "違います"

answer_variable = (arg...) ->
  "#{arg[arg.length-1]}に飲むの忘れました"
  

eat_today = (food) ->
  "#{food}を食べました"

eat_two = (me, she) ->
  "私は#{me}を、彼女は#{she}を食べました"

favorite = (first, second, others...) ->
   "#{first}が大好きです。#{second}が次に好きです。あと#{others}
も悪くないですね。"


