<?PHP

require '../../../vendor/autoload.php';
use Telegram\Bot\Api;

/**
 * Create a Telegram API object.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_telegram_create_api($env) {

  $telegram = new Api(SERCHILO_TELEGRAM_BOT_TOKEN);
  return $telegram;
}

/**
 * Populate the environment based on Telegram input.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_telegram_populate_environment(&$env, $telegram) {

  $update = $telegram->getWebhookUpdates();

  if ($message = $update->getMessage()) {
    $env['query'] = $message->getText();
    $env['telegram'] = array();
    $env['telegram']['chat'] = array();
    $env['telegram']['chat']['id'] = $message->getChat()->getId();
  }

  if ($inline_query = $update->getInlineQuery()) {
    $env['query'] = $inline_query->getQuery();
    $env['telegram']['inline_query']['id'] = $inline_query->getId();
  }

    $env = serchilo_parse_query($env['query']) + $env;

    // TODO: Copied this from 
    // serchilo_populate_environment(&$env)
    // case SERCHILO_NAMESPACES_PATH_AFFIX:
    // Needs to be refactored.

    // Add extra_namespace to namespace_names.
    if (!empty($env['extra_namespace_name'])) {
      $env['namespace_names'][] = $env['extra_namespace_name'];
    }
    // Get namespace_ids from namespace_names.
    $env['namespace_ids'] = array_map('serchilo_get_namespace_id', $env['namespace_names']);
}
