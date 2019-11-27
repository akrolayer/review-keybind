= Karabiner-Elements
== Karabiner-Elementsとは
Karabiner-Elementsとは、Sierra以降のmacOSのキーボードをカスタマイズするためのツールです。Sierraからキーボードドライバの構成が変更されたため、Karabiner-Elementsが開発されました。それより前はKarabinerが開発されていました。既存で用意されている設定に、主要エディタのショートカットキーがあり（Vim, emacs, vscode）、とても簡単に設定できます。キーの組み合わせで他のキー入力や、マウス操作、キーバインド設定が独自で定義できます。この本では、Karabiner-Elementsを扱います。設定のインポート方法、独自設定の設定方法を紹介します。

== 実際にキーバインド設定してみよう
まず、公式サイト（https://pqrs.org/osx/karabiner/）からインストールします。設定は変更せずインストール完了まで進めてください。Karabiner-Elementsの設定は~/.config/karabiner/karabiner.jsonに保存されます。Karabiner-Elementsを起動すると、このような画面が出ます。（画像入れる）
Simple Modificationsでは、From keyの入力をTo keyの入力に変換できます。Add itemをクリックして、新たなルールを設定してください。消したい場合は、右側のRemoveをクリックしてください。

=== 既存設定のインポート
Complex Modificationsでは、主要エディタのショートカットキー設定（emacs、vim、vscodeなど）が既存で設定されています。独自設定を追加する場合は複数キーの組み合わせを扱うことができ、押しっぱなしといった複雑なルールも扱うことができます。Add ruleをクリックして、Import more rules from the internet(open a web browser) をクリックすると、インポート可能なキーバインド設定の一覧が表示されているサイトが立ち上がります。追加したいキーバインド設定のImportをクリックして、インポートが完了すると、Karabiner-Elementsの画面に適用可能なキーバインドの一覧が表示され、Enableをクリックすると適用されます。Rulesに追加され、Enableになっているキーバインドの設定が表示されます。

=== 独自設定
キーバインド設定をするなら、自分に合った独自のキーバインド設定をしたいですよね。Karabiner-Elementsでも独自キーバインド設定ができます。キーバインド設定は、~/.config/karabiner/assets/complex_modificationsに保存されます。インポートした設定は数列.jsonというファイル名で保存されます。このディレクトリのjsonファイルを読み込んでいるため、自分でjsonファイルを作成すると読み込まれます。設定ファイル名は英数字内で自由なのですが、ごくたまに読み込まれないことがあります。その際はファイル名を数列.jsonとしてください。jsonファイルが分からなくても、Karabiner-Elementsにおいては簡単な書式なので真似すれば問題ないです。
=== [column]jsonファイルとは
JSONとはJavaScript Object Notationの略で、テキストベースのデータフォーマットです。主要なプログラミング言語にはjsonの生成や読み込みを行うライブラリが存在しているため、データ交換のためのデータフォーマットとして利用されます。書式は
//emlist[ex1]{
{
  "key":"value",
  "key2":"value2",
  "key3":[true, 123, "value3"]
}
//}
まず、全体を｛｝で囲む必要があります。キーと値を：で区切って並べて書きます。複数にわたる場合は「,」で区切って並べます。値は、文字列は""で囲み、数値とbool値はそのまま、配列は[]で囲み要素を「,」で区切ります。見やすいように改行することが多いですが、すべてを1行で書いてもいいです。
===

それでは、jsonファイルの中身を見ていきましょう。
//emlist[rule]{
{
  "title": "Add rulesに表示させる",
  "rules": [
    {
      "description": "descriptionを表示させる"
    }
  ]
}
//}
まず、Karabiner-ElementsのRule追加画面に表示させる設定です。titleに設定した文字列が表示され、その中にdescriptionが各項目の設定として表示されています。（画像入れる）

設定ファイルを編集後、変更を反映させるには「Complex Modifications」で対象のルールをEnableして、Add rulesで再度ルールを適用してください。

コメントは、キーを増やしても問題ないので"comment"のキーを作成する方法があります。
//emlist[コメントの付け方]{
"description": "descriptionを表示させる",
"comment": "このキーを増やしてここにコメントを書いてもよい"
//}

rulesは配列になっているので、１つのrulesの中に複数のdescription以下の設定を記述できます。titleの中に複数の設定が表示されていましたよね。
また、１つのdescriptionの中に複数の設定をすることもできます。
//emlist[karabiner-Elementsの設定ツリー]{
"title"
"rules"
  "description"
  "manipulators"
    "type"      //1つ目の設定
    "from"
    "to"
    "type"      //2つ目の設定
    "from"
    "to"
//}

実際にキーバインド設定の記述に入ります。基本としては、fromで設定したキー入力を受け付けたら、toで設定したキー入力に変更するというものです。

設定全体の注意点として、fromに設定した入力は、通常の動作をせずここで設定した入力をすることに注意してください。ちなみに、toになにも設定しないと何もしないのでfromに設定したキーを無効化します。また、単純にfrom、toに1つのキーを設定した場合は、キーマップの変更になります。

typeには、基本的には"basic"を指定します。マウスの動きをスクロールに変換したい場合のみ"mouse_motion_to_scroll"を指定します。この機能を使う場合は、Karabiner-ElementsのDevicesで、自分が使っているマウスにチェックを入れておく必要があります。
//emlist[マウススクロール]{
{
  "description": "Change control + mouse motion to scroll wheel (rev 1)",
  "available_since": "12.3.0",
  "manipulators": [
    {
      "type": "mouse_motion_to_scroll",
      "from": {
        "modifiers": {
          "mandatory": [
            "control"
          ]
        }
      }
    }
  ]
}
//}
この設定では、Controlキーを押しながらマウスを動かすと、動かした方向にスクロールするようになります。

ここからの説明では、"title"/"rules"/"description"/"manipulators"/"type"の直接関係ない部分は省略してサンプルを載せていきます。ここからの設定は、全てtypeは"basic"です。
//emlist[カーソルキー]{
"type":"basic"
"from":{
  "key_code":"j"
  "modifiers":{
    "mandatory":["control"]
  }
"to":[
  {"key_code":"left_arrow"}
 ]
//}

上記のコードは、control-jの組み合わせを指定しています。例の"controll"部分にanyを指定すると、全てのキー入力を指定します。キー入力ではなく、マウスのボタンを指定する時はkey_codeではなく、"pointing_button":"button3"のように指定してください。modifiersはキーの組み合わせを指定します。ここでは、mandatoryとoptionalがあります。

mandatoryはキーの組み合わせを指定します。この組み合わせが入力されたときに"to"の処理を行います。mandatoryには、修飾キーのcommand, control, shift, option, fn, caps_lock, anyのどれかを設定することをお勧めします。これら以外だと、mandatoryに指定したキーを押しながらkey_codeに指定したキーを押した場合のみ動作するので、mandatoryに指定したキーの入力が少なくとも1回入ってしまいます。

"pointing_button"を用いる際の注意点があります。button1は左クリックで、button1のみに処理を割り当てると左クリックとして使えなくなります。modifiersを用いて同時押しの一部にに使いましょう。

"optional"は、"from"の時に受け付けたキーを、"to"の時にも引き継ぐキーを指定します。"any"だと、全てのキー入力を引き継ぎます。ちなみに、Shift、controlなど左右に存在しているキーは、left_controlのようにすると左右区別できます。left、rightを書いていない場合は、どちらでも受け付けます。

//emlist[any]{
"from":{
  "key_code":"j"
  "modifiers":{
    "mandatory":["control"]
    "optional":["any"]
  }
"to":[
  {"key_code":"command"}
 ]
//}
control-Aのキー入力を受け付けると、command-Aにするといったものです。anyの部分には、一つのキーを指定することができます。"caps_lock"を指定すると、CapsLockがON状態でも変換を実行するようになります。Karabiner-Elementsは、CapsLockがONだと、CapsLockが押されていると判断しています。注意点として、"mandatory"と"optional"に同じキーを指定すると引き継ぎできなくなります。

"simultaneous"は、複数キーの同時押しに何らかの処理を割り当てたいときに使います。同時押しの許容時間は、Complex Modifications/Parameters/simultaneous_threshold_millisecondsで設定できます。デフォルトでは、50ミリ秒になっています。
//emlist[同時押し]{
{
  "manipulators": [
    {
      "type": "basic",
      "from": {
        "simultaneous": [
          { "key_code": "j" },
          { "key_code": "k" },
          { "key_code": "l" }
        ]
      },
      "to": [
        { "shell_command": "open -a TextEdit" }　//動作未確認
      ]
    }
  ]
}
//}
jklの同時押しでテキストエディタを起動します。simultaneousの下に、オプションを書けます。
//emlist[simultaneousのオプション]{
"simultaneous_options":{
  "detect_key_down_uninterruptedly",
  "key_down_order",
  "key_up_order",
  "key_up_when",
  "to_after_key_up"
}
//}
この５つがあります。
* "detect_key_down_uninterruptedly"
trueかfalseで指定します。trueだと、同時押しの途中に違うキーを押しても、同時押しに設定された操作の変換を行った後、違うキーを押します。上の例だと、jkslと押した場合、jklを押した動作をした後、sが入力されます。
* "key_down_order"
"strict","strict_inverse","insensitive"のどれかで指定します。発火するキーを押す順番を明確に決める設定です。"strict"が記述した順番、"strict_inverse"が記述と反対の順番です。"insensitive"は、順番を問わなくなります。
* "key_up_order"
"strict","strict_inverse","insensitive"のどれかで指定します。key_up_orderを指定すると、指定キーを押した時点では変換されず、いずれかのキーを一つ離した時点で発火します。"strict"だと"simultaneous"で最初に記述したキー、"strict_inverse"だと最後に記述したキー、"insensitive"だと記述したどのキーを離しても発火します。
* "key_up_when"
"all"か"any"を指定します。同時押しした全てのキーを離したことにするタイミングを設定します。"all"だとすべて離したとき、"any"だとどれか一つを離した時点で記述した全てのキーを離したことにします。
* "to_after_key_up"
同時押ししたキーを離した時点で処理を行いたい場合に設定します。例えば、フラグ処理に使えます。
//emlist[set_variable]{
"simultaneous_options": {
  "to_after_key_up": [
    { "set_variable": { "name": "hogehoge", "value": 0 } }
  ]
  },
  "to": [
    { "set_variable": { "name": "hogehoge", "value": 1 } }
  ]
//}
"set_variable"で代入ができます。このようにすれば、押したときに"value"を１、離したときに０にできます。

=== to
"to"についてですが、キーの指定方法に関しては"from"と同様です。配列なので、複数の処理を設定できます。
//emlist[toの例]{
"to":[
  {"key_code":"control"}
  {"key_code":"japanese_eisuu"}
  {"key_code":"control"}
]
//}
これで、fromの設定が発火したらcontrolを2回とjapanese_eisuuを押すことができます。"pointing_button"もあります。
//emlist[ダブルクリック]{
"to": [
  { "pointing_button": "button1" },
  { "pointing_button": "button1" }
]
//}
button1は左クリックなので、キー操作にダブルクリックを割り当てることができます。
//emlist[シェルコマンド1]{
"to": [
  { "shell_command": "open -a TextEdit" }　//動作未確認
]
//}

//emlist[シェルコマンド2]{
"to": [
  { "shell_command": "open \"aaa\"" }　//動作未確認
]
//}
キーの組み合わせにシェルコマンドを割り当てることができます。打ち込むコマンドにエスケープシーケンスが含まれる場合は\でエスケープ処理をする必要があります。

"modifiers"は、"from"の場合とは異なり、"mandatory"、"optional"の設定は不要です。
//emlist[toの場合の同時押し]{
"to": [
  {
    "key_code": "down_arrow",
    "modifiers": ["command", "shift"]
    "lazy":true
  }
]
//}
"lazy":true とすると、変換が実行されるタイミングが"from"が発火したタイミングではなく"from"が発火したキーを押しながら他のキーを押したタイミングになります。

"select_input_source"の"input_source_id"に特定の値を指定することでIMEの状態を指定することができます。IMEは特殊キーなので、値を確認します。Karabiner-ElementsのEventViewer→variablesでキーを押したときの値を見ることができます。アップル日本語入力か、Google
日本語入力など入力方式で値が変わります。input_source_identifiersの項目で"input_source_id"の値を確認してください。"language"が"ja"の時がIMEオンです。
//emlist[IME変更]{
//標準IMEでオンにする
"to": [
  {
    "select_input_source": {
      "input_source_id": "^com\\.apple\\.inputmethod\\.Kotoeri\\.Japanese$"
    }
  }
]
//}
"mouse_key"を使うと、マウス移動、ホイールスクロールが割り当てられます。クリックは前述の"pointing_button"で割り当てます。
//emlist[マウス移動]{
"to": [ { "mouse_key": { "x": -10 }} ,
        { "mouse_key": { "y": -10 }}
]
//}
//emlist[ホイールスクロール]{
"to": [
  { "mouse_key": { "horizontal_wheel": 64 } }
]
//}
x,yは座標のことなので、xが横方向（正で右、負で左）、yが縦方向（正で下、負で上）移動です。ホイールは、"horizontal_wheel"は左右のスクロール（正で右、負で左）、"vertical_wheel"は上下のスクロール（正で下、負で上）です。

"to_if_alone"は、単独で押したときのみ、設定に変換するというものです。
//emlist[単独押しの設定]{
"from": {
  "key_code": "left_command",
  "modifiers": {
    "optional": [ "any" ]
  }
},
"to": [
  {"key_code": "left_command"}
],
"parameters": {
  "basic.to_if_alone_timeout_milliseconds": 2000,
},
"to_if_alone": [
  {"key_code": "japanese_eisuu"}
]
//}
左Commandキーを単独で押した場合は英数キーとして認識し、他のキーと組み合わせて押すと左Command＋押したキーとして認識する設定です。2000ミリ秒押し続けると、英数への変換はキャンセルされます。

"to_delayed_action"はコードで説明します。
//emlist[to_delayed_action]{
"from": {
  "key_code": "x",
  "modifiers": { "mandatory": [ "control" ] }
},
"to": [ { "set_variable": { "name": "ctrl-x", "value": 1 } } ],
"to_delayed_action": {
  "to_if_invoked": [
     { "set_variable": { "name": "ctrl-x", "value": 2 } } 
   ],
  "to_if_canceled": [
     { "set_variable": { "name": "ctrl-x", "value": 0 } } 
   ]
}
//}
ctrl-xを押すと"ctrl-x"に1を代入し"to"の内容を実行します。そのまま何も押さないと2を代入します。ctrl-xに続けて何か別のキーを押すと0が代入されます。"to_if_invoked"が実行されるまでの時間はComplex Modifications→Parametersで指定できます。これをどのように使うかというと、emacsなどにある"ctrl-x ctrl-s"のキーバインド設定をするために使います。後述する"condition"を使って実装します。

"to_after_key_up"は、"from"で設定したキーから手を離したときに実行する処理を書きます。設定した変数の値を初期化するのによく使います。
//emlist[to_after_key_up]{
"to_after_key_up": [
  {"set_variable": { "name": "enthumble_mode","value": 0 } }
]
//}
"to_if_held_down"は、"from"で設定したキーを押し続けたときに実行する処理を書きます。"repeat"をtrueに指定すると、処理が実行され続けます。
//emlist[to_if_held_down]{
"parameters": { "basic.to_if_held_down_threshold_milliseconds": 1000 },
      "from": {
        "key_code": "q",
        "modifiers": { "mandatory": [ "command" ], "optional": [ "caps_lock" ] }
      },
      "parameters": { "basic.to_if_held_down_threshold_milliseconds": 1000 },
      "to_if_held_down": [
        { 
          "key_code": "q",
          "modifiers": [ "command" ],
          "repeat": false
        }
      ]
//}
command-qは楽ですが、閉じる必要のないアプリケーションを閉じないために1秒間押し続けないと処理を実行しないようにしています。

"conditions"は、一定の条件を満たすときのみに処理を行いたいときに指定する項目です。いわゆるif文です。

 * device_if、devece_unless
特定のキーボードの時、特定のキーボードでないときを条件にしたい場合は、　"identifiers"に、"vendor_id"と"product_id"を指定します。"vendor_id"と"product_id"は、Karabiner-ElementsのDevicesタブで確認できます。
//emlist[特定デバイス]{
"conditions": [
  {
    "type": "device_if",
    "identifiers": [
      {
        "vendor_id": 1278,
        "product_id": 515
        }
    ]
  }
]
//}
 * frontmost_application_if、frontmost_application_unless
特定のアプリの時、特定のアプリでないときを条件にしたい場合は、アプリを指定します。アプリの名称は"karabiner-EventViewer"で調べるか、シェルでosascript -e 'id of app "(調べたいアプリの名称)"'コマンドを実行して調べます。"karabiner-EventViewer"を立ち上げて、調べたいアプリを開くとFrontmost Application画面にアプリの名称が表示されます。アプリの名称は、正規表現でも指定できます。
//emlist[特定アプリケーション]{
"conditions": [
  {
    "type": "frontmost_application_if",
    "bundle_identifiers": [ "^com\\.apple\\.Safari" ]
  }
]
//}
 * variable_if、variable_unless
変数が特定の値の時、特定の値以外の時を条件にしたい場合は、押した時と離したときに異なる数値を"set_variable"で設定して条件に使います。
//emlist[特定変数]{
"from": {
  "key_code": "s",
},
"to": [
  {
    "set_variable": {    
      "name": "mode", "value": 1
    }
  }
],
"to_after_key_up": [
  {
    "set_variable": {
      "name": "mode", "value": 0
    }
  }
],
},
{
"type": "basic",
"from": {
  "key_code": "h",
},
"to": [
  { "key_code": "left_arrow" }
],
"conditions": [
  {
    "type": "variable_if",
    "name": "mode", 
    "value": 1
  }
]
//}
Sを押したときに1、離したときに0を設定しています。"name"は何でも良いです。Hを押したとき、mode変数が1ということはSが押しっぱなしなので、Sを押しながらHを推したときに"left_arrow"に変換します。

* input_source_if、input_source_unless
IMEが指定した状態の時、指定した状態でないときを条件にしたいときに使います。同じキーを押したときにIMEの状態によって処理内容を変更したい場合に使います。IME変更をトグル処理にしたいときに使うことが多いです。
//emlist[特定IME]{
{
  "type": "basic",
  "from": { "key_code": "Japanese_eisuu" },
  "to": [{"key_code": "Japanese_kana"}],
  "conditions": [
    {
      "type": "input_source_if",
      "input_sources": [{ "language": "en" }]
    }
  ]
},
//}

キーボードに含めていいのかは意見が分かれるでしょうが、タッチパッドに何本触れているかという情報を取得できます。全体だけでなく、左右半分、上下半分を分けて取得できます。キーを押さずにタッチパッドに触れるだけで良いので、押しながらの処理がもっと簡単な操作でできるようになります。この機能を使う際は、まずKarabiner-Elementsの設定画面の「Misc」から「Open Karabiner-MultitouchExtension app」を起動しておく必要があります。（（画像入れる））

このアプリが起動していると、以下の変数が格納されます。

 * multitouch_extension_finger_count_total
タッチパッドに触れている指の本数 
 * multitouch_extension_finger_count_left_half_area
タッチパッドの左半分に触れている指の本数
 * multitouch_extension_finger_count_right_half_area
タッチパッドの右半分に触れている指の本数
 * multitouch_extension_finger_count_upper_half_area
タッチパッドの上半分に触れている指の本数
 * multitouch_extension_finger_count_lower_half_area
タッチパッドの下半分に触れている指の本数

そのうえで、"variable_if"を使って変数の値に応じた処理を記述していきます。
//emlist[タッチパッド]{
{
  "type": "basic",
  "from": {
    "key_code": "j",
    "modifiers": {
      "optional": ["any" ]
    }
  },
  "to": [
    { "key_code": "up_arrow" }
  ],
  "conditions": [
    {
      "type": "variable_if",
      "name": "multitouch_extension_finger_count_total",
      "value": 1
    }
  ]
}
//}
タッチパッドに1本の指で触れているとJキーを↑に変換する設定です。実際に操作するときは、どちらかの親指で触れるとやりやすいです。

キーバインド設定とは直接関係ないですが、特定のキーボードが接続されている場合に内蔵キーボードを無効化する機能があります。ですが、タッチパッドは無効化できません。この機能を使うときは、Karabiner-Elementsの設定画面の「Device」から「Advanced」にある「Disable the built-in keyboard while one of the following selected device is connected.」で、キーボードを指定します。

=== 2連打に処理を割り当てる方法
ここまでの設定の紹介では思いつきにくいですが便利な設定である、キーの2連打に処理を割り当てる方法を紹介します。"set_variable"による変数の値変更で"condition"の条件判定を用いて実現します。アプリケーションを起動する設定は以下のようになります。
//emlist[アプリ起動]{
"manipulators": [
    {
      "type": "basic",
      "from": { "key_code": "left_control" },
      "to": [
        { "shell_command": "open -a 'safari'" }
      ],
      "conditions": [
        { "type": "variable_if", "name": "left_control_key", "value": 1 }
      ]
    },
    {
      "type": "basic",
      "from": {
        "key_code": "left_control",
        "modifiers": { "optional": [ "any" ] }
      },
      "to": [
        { "set_variable": { "name": "left_control_key", "value": 1 } },
        { "key_code": "left_control" }
      ],
      "to_delayed_action": {
        "to_if_invoked": [
          { "set_variable": { "name": "left_control_key", "value": 0 } }
        ],
        "to_if_canceled": [
          { "set_variable": { "name": "left_control_key", "value": 0 } }
        ]
      },
      "conditions": [
        { "type": "variable_if", "name": "left_control_key", "value": 0 }
      ]
    }
  ]
//}
前半部分はvalueが1のときに実行するので、1回目に押したときは読み飛ばします。後半部分は、左のコントロールと何かのキーが押されたときにvalueを1にして、指定した時間何もしなければ0、他のキーが押されたら0にします。2連打したときはvalueが1のため、前半部分を実行します。という仕組みです。これを文章の入力に使用するときは工夫が必要です。たとえば、「、」キーを2回押すと「。」を入力する設定は、「、」が入力されてしまいます。なので、消す必要があります。
//emlist[「、」2回で「。」を入力]{
{
  "description": "Double tap 'keypad_period' to 'comma'",
  "manipulators": [
    {
      "type": "basic",
      "from": { "key_code": "keypad_period" },
      "to": [
        { "key_code": "delete_or_backspace"},
        { "key_code": "comma" },
        { "set_variable": { "name": "press_period_key", "value": 0 } }
      ],
      "conditions": [
        { "type": "variable_if", "name": "press_period_key", "value": 1 }
      ]
    },
    {
      "type": "basic",
      "from": { "key_code": "keypad_period" },
      "to": [
        { "set_variable": { "name": "press_period_key", "value": 1 } },
        { "key_code": "keypad_period" }
      ],
      "to_delayed_action": {
        "to_if_invoked": [
          { "set_variable": { "name": "press_period_key", "value": 0 } }
        ],
        "to_if_canceled": [
          { "set_variable": { "name": "press_period_key", "value": 0 } }
        ]
      },
      "conditions": [
        { "type": "variable_if", "name": "press_period_key", "value": 0 }
      ]
    }
  ]
}
//}
大体は一つ前に挙げたものと同じです。ですが、前半部分にBackSpaceを一回押す処理を入れたことで2連打するとピリオドが打てたように見えるというものです。

== 終わりに
この章を読むことによって、Karabiner-Elementsによるキー割り当て変更、キーバインド設定、マウス操作が可能になりました使っているキーボードだけでなく使用者の好み・タイピング方法によって使いやすい設定は異なるので、ぜひ自分にあった設定を見つけてください。