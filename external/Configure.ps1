# *.vcxprojファイルを検索
$files = Get-ChildItem -Path . -Filter *.vcxproj -Recurse

# 各ファイルに対して文字列置換
foreach ($file in $files) {
  # ファイルの内容を読み込む
  $content = Get-Content -Path $file.FullName

  # WindowsSDKとVisualStudioのバージョンを更新する
  $content = $content.Replace("10.0.16299.0", "10.0.22000.0")
  $content = $content.Replace("v141", "v143")

  # ファイルに書き込む
  Set-Content -Path $file.FullName -Value $content
}