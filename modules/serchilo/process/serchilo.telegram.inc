<?PHP

//error_log(var_export($message->getChat()->getId(), TRUE));
//return;

require '../../../vendor/autoload.php';
use Telegram\Bot\Api;

/**
 * Process a shortcut Telegram query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_telegram_create_api($env) {

  $telegram = new Api(SERCHILO_TELEGRAM_BOT_TOKEN);
  return $telegram;
}

function serchilo_telegram_populate_environment(&$env, $telegram) {

  $update = $telegram->getWebhookUpdates();
  $message = $update->getMessage();

  $env['query'] = $message->getText();
  $env = serchilo_parse_query($env['query']) + $env;

  $env['telegram'] = array();
  $env['telegram']['chat'] = array();
  $env['telegram']['chat']['id'] = $message->getChat()->getId();
}
