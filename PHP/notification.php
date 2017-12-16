<?php
define('LINE_API_URL'  ,"https://notify-api.line.me/api/notify");
define('LINE_API_TOKEN','W8wS2XQ2SkSzxWpA4rNJRrBrUbNunEacW9fQEB9Rl26');

function send_notify(){

  //FeliCaIDを受け取る
  $id;
  if(isset($_GET['id'])){
    $id = $_GET['id'];
    if ( $id == 'sm123' ){
      $id = "カビゴンさんが出勤しました。";
    }elseif ( $id == 'sm456' ) {
      $id = "ピカチュウさんが出勤しました。";
    } else {
      $id = "IDが見つかりません";
    }
  }

  $data = array(
    "message" => $id
  );
  $data = http_build_query($data, "", "&");
  $options = array(
    'http'=>array(
    'method'=>'POST',
    'header'=>"Authorization: Bearer " . LINE_API_TOKEN . "\r\n"
      . "Content-Type: application/x-www-form-urlencoded\r\n"
      . "Content-Length: ".strlen($data)  . "\r\n" ,
    'content' => $data
    )
  );
  $context = stream_context_create($options);
  $resultJson = file_get_contents(LINE_API_URL,FALSE,$context );
  $resutlArray = json_decode($resultJson,TRUE);
  if( $resutlArray['status'] != 200)  {
      return "Error";
  }
  return $id;
}
?>

<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Notification</title>
  </head>
  <body>
    <?php echo send_notify(); ?>
  </body>
</html>