# AviUtl プラグイン - 最終フレーム自動調整

タイムラインを編集したとき、最終フレームを自動的に調整します。
[最新バージョンをダウンロード](../../releases/latest/)

## 導入方法

以下のファイルを AviUtl の Plugins フォルダに入れてください。
* AdjustLastFrame.auf
* AdjustLastFrame (フォルダ) (ボイスが必要な場合のみ)

## ボイス

AdjustLastFrame フォルダ内の wav ファイルが再生されます。

* 0 ボイスなし
* 1 青山龍星（ノーマル）最終フレームをちょうせいしました
* 2 波音リツ（ノーマル）最終フレームをちょうせいしました
* 3 九州そら（ささやき）最終フレーム、調整しました
* 4 ~ 10 空き

## 更新履歴

* 2.2.0 - 2022/07/20 発動を知らせるボイスを追加
* 2.1.0 - 2022/06/15 ON/OFF を切り替えられるように変更
* 2.0.1 - 2022/05/11 AviUtl で動画を開いたあと拡張編集で編集作業をするとフリーズする問題を修正
* 2.0.0 - 2022/05/11 リファクタリング
* 1.0.3 - 2022/01/23 オブジェクトの個数を取得するように修正
* 1.0.2 - 2021/12/20 メイン処理を func_proc() で行うように修正
* 1.0.1 - 2021/08/22 最終フレームが 0 にならないように修正
* 1.0.0 - 2021/08/03 初版

## 動作確認

* (必須) AviUtl 1.10 & 拡張編集 0.92 http://spring-fragrance.mints.ne.jp/aviutl/
* (共存確認) patch.aul r41 https://scrapbox.io/ePi5131/patch.aul

## クレジット

* Microsoft Research Detours Package https://github.com/microsoft/Detours
* aviutl_exedit_sdk https://github.com/ePi5131/aviutl_exedit_sdk
* Common Library https://github.com/hebiiro/Common-Library
* VOICEVOX (青山龍星、波音リツ、九州そら) https://voicevox.hiroshiba.jp/

## 作成者情報
 
* 作成者 - 蛇色 (へびいろ)
* GitHub - https://github.com/hebiiro
* Twitter - https://twitter.com/io_hebiiro

## 免責事項

この作成物および同梱物を使用したことによって生じたすべての障害・損害・不具合等に関しては、私と私の関係者および私の所属するいかなる団体・組織とも、一切の責任を負いません。各自の責任においてご使用ください。
