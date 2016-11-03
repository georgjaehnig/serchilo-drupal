<?PHP

//error_log(var_export($message->getChat()->getId(), TRUE));
//return;

require '../../../vendor/autoload.php';
use Telegram\Bot\Api;

$telegram = new Api(SERCHILO_TELEGRAM_BOT_TOKEN);
//$response = $telegram->getMe();

$update = $telegram->getWebhookUpdates();
$message = $update->getMessage();

$response = $telegram->sendMessage([
  'chat_id' => $message->getChat()->getId(),
  'text' => $message->getText()
]);
