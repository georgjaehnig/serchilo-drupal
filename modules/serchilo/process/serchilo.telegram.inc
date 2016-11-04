<?PHP

//error_log(var_export($message->getChat()->getId(), TRUE));
//return;

require '../../../vendor/autoload.php';
use Telegram\Bot\Api;

  $telegram = new Api(SERCHILO_TELEGRAM_BOT_TOKEN);
  //$response = $telegram->getMe();

  $update = $telegram->getWebhookUpdates();
  $message = $update->getMessage();

  $env['query'] = $message->getText();
  $env = serchilo_parse_query($env['query']) + $env;

  $output = serchilo_get_output($env);

  if ($output['status']['found']) {
    $text = $output['url']['final'];
  } else {
    $text = 'Error: No shortcut found.';
  }
  $response = $telegram->sendMessage([
    'chat_id' => $message->getChat()->getId(),
    'text' => $text
  ]);

// TODO: Log the call.
